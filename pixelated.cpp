#include <Windows.h>
#include<stdio.h>
#include<iostream>
#include <gl/glut.h>
#include <math.h>

#define KEY_ESC 27 /* GLUT doesn't supply this */

using namespace std;

int fullscreen = 0;
int mouseDown = 0;

float xrot = 100.0f;
float yrot = -100.0f;

float xdiff = 100.0f;
float ydiff = 100.0f;

float tra_x = 0.0f;
float tra_y = 0.0f;
float tra_z = 0.0f;


float grow_shrink = 70.0f;
float resize_f = 1.0f;

//const float THICKNESS = 15;
const float PI = 3.141592653979;
//const float UNADJUSTED_RADIUS = 200;
const float MAIN_RADIUS = 1;// 8 rings + 8 gaps + radius of the center
const float SMALL_RADIUS = (MAIN_RADIUS / 20); // Since there are 9 rings 
const float SMALL_DIAMETER = SMALL_RADIUS * 2;
const float GAP = SMALL_RADIUS / 3;

const float WINDOW_WIDTH = 500;
const float WINDOW_HEIGHT = WINDOW_WIDTH;


struct Point
{
	double X;
	double Y;

	bool operator==(Point p) {
		if (X == p.X && Y == p.Y)
			return true;
		else
			return false;
	}

	bool operator!=(Point p) {
		if (X == p.X && Y == p.Y)
			return false;
		else
			return true;
	}


	Point operator+(float f) {
		Point p = { X + f, Y + f };
		return p;
	}

	Point operator-(float f) {
		Point p = { X - f, Y - f };
		return p;
	}

};

struct Circle {
	double radius;
	Point center;

	float getCircumference() {
		return PI * (radius * 2);
	}

};

struct Color {
	float R;
	float G;
	float B;

};


Circle Rings[7];
Color RingColor[7];
const Point CENTER = { 0.0, 0.0 };

void handleKeypress(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
	}
}
float getRadian(float degree) {
	// Converts degree to radian
	return (degree * 3.141592653979) / 180;
}

void drawCircle(Point center, float radius, float z = 0) {
	// The following code makes a circle by creating 360 vertexes, whose locations are calculated by an angle,
	// radius of the circle and the center of the circle
	float theta;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		theta = getRadian(i);

		glVertex3f((radius * cos(theta)) + center.X, (radius * sin(theta) + center.Y), z);
	}
	glEnd();
}

void setColors() {
	// The following is a list of colors from the innermost outwards
	RingColor[0] = { 0.90, 0.73, 0.25 };
	RingColor[1] = { 0.64, 0.12, 0.13 };
	RingColor[2] = { 0.60, 0.30, 0.35 };
	RingColor[3] = { 0.29, 0.08, 0.47 };
	RingColor[4] = { 0.20, 0.29, 0.51 };
	RingColor[5] = { 0.33, 0.51, 0.32 };
	RingColor[6] = { 0.44, 0.64, 0.45 };
}
void setRings() {
	// The following initialzes each ring's radius and center;
	for (int i = 0; i < 7; i++) {
		Rings[i].center = CENTER;
		Rings[i].radius = (i + 1) * (SMALL_DIAMETER + GAP);

	}
	setColors();
}

int getNumberOfCirclesPerRing(Circle c) {
	// The circumference divided by the diameter and the gaps tells us how many others circles would fit
	int number = (c.getCircumference() / (SMALL_DIAMETER + GAP));
	return number > 1 ? number : 1;
}

void drawCirclesOnRing(Circle ring) {
	// Gets the number of circles per ring
	int number = getNumberOfCirclesPerRing(ring);

	for (int i = 1; i <= number; i++) {
		// For each circle on the ring the following two lines calculate the angle of position
		float multiplicationFactor = (float)i / (float)number;
		float theta = getRadian((360 * multiplicationFactor));

		// The following Point is the center of the each circle on the ring calculated from the ring radius
		Point miniCenter = {
			(ring.radius * cos(theta)) + ring.center.X,
			(ring.radius * sin(theta)) + ring.center.Y
		};
		drawCircle(miniCenter, SMALL_RADIUS, 0.01);
	}
}






void drawBox()
{


	glTranslatef(tra_x, tra_y, tra_z);


	// Draws the main circle
	glColor3f(0.07, 0.07, 0.07);
	drawCircle(CENTER, MAIN_RADIUS);

	// Draws the inner most circle
	glColor3f(0.92, 0.79, 0.34);
	drawCircle(CENTER, SMALL_RADIUS, 0.01);

	drawCircle(CENTER, SMALL_RADIUS, 0.01);

	// Draws the rest of the circle
	for (int i = 0; i < 7; i++) {
		glColor3f(RingColor[i].R, RingColor[i].G, RingColor[i].B);
		drawCirclesOnRing(Rings[i]);
	}

	glFlush();
}

int init(void)
{
	glClearColor(0.93f, 0.93f, 0.93f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glClearDepth(1.0f);

	return 1;
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(
		0.0f, 0.0f, 3.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f);

	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);

	drawBox();

	glFlush();
	glutSwapBuffers();
}

void resize(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);

	gluPerspective(grow_shrink, resize_f * w / h, resize_f, 100 * resize_f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void idle(void)
{
	if (!mouseDown)
	{
		xrot += 0.3f;
		yrot += 0.4f;
	}

	glutPostRedisplay();
}


void mySpecialFunction(int key, int x, int y)
{
	cout << "U -----------> rotate clockwise\n";
	cout << "W or w ------> Up\n";
	cout << "S or s -----> Down\n";
	cout << "D or d ------> Right\n";
	cout << "A or a ------> Left\n";
	cout << "Z or z ------> Shrink\n";
	cout << "X or x ------> Grow\n";
	cout << "Z or z ------> Shrink\n";
	cout << "Escape Key ---> exit the program\n\n";

}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(1);
		break;



	case 'w':
	case 'W':
		tra_x += 0.1f;
		break;
	case 's':
	case 'S':
		tra_x -= 0.1f;
		break;
	case 'a':
	case 'A':
		tra_z -= 0.1f;
		break;
	case 'd':
	case 'D':
		tra_z += 0.1f;
		break;
	case 'u':
	case 'U':
		xrot += 1.0f;
		yrot += 1.0f;
		xdiff += 1.0f;
		ydiff += 1.0f;
		break;

	case 'y':
	case 'Y':
		xrot -= 1.0f;
		yrot -= 1.0f;
		xdiff += 1.0f;
		ydiff += 1.0f;
		break;

	case 'h':
	case 'H':
		mySpecialFunction(key, x, y);
		break;
	case 'Z':
	case 'z':
		grow_shrink--;
		resize(500, 500);

		break;
	case 'X':
	case 'x':
		grow_shrink++;
		resize(500, 500);

		break;

	}


	glutPostRedisplay();
}

void specialKeyboard(int key, int x, int y)
{
	if (key == GLUT_KEY_F1)
	{
		fullscreen = !fullscreen;

		if (fullscreen)
			glutFullScreen();
		else
		{
			glutReshapeWindow(500, 500);
			glutPositionWindow(50, 50);
		}
	}
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		mouseDown = 1;

		xdiff = x - yrot;
		ydiff = -y + xrot;
	}
	else
		mouseDown = 0;
}

void mouseMotion(int x, int y)
{
	if (mouseDown)
	{
		yrot = x - xdiff;
		xrot = y + ydiff;

		glutPostRedisplay();
	}
}

int main(int argc, char* argv[])
{
	setRings();
	glutInit(&argc, argv);

	glutInitWindowPosition(50, 50);
	glutInitWindowSize(500, 500);

	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

	glutCreateWindow("GLUT 3D -> Camera / 3D Transformation ");

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialKeyboard);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutReshapeFunc(resize);
	//glutIdleFunc(idle);

	if (!init())
		return 1;

	glutMainLoop();

	return 0;
}