#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>

#define PI 3.1428571428571428571428571428571


//colors

float red[] = { 0.5, 0.0, 0.0 };
float trainEngine[] = { 0.0,0.0,0.0 };//engine
float crashbars[] = { 0.4, 0.4, 0.4 };//crashbars
float steampipe[] = { 0.1,0.1,0.1 };
float box[] = { 0.1,0.1,0 };
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

float xpos = 0, ypos = 0, zpos = 0, xrot = 0, yrot = 0, zrot = 0 , drive = 0.0 , angle=0.0;
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
	glScaled(.03, .022, .004);
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


//******train
void train(GLfloat x, GLfloat y, GLfloat z){
	GLUquadricObj* qobj = gluNewQuadric();

	glPushMatrix();

	glPushMatrix();
	glColor3fv(cement);
	glTranslated(x + 40, y, z - 20);
	glRotated(180, 0, 1, 0);
	glScaled(1.2, .5, .6);
	glutSolidCube(25.0);
	glPopMatrix();

	//engine- cylinder
	glPushMatrix();
	glColor3fv(trainEngine);
	glTranslated(x + 5, y, z - 20);
	glRotatef(90, 0.0, 1, 0.0);
	//glScaled(0.3, 0.3, 0.3);
	gluCylinder(qobj, 5, 5, 25, 100, 36);
	glPopMatrix();

	//chimini
	glPushMatrix();
	glColor3fv(trainEngine);
	glTranslated(x + 12, y + 9, z - 20);
	glRotatef(90, 1.0, 0.0, 0.0);
	gluCylinder(qobj, 1, 1, 5, 36, 36);
	gluCylinder(qobj, 1, 2.2, 1.5, 36, 36);
	glPopMatrix();

	//valve
	glPushMatrix();
	glColor3fv(trainEngine);
	glTranslated(x + 20, y + 7, z - 20);
	glRotatef(90, 1.0, 0.0, 0.0);
	gluCylinder(qobj, 2, 2, 3, 36, 36);
	gluCylinder(qobj, 0.1, 2, 0.1, 36, 36);
	glPopMatrix();

	//light
	glPushMatrix();
	glColor3fv(trainEngine);
	glTranslated(x + 5, y + 6, z - 20);
	glRotatef(90, 0.0, 1.0, 0.0);
	gluCylinder(qobj, 1, 1, 2, 36, 36);
	glPopMatrix();

	//engineBase
	glPushMatrix();
	glColor3fv(red);
	glTranslated(x + 15, y - 5, z - 20);
	glScaled(1, .1, .5);
	glutSolidCube(25.0);
	glPopMatrix();

	//engineCup
	glPushMatrix();
	glColor3fv(trainEngine);
	glTranslated(x + 5, y, z - 20);
	glScaled(0.3, 1, 1);
	glutSolidSphere(5.0, 100, 300);
	glPopMatrix();

	//lightCup
	glPushMatrix();
	glColor3fv(trainEngine);
	glTranslated(x + 7, y + 6, z - 20);
	glScaled(0.3, 1, 1);
	glutSolidSphere(1.0, 100, 300);
	glPopMatrix();

	//headCup cylinders left
	glPushMatrix();
	glColor3fv(trainEngine);
	glTranslated(x, y - 5, z - 24);
	glRotatef(90, 0.0, 1, 0.0);
	gluCylinder(qobj, 1, 1, 3, 50, 36);
	glRotatef(90, 0.0, 1, 0.0);
	glScaled(0.3, 1, 1);
	glutSolidSphere(1.2, 100, 300);
	glPopMatrix();

	//headCup cylinders right
	glPushMatrix();
	glColor3fv(trainEngine);
	glTranslated(x, y - 5, z - 16);
	glRotatef(90, 0.0, 1, 0.0);
	gluCylinder(qobj, 1, 1, 3, 50, 36);
	glRotatef(90, 0.0, 1, 0.0);
	glScaled(0.3, 1, 1);
	glutSolidSphere(1.2, 100, 300);
	glPopMatrix();

	//crash bars right
	float t = 53;
	float v = 45;
	for (float i = 0; i < 7;i++) {

		glPushMatrix();
		glRotatef(-25, 0.0, 0.0, 1.0);
		glColor3fv(crashbars);
		glTranslated(x + 3.42 + v + (i / 5), y -6 + t+ (i / 5), z -20 - i );
		glRotatef(90, 1.0, 0.0, 0.0);
		gluCylinder(qobj, 0.2, 0.2, 5, 50, 36);
		glPopMatrix();
	}
	//crash bars left
	for (float i = 0; i < 7; i++) {

		glPushMatrix();
		glRotatef(-25, 0.0, 0.0, 1.0);
		glColor3fv(crashbars);
		glTranslated(x + 3.42  + (i / 5), y -6+ t + (i / 5), z - 20 + i );
		//glRotatef(90, 1.0, 0.0, 0.0);
		gluCylinder(qobj, 0.2, 0.2, 5, 50, 36);
		glPopMatrix();
	}


	//barholders
	glPushMatrix();
	glColor3fv(red);
	glTranslated(x + 2, y - 7, z - 20);
	glScaled(0.25, .15, 1);
	glutSolidCube(14);
	glPopMatrix();


	//nuts 1
	for (float i = 0; i <= 12; i++) {
		glPushMatrix();
		glColor3fv(trainEngine);
		glTranslated(x + 2.5, y - 4, z - 26 + i);
		glutSolidSphere(0.1, 100, 100);
		glPopMatrix();
	}

	//nuts 1-left
	for (float i = 0; i < 3; i++) {
		glPushMatrix();
		glColor3fv(trainEngine);
		glTranslated(x + 2.5, y - 4.47 - (i / 2), z - 26);
		glutSolidSphere(0.1, 100, 100);
		glPopMatrix();
	}
	//nuts 1-right
	for (float i = 0; i < 3; i++) {
		glPushMatrix();
		glColor3fv(trainEngine);
		glTranslated(x + 2.5, y - 4.47 - (i / 2), z - 14);
		glutSolidSphere(0.1, 100, 100);
		glPopMatrix();
	}

	//nuts 2
	for (float i = 0; i < 14; i++) {
		glPushMatrix();
		glColor3fv(trainEngine);
		glTranslated(x + 0.2, y - 6.2, z - 26.4 + i);
		glutSolidSphere(0.1, 100, 100);
		glPopMatrix();
	}

	//nuts 3

	for (float i = 0; i < 3; i++) {
		glPushMatrix();
		glColor3fv(trainEngine);
		glTranslated(x + 0.2, y - 6.7 - (i / 2), z - 26.4);
		glutSolidSphere(0.1, 100, 100);
		glPopMatrix();
	}

	//nuts 3

	for (float i = 0; i < 3; i++) {
		glPushMatrix();
		glColor3fv(trainEngine);
		glTranslated(x + 0.2, y - 6.7 - (i / 2), z - 14 + 0.56);
		glutSolidSphere(0.1, 100, 100);
		glPopMatrix();
	}
	//underbars
	glPushMatrix();
	glPushMatrix();
	glColor3fv(red);
	glTranslated(x - 0.5, y - 11, z - 23.5);
	glRotatef(-16, 0.0, 1, 0.0);
	glScaled(0.1, 0.1, 1);
	glutSolidCube(9);
	glPopMatrix();

	glPushMatrix();
	glColor3fv(red);
	glTranslated(x - 0.5, y - 11, z - 16.5);
	glRotatef(16, 0.0, 1, 0.0);
	glScaled(0.1, 0.1, 1);
	glutSolidCube(9);
	glPopMatrix();
	glPopMatrix();
	//wheels left
	for (float j = 0; j < 8;j++) {
		glPushMatrix();
		glColor3fv(trainEngine);
		glTranslated(x + 5 + (j * 7), y - 10.5, z - 14);
		glScaled(1, 1, 0.5);
		glutSolidSphere(0.6, 100, 100);
		glutSolidTorus(0.7, 3.20, 60, 60);
		glRotatef(90, 0.0, 1.0, 0.0);
		for (int i = 0; i < 20; i++) {
			glRotatef(i * (18), 1.0, 0.0, 0.0);
			gluCylinder(qobj, 0.2, 0.12, 3.7, 50, 36);
		}
		glPopMatrix();
	}
	//wheels right
	for (float j = 0; j < 8; j++) {
		glPushMatrix();
		glColor3fv(trainEngine);
		glTranslated(x + 5 + (j * 7), y - 10.5, z - 26);
		glScaled(1, 1, 0.5);
		glutSolidSphere(0.6, 100, 100);
		glutSolidTorus(0.7, 3.20, 60, 60);
		glRotatef(90, 0.0, 1.0, 0.0);
		for (int i = 0; i < 20; i++) {
			glRotatef(i * (18), 1.0, 0.0, 0.0);
			gluCylinder(qobj, 0.2, 0.12, 3.7, 50, 36);
		}

		glPopMatrix();
	}

	//steampipes
	glPushMatrix();
	glColor3fv(steampipe);
	glTranslated(x + 5, y + 1, z - 14.8);
	glRotatef(90, 0.0, 1, 0.0);
	gluCylinder(qobj, 0.3, 0.3, 20, 100, 36);
	//glScaled(1, 0.1, 1);
	glScaled(1, 1, 0.1);
	glutSolidSphere(0.3, 100, 100);
	glPopMatrix();

	glPushMatrix();
	glColor3fv(steampipe);
	glTranslated(x + 5, y + 1, z - 25.2);
	glRotatef(90, 0.0, 1, 0.0);
	gluCylinder(qobj, 0.3, 0.3, 20, 100, 36);
	glScaled(1, 1, 0.1);
	glutSolidSphere(0.3, 100, 100);
	glPopMatrix();

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
	glRotatef(90,0.0,1.0,0.0);
	//glTranslatef(0.0, 0.0, 0.0);
	glTranslatef(drive,0.0,0.0);
	train(110.0,9.5,57.0);

	glutSwapBuffers();
	drive = drive -0.1;
	//angle = angle + 0.1;
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

	if(key == 'r'){
		drive = 0.0;
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