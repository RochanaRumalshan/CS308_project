#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>

#define PI 3.1428571428571428571428571428571


//colors
float road[] = { 0.25f,0.262f,.266f };
float grass[] = { 0,0.406,0.039 };
float marble[] = { 0.988,0.914,0.777 };
float cement[] = { .711,.660,.660 };
float cement2[] = { 0.5,.519,.480 };
float water[] = { .777,.926,.906 };
float building1[] = { .929,.832,.715 };
float building2[] = { .976,.5,.445 };
float board[] = { .695,.133,.133 };
float nameboardWhite[] = { 1.0f,1.0f,1.0f};
float nameboardBlack[] = { 0.0f,0.0f,0.0f };
float silper[] = { 0.533, 0.027, 0.027 };
float fenceColor[] = { 0.235, 0.008, 0.031 };


//light
GLfloat ambientLight[] = { 0,0,0,0 };
GLfloat diffuseLight[] = { 0.2,0.2,0.2,1.0 };
GLfloat specular[] = { 0.60, 0.6, 0.6,1.0 };
GLfloat specref[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat position[] = { 10, 100, 150, 1.0 };

float xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, zrot = 0 , angle = 0.0;
float lastx, lasty;


void init(void) {
	glShadeModel(GL_SMOOTH);

	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);


	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 400);
}

void enable(void) {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);

}

void camera(void) {
	glRotatef(xrot, 1.0, 0.0, 0.0);
	glRotatef(yrot, 0.0, 1.0, 0.0);
	glTranslated(-xpos, -ypos, -zpos);
	//glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void sarasaviUyanaNameBoard() {

	char _facName[20];
	strcpy_s(_facName, "Sarasavi Uyana");
	glPushMatrix();

	glColor3fv(nameboardBlack);
	glRotated(90, 0, 1, 0);
	glRotated(180, 0, 1, 0);

	//glTranslated(50, 20, -50);
	glScaled(.9, .2, .2);
	for (int i = 0; i < 15; i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, _facName[i]);
	glPopMatrix();


	//glPushMatrix();
}


void platform() {

	//glPushMatrix();
	//glTranslated(35, 15, -90);
	//glRotated(190, 0, 1, 0);
	char _stationName[20];
	strcpy_s(_stationName, "Sarasavi Uyana");
	glPushMatrix();
	glColor3fv(nameboardBlack);
	glTranslated(47, 0, -62);
	glRotated(-90, 0, 1, 0);
	glLineWidth(1.5f);
	glScaled(.03, .006, .004);
	for (int i = 0;i < 16;i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, _stationName[i]);
	glPopMatrix();
	//glPushMatrix();
	
	//platform upper building
	glPushMatrix();
	glColor3fv(building1);
	glTranslated(50,0,-50);
	glScaled(1, 1, 6);
	glutSolidCube(6.0);
	/*glPopMatrix();

	glPushMatrix();*/
	//platform base
	glColor3fv(building2);
	glTranslated(0, -5, 0);
	glScaled(1,0.5,2); //z get multiplied by 8 times
	glutSolidCube(10.0);
	glPopMatrix();


	//sarasaviUyanaNameBoard();
	//glPopMatrix();
}

void roof() {
	glPushMatrix();
	glColor3fv(road);
	glTranslated(50, 3, -50);
	glScaled(10, 0.5, 40);
	glutSolidCube(1.0);
	glPopMatrix();

}



//****************************terrain
void drawTerrain()
{
	glPushMatrix();
	glColor3fv(grass);
	glBegin(GL_QUAD_STRIP);

	glVertex3d(220.0, -7.0, 0);
	glVertex3d(220.0, -7.0, -300);
	glVertex3d(-50.0, -6, 0);
	glVertex3d(-50.0, -6, -300);
	
	glEnd();
	glPopMatrix();
}



void railRoad() {
	glPushMatrix();
	glColor3fv(road);
	glTranslated(42, -5, -50);
	glScaled(0.5, 0.5, 300);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glColor3fv(road);
	glTranslated(32, -5, -50);
	glScaled(0.5, 0.5, 300);
	glutSolidCube(1.0);
	glPopMatrix();

	int space = 50;

	//glPushMatrix();
	glColor3fv(silper);
	for (int i = 0; i <60;i++) {
		glPushMatrix();
		glTranslated(36, -5.5, space);
		glScaled(16, 0.5, 0.5);
		glutSolidCube(1.0);
		space = space - 5;
		glPopMatrix();
	}
	glPopMatrix();
}


void fence() {
	glColor3fv(fenceColor); //dark brown

	int upSpace = -1;
	int inBetweenSpace = -5;
	for (int i = 0; i < 3;i++) {
		glPushMatrix();
		glTranslated(56, upSpace, -60);
		glScaled(0.5, .5, 120);
		glutSolidCube(1.0);
		upSpace = upSpace +1;
		glPopMatrix();
	}

	for (int i = 0; i < 23;i++) {
		glPushMatrix();
		glTranslated(55, -5, inBetweenSpace);
		glScaled(0.5,15, 0.5);
		glutSolidCube(1.0);
		inBetweenSpace = inBetweenSpace -5;
		glPopMatrix();
	}
}


void display(void) {
	glClearColor(0.0, 0.79, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	init();
	glLoadIdentity();
	camera();
	enable();

	glColor3f(1.0, 0.0, 0.0);
	GLUquadricObj* cylin = gluNewQuadric();
	//gluCylinder(cylin, 0.5, 0.5, 10, 20, 20);
	//gluDisk(cylin, 0.5, 1.0, 20, 20);

	platform();
	railRoad();
	roof();
	//****************************terrain
	drawTerrain();
	fence();

	glutSwapBuffers();
	angle++;
}

void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'q')
	{
		xrot += 1;
		if (xrot > 360)
			xrot -= 360;
	}

	if (key == 'z')
	{
		xrot -= 1;
		if (xrot < -360) xrot += 360;
	}

	if (key == 'w')
	{
		float xrotrad, yrotrad;
		yrotrad = (yrot / 180 * PI);
		xrotrad = (xrot / 180 * PI);
		xpos += float(sin(yrotrad));
		zpos -= float(cos(yrotrad));
		ypos -= float(sin(xrotrad));
	}

	if (key == 's')
	{
		float xrotrad, yrotrad;
		yrotrad = (yrot / 180 * PI);
		xrotrad = (xrot / 180 * PI);
		xpos -= float(sin(yrotrad));
		zpos += float(cos(yrotrad));
		ypos += float(sin(xrotrad));
	}

	if (key == '.')
	{
		float yrotrad;
		yrotrad = (yrot / 180 * PI);
		xpos += float(cos(yrotrad)) * 0.2;
		zpos += float(sin(yrotrad)) * 0.2;
	}

	if (key == ',')
	{
		float yrotrad;
		yrotrad = (yrot / 180 * PI);
		xpos -= float(cos(yrotrad)) * 0.2;
		zpos -= float(sin(yrotrad)) * 0.2;
	}

	if (key == 'd')
	{
		yrot += 1;
		if (yrot > 360) yrot -= 360;
	}

	if (key == 'a')
	{
		yrot -= 1;
		if (yrot < -360)yrot += 360;
	}

	if (key == 27)
	{
		exit(0);
	}
}

void mouseMovement(int x, int y) {
	int diffx = x - lastx;
	int diffy = y - lasty;
	lastx = x;
	lasty = y;
	xrot += (float)diffy / 10;
	yrot += (float)diffx / 10;

}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Sarasavi Uyana Railway Station");
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);

	glutPassiveMotionFunc(mouseMovement);

	glutKeyboardFunc(keyboard);
	std::cout << "Hello World!\n";
	glutMainLoop();
	return 0;
}





//glPushMatrix();
//glLoadIdentity();
//
//// Rotate before Translate (otherwise wierd things happen)
//glRotated(rotz, 0.0, 0.0, 1.0);
//glRotated(roty, 0.0, 1.0, 0.0);
//glRotated(rotx, 1.0, 0.0, 0.0);
//glTranslated(xpos, ypos, zpos);
//
//glBegin(GL_QUADS);
//glVertex4d(0.0, 0.0, 0.0, 1.0);   // Start from Origin
//glVertex4d(0.0, yLen, 0.0, 1.0);
//glVertex4d(xLen, yLen, 0.0, 1.0);
//glVertex4d(xLen, 0.0, 0.0, 1.0);
//
//glVertex4d(0.0, 0.0, 0.0, 1.0);  // Start new face
//glVertex4d(0.0, 0.0, zLen, 1.0);
//glVertex4d(0.0, yLen, zLen, 1.0);
//glVertex4d(0.0, yLen, 0.0, 1.0);
//
////etc...
//glEnd();
//glPopMatrix();