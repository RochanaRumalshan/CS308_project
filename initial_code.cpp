#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glut.h>
#include <math.h>

#define PI 3.1428571428571428571428571428571

float width = 30.0f; //road width
float stepWidth = 10.0f;
float stepHeight = 1.5f;
float stepLength = 1.5f;

//colors
float road[] = {0.25f,0.262f,.266f};
float grass[] = {0,0.406,0.039};
float marble[] = {0.988,0.914,0.777};
float cement[] = {.711,.660,.660};
float cement2[] = {0.5,.519,.480};
float water[] = {.777,.926,.906};
float building1[] = {.929,.832,.715};
float building2[] = {.976,.5,.445};
float board[] = {.695,.133,.133};

//light
GLfloat ambientLight[]={0.2,0.2,0.2,1.0};
GLfloat diffuseLight[]={0.2,0.2,0.2,1.0};
GLfloat specular[]={0.60, 0.6, 0.6,1.0};
GLfloat specref[]={0.8, 0.8, 0.8, 1.0};
GLfloat position[]={10, 100, 150, 1.0};

float xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, angle=0.0;

float lastx, lasty; //for the mouse function


//****************************roads
void straightRoad(float stX, float stZ, float length, float width)
{
	glPushMatrix();
	glColor3fv(road);
		glBegin(GL_QUADS);
			glNormal3d(0,1,0);
			//glNormal3d(stX+width/2,-5,stZ);
			glVertex3d(stX+width/2,-5.1,stZ);
			//glNormal3d(stX-width/2,-5,stZ);
			glVertex3d(stX-width/2,-5.1,stZ);
			//glNormal3d(stX-width/2,-5,length+stZ);
			glVertex3d(stX-width/2,-5.1,length+stZ);
			//glNormal3d(stX+width/2,-5,length+stZ);
			glVertex3d(stX+width/2,-5,length+stZ);
		glEnd();
	glPopMatrix();
}

void rightRoad(float stX, float stZ, float length, float width)
{
	glPushMatrix();
	glColor3fv(road);
		glBegin(GL_QUADS);
			glNormal3d(0,1,0);
			//glNormal3d(stX+width/2,-5,stZ);
			glVertex3d(stX,-5.1,stZ+width/2);
			//glNormal3d(stX-width/2,-5,stZ);
			glVertex3d(stX,-5.1,stZ-width/2);
			//glNormal3d(stX-width/2,-5,length+stZ);
			glVertex3d(length+stX,-5.1,stZ-width/2);
			//glNormal3d(stX+width/2,-5,length+stZ);
			glVertex3d(length+stX,-5,stZ+width/2);
		glEnd();
	glPopMatrix();
}

void rightTurnI(float x, float y, float z)
{
	glPushMatrix();
	glTranslated(x,y,z);
	glBegin(GL_QUAD_STRIP);
	glNormal3d(0,1,0);
		for(int i= 180; i>90; i--)
		{
			glColor3fv(road);
			
			//glNormal3d(width*cos(i*PI/180),-5,width*sin(i*PI/180));
			//glNormal3d(width/2*cos(i*PI/180),-5,width/2*sin(i*PI/180));
			glVertex3d(width*cos(i*PI/180),-5,width*sin(i*PI/180));
			glVertex3d(width/2*cos(i*PI/180),-5,width/2*sin(i*PI/180));
		}
	glEnd();
	glPopMatrix();
}

void rightTurn(float x, float y, float z)
{
	glPushMatrix();
	glTranslated(x,y,z);
	glBegin(GL_QUAD_STRIP);
	glNormal3d(0,1,0);
		for(int i= 180; i<270; i++)
		{
			glColor3fv(road);
			
			//glNormal3d(width*cos(i*PI/180),-5,width*sin(i*PI/180));
			//glNormal3d(width/2*cos(i*PI/180),-5,width/2*sin(i*PI/180));
			glVertex3d(width*cos(i*PI/180),-5,width*sin(i*PI/180));
			glVertex3d(width/2*cos(i*PI/180),-5,width/2*sin(i*PI/180));
		}
	glEnd();
	glPopMatrix();
}

void leftTurn(float x, float y, float z)
{
	
	glPushMatrix();
	glTranslated(x,y,z);
	glBegin(GL_QUAD_STRIP);
	glNormal3d(0,1,0);
		for(int i= 270; i<360; i++)
		{
			glColor3fv(road);
			
			//glNormal3d(width*cos(i*PI/180),-5,width*sin(i*PI/180));
			//glNormal3d(width/2*cos(i*PI/180),-5,width/2*sin(i*PI/180));
			glVertex3d(width*cos(i*PI/180),-5,width*sin(i*PI/180));
			glVertex3d(width/2*cos(i*PI/180),-5,width/2*sin(i*PI/180));
		}
	glEnd();
	glPopMatrix();
}

//****************************Steps
void leftSteps(float x, float y, float z, int n)
{
	float oriX = x;
	float oriY = y;
	glPushMatrix();
		glColor3fv(cement);
		glBegin(GL_QUAD_STRIP);
			for(int i = 0; i<n; i++)
			{
				glNormal3d(0,1,0);
				glVertex3d(x,y,z-stepWidth/2);
				glVertex3d(x,y,z+stepWidth/2);
				glNormal3d(1,0,0);
				glVertex3d(x-stepLength,y,z-stepWidth/2);
				glVertex3d(x-stepLength,y,z+stepWidth/2);
				x-=stepLength;
				y+=stepHeight;
			}
		glEnd();
		x = oriX;
		y = oriY;
		glBegin(GL_QUADS);
		glColor3fv(cement2);
			for(int i = 0; i<n-1; i++)
			{
				glNormal3d(0,0,-1);
				glVertex3d(x-stepLength,y,z-stepWidth/2);
				glVertex3d(x-2*stepLength,y,z-stepWidth/2);
				glVertex3d(x-2*stepLength,y+stepHeight,z-stepWidth/2);
				glVertex3d(x-stepLength,y+stepHeight,z-stepWidth/2);
				x-=stepLength;
				y+=stepHeight;
			}
		glEnd();
		x = oriX;
		y = oriY;
		glBegin(GL_QUADS);
			for(int i = 0; i<n-1; i++)
			{
				glNormal3d(0,0,1);
				glVertex3d(x-stepLength,y,z+stepWidth/2);
				glVertex3d(x-2*stepLength,y,z+stepWidth/2);
				glVertex3d(x-2*stepLength,y+stepHeight,z+stepWidth/2);
				glVertex3d(x-stepLength,y+stepHeight,z+stepWidth/2);
				x-=stepLength;
				y+=stepHeight;
			}
		glEnd();

	glPopMatrix();
}

//Water fountain
void drawWaterFountain(float x, float y, float z, float h, float r)
{
	glColor3d(.99,.95,.7);
	glPushMatrix();
		
		glTranslated(x,y,z);

		glBegin(GL_QUAD_STRIP);
		glNormal3d(0,1,0);
			for(int i=0;i<363; i++)
			{
				//round about road
				glColor3fv(road);
				
				//glNormal3d(r*cos(i*PI/180),-5,r*sin(i*PI/180));
				//glNormal3d(r*8*cos(i*PI/180),-5,r*8*sin(i*PI/180));
				glVertex3d(r*cos(i*PI/180),-5,r*sin(i*PI/180));
				glVertex3d(r*8*cos(i*PI/180),-5,r*8*sin(i*PI/180));
			}
		glEnd();

		glBegin(GL_QUAD_STRIP);
			for(int i=0;i<363; i++)
			{
				//round cement part
				glColor3fv(cement);
				//glNormal3d(r*3*cos(i*PI/180),-5,r*3*sin(i*PI/180));
				//glNormal3d(r*3*cos(i*PI/180),-5+1,r*3*sin(i*PI/180));
				glVertex3d(r*3*cos(i*PI/180),-5,r*3*sin(i*PI/180));
				glVertex3d(r*3*cos(i*PI/180),-5+1,r*3*sin(i*PI/180));
			}
		glEnd();
			glBegin(GL_QUAD_STRIP);
			for(int i=0;i<363; i++)
			{
				//grass part
				glColor3fv(grass);				
				//glNormal3d(r*3*cos(i*PI/180),-5+1,r*3*sin(i*PI/180));
				//glNormal3d(r*cos(i*PI/180),-5+2,r*sin(i*PI/180));
				glVertex3d(r*3*cos(i*PI/180),-5+1,r*3*sin(i*PI/180));
				glVertex3d(r*cos(i*PI/180),-5+2,r*sin(i*PI/180));
			}
		glEnd();
		glBegin(GL_QUAD_STRIP);
			for(int i= 0; i<363; i++)
			{
				//base
				glColor3fv(marble);				
				//glNormal3d(r*cos(i*PI/180),-5+2,r*sin(i*PI/180));
				//glNormal3d(r/2*cos(i*PI/180),-5+h,r/2*sin(i*PI/180));
				glVertex3d(r*cos(i*PI/180),-5+2,r*sin(i*PI/180));
				glVertex3d(r/2*cos(i*PI/180),-5+h,r/2*sin(i*PI/180));
			}
		glEnd();
		glBegin(GL_QUAD_STRIP);
			for(int i= 0; i<363; i++)
			{
				//fountain
				glColor3fv(marble);
				//glNormal3d(0.3,.5,.1);
				//glNormal3d(r/2*cos(i*PI/180),(-5+h)/500,r/2*sin(i*PI/180));
				glVertex3d(r/2*cos(i*PI/180),-5+h,r/2*sin(i*PI/180));
				//glNormal3d(r*2*cos(i*PI/180),-5+h+3,r*2*sin(i*PI/180));
				glVertex3d(r*2*cos(i*PI/180),-5+h+3,r*2*sin(i*PI/180));
			}
		glEnd();

		glPushMatrix();
		glTranslated(0,-5+h+3,0);
		//glutSolidSphere(3.0,20,10);
		glPopMatrix();

		glPushMatrix();
			glBegin(GL_TRIANGLE_FAN);
				glColor3fv(water);
				for(int i= 0; i<363; i++)
				{//water
					//glNormal3d(r*cos(i*PI/180),-5+h+2,r*sin(i*PI/180));
					glVertex3d(r*cos(i*PI/180),-5+h+1,r*sin(i*PI/180));
				}
			glEnd();
		glPopMatrix();

	glPopMatrix();
}

//****************************buildings
void wijewardene()
{
	char _wijewardene[20];
	strcpy_s(_wijewardene,"WIJEWARDENE");
	glPushMatrix();
	glColor3fv(road);
		glTranslated(84,6,-58);
		glRotated(270,0,1,0);
		glScaled(.02,.02,.02);
		for(int i=0;i<11;i++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, _wijewardene[i]);
	glPopMatrix();

	glPushMatrix();
	glColor3fv(building1);
		glTranslated(100,-6,-50);
		glutSolidCube(30.0);
		glTranslated(0,0,0);
	glPopMatrix();

	glPushMatrix();
	glColor3fv(building1);
	glTranslated(111,0,-65);
		glRotated(-30,0,1,0);
		glScaled(1,.5,2);
		glutSolidCube(27.0);
	glPopMatrix();

	glPushMatrix();
	glColor3fv(building1);
	glTranslated(130,0,-35);
		glRotated(60,0,1,0);
		glScaled(1,.5,2);
		glutSolidCube(27.0);
	glPopMatrix();
}

void mlt()
{
	glPushMatrix();
	glColor3fv(building1);
	glTranslated(150,0,-120);
		glRotated(180,0,1,0);
		glScaled(1,.5,.3);
		glutSolidCube(25.0);
	glPopMatrix();
}

void faculty()
{
	glPushMatrix();
	glColor3fv(building2);
	glTranslated(120,0,-160);
		glRotated(180,0,1,0);
		glScaled(5,1,.3);
		glutSolidCube(25.0);
	glPopMatrix();

	glPushMatrix();
	glColor3fv(building1);
	glTranslated(73,0,-175);
		glRotated(90,0,1,0);
		glutSolidCube(25.0);
	glPopMatrix();

	glPushMatrix();
	glColor3fv(building2);
	glTranslated(120,0,-185);
		glRotated(180,0,1,0);
		glScaled(5,1,.3);
		glutSolidCube(25.0);
	glPopMatrix();
}

void jayathilaka()
{
	glPushMatrix();
	glTranslated(35,15,-90);
	glRotated(190,0,1,0);
		char _wijewardene[20];
		strcpy_s(_wijewardene,"JAYATHILAKA HALL");
		glPushMatrix();
		glColor3fv(road);
			glTranslated(84.5,6,-62);
			glRotated(270,0,1,0);
			glScaled(.02,.02,.02);
			for(int i=0;i<16;i++)
				glutStrokeCharacter(GLUT_STROKE_ROMAN, _wijewardene[i]);
		glPopMatrix();

		glPushMatrix();
		glColor3fv(building1);
			glTranslated(100,-6,-50);
			glutSolidCube(30.0);
			glTranslated(0,0,0);
		glPopMatrix();

		glPushMatrix();
		glColor3fv(building1);
		glTranslated(111,0,-65);
			glRotated(-30,0,1,0);
			glScaled(1,.5,2);
			glutSolidCube(27.0);
		glPopMatrix();

		glPushMatrix();
		glColor3fv(building1);
		glTranslated(130,0,-35);
			glRotated(60,0,1,0);
			glScaled(1,.5,2);
			glutSolidCube(27.0);
		glPopMatrix();
	glPopMatrix();
}

//**************************name post
void namePost()
{
	char _facName[20];
	strcpy_s(_facName,"Science Faculty");
	glPushMatrix();
	glColor3fv(road);
		glTranslated(25.5,-4,-184.5);
		glScaled(.009,.02,.02);
		for(int i=0;i<15;i++)
			glutStrokeCharacter(GLUT_STROKE_ROMAN, _facName[i]);
	glPopMatrix();

	glPushMatrix();
	glColor3fv(board);
	glTranslated(30,-5,-185);
		//glRotated(90,0,1,0);
		glScaled(.38,.3,.02);
		glutSolidCube(25.0);
	glPopMatrix();
}

//****************************terrain
void drawTerrain()
{
	glPushMatrix();
	glColor3fv(grass);
		glBegin(GL_QUAD_STRIP);
			/*glNormal3d(50.0,-10.0,0);
			glNormal3d(50.0,-10.0,-100);
			glNormal3d(15.0,-6,0);				
			glNormal3d(15.0,-6,-100);
			glNormal3d(-15,-6,0);
			glNormal3d(-15,-6,-100);
			glNormal3d(-30,10,0);	
			glNormal3d(-30,10,-100);*/

			glVertex3d(220.0,-7.0,0);
			glVertex3d(220.0,-7.0,-300);
			glVertex3d(15.0,-6,0);				
			glVertex3d(15.0,-6,-300);
			glVertex3d(-15,-6,0);
			glVertex3d(-15,-6,-100);
			glVertex3d(-15,-6,-210);
			glVertex3d(-30,10,0);	
			glVertex3d(-30,10,-100);	
			glVertex3d(-30,10,0);	
			glVertex3d(-80,10,0);	
			glVertex3d(-80,10,-100);
		glEnd();
	glPopMatrix();
}

//******************Scene
void scene(void) 
{
	drawTerrain();
	rightTurn(30,0,-10); //wijewaredene turn
	rightRoad(27,-32.6,30,15);

	wijewardene();

	
	jayathilaka();	

	mlt();

	namePost();

	faculty();

	leftSteps(-14.19,-4.9,-50,11); //jayathilaka steps 1

	rightRoad(27,-72.6,50,15);//mlt road
	rightTurn(30,0,-50); //mlt turn 1
	rightTurnI(30,0,-110); //mlt turn 2

	drawWaterFountain(0,0,-215,5,3);//alwis pond
	rightRoad(15,-222,100,20); //science turn

	straightRoad(0,0,-210,30.0f); //galaha road
}

void init (void) {
	glShadeModel(GL_SMOOTH);
	//glEnable(GL_LIGHTING);
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambientLight);
	glLightfv(GL_LIGHT0,GL_DIFFUSE,diffuseLight);
	glLightfv(GL_LIGHT0,GL_SPECULAR,specular);
	glLightfv(GL_LIGHT0,GL_POSITION,position);
	//glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT,GL_SPECULAR,specref);
	glMateriali(GL_FRONT,GL_SHININESS,400);
}

void enable (void) {
    glEnable (GL_DEPTH_TEST); //enable the depth testing
	glEnable(GL_NORMALIZE);
    glEnable (GL_LIGHTING); //enable the lighting
    glEnable (GL_LIGHT0); //enable LIGHT0, our Diffuse Light
    glShadeModel (GL_SMOOTH); //set the shader to smooth shader

}

void camera (void) {
    glRotatef(xrot,1.0,0.0,0.0);  //rotate our camera on teh x-axis (left and right)
    glRotatef(yrot,0.0,1.0,0.0);  //rotate our camera on the y-axis (up and down)
    glTranslated(-xpos,-ypos,-zpos); //translate the screen to the position of our camera
	glLightfv(GL_LIGHT0,GL_POSITION,position);
}

void display (void) {
    glClearColor (0.0,0.79,1.0,1.0); 
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	    init (); 
    glLoadIdentity();
    camera();
    enable();
    scene();
	
    glutSwapBuffers();
    angle++;
}

void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei)w, (GLsizei)h); 
    glMatrixMode (GL_PROJECTION); 
    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0); 
    glMatrixMode (GL_MODELVIEW); 

}

void keyboard (unsigned char key, int x, int y) {
    if (key=='q')
    {
    xrot += 1;
    if (xrot >360) 
		xrot -= 360;
    }

    if (key=='z')
    {
    xrot -= 1;
    if (xrot < -360) xrot += 360;
    }

    if (key=='w')
    {
    float xrotrad, yrotrad;
    yrotrad = (yrot / 180 * PI);
    xrotrad = (xrot / 180 * PI); 
    xpos += float(sin(yrotrad)) ;
    zpos -= float(cos(yrotrad)) ;
    ypos -= float(sin(xrotrad)) ;
    }

    if (key=='s')
    {
    float xrotrad, yrotrad;
    yrotrad = (yrot / 180 * PI);
    xrotrad = (xrot / 180 * PI); 
    xpos -= float(sin(yrotrad));
    zpos += float(cos(yrotrad)) ;
    ypos += float(sin(xrotrad));
    }

    if (key=='.')
    {
    float yrotrad;
    yrotrad = (yrot / 180 * PI);
    xpos += float(cos(yrotrad)) * 0.2;
    zpos += float(sin(yrotrad)) * 0.2;
    }

    if (key==',')
    {
    float yrotrad;
    yrotrad = (yrot / 180 * PI);
    xpos -= float(cos(yrotrad)) * 0.2;
    zpos -= float(sin(yrotrad)) * 0.2;
    }

	if (key=='d')
    {
    yrot += 1;
    if (yrot >360) yrot -= 360;
    }

    if (key=='a')
    {
    yrot -= 1;
    if (yrot < -360)yrot += 360;
    }

    if (key==27)
    {
    exit(0);
    }
}

void mouseMovement(int x, int y) {
    int diffx=x-lastx; 
    int diffy=y-lasty; 
    lastx=x; 
    lasty=y; 
    xrot += (float) diffy; 
    yrot += (float) diffx;    
}

int main (int argc, char **argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_DEPTH); 
    glutInitWindowSize (800, 600); 
    glutInitWindowPosition (100, 100);
    glutCreateWindow ("MAP - Wijewardene Hall to Alwis pond"); 
    glutDisplayFunc (display); 
    glutIdleFunc (display); 
    glutReshapeFunc (reshape);

    glutPassiveMotionFunc(mouseMovement);

    glutKeyboardFunc (keyboard); 
    glutMainLoop (); 
    return 0;
}