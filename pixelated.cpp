#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>

//const float THICKNESS = 15;
const float PI = 3.141592653979;
const float UNADJUSTED_RADIUS = 200;
const float SMALL_RADIUS = (UNADJUSTED_RADIUS / 18); // Since there are 9 rings 
const float SMALL_DIAMETER = SMALL_RADIUS * 2;
const float GAP = SMALL_RADIUS / 3;
const float MAIN_RADIUS = (SMALL_DIAMETER * 8) + (GAP * 8) + SMALL_RADIUS;// 8 rings + 8 gaps + radius of the center
const float WINDOW_WIDTH = (MAIN_RADIUS * 2) + (SMALL_RADIUS / 2);
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
const Point CENTER = { WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 };

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

void drawCircle(Point center, float radius) {
	// The following code makes a circle by creating 360 vertexes, whose locations are calculated by an angle,
	// radius of the circle and the center of the circle
	float theta;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++) {
		theta = getRadian(i);
		glVertex2f((radius * cos(theta)) + center.X, (radius * sin(theta) + center.Y));
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
		drawCircle(miniCenter, SMALL_RADIUS);
	}
}

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT);


	// Draws the main circle
	glColor3f(0.07, 0.07, 0.07);
	drawCircle(CENTER, MAIN_RADIUS);
	
	// Draws the inner most circle
	glColor3f(0.92, 0.79, 0.34);
	drawCircle(CENTER, SMALL_RADIUS);
	
	// Draws the rest of the circle
	for (int i = 0; i < 7; i++) {
		glColor3f(RingColor[i].R, RingColor[i].G, RingColor[i].B);
		drawCirclesOnRing(Rings[i]);
	}
		
	glFlush();
}


void reshape(int width, int height)
{
	glViewport((width - WINDOW_WIDTH) / 2, (height - WINDOW_HEIGHT) / 2, WINDOW_WIDTH, WINDOW_HEIGHT);
	
}
int main(int argc, char** argv) {
	setRings();
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Carpet");
	//glutFullScreen();
	glutKeyboardFunc(handleKeypress);
	glClearColor(0.94, 0.91, 0.87, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0.0,10.0,0.0,10.0,-1.0,1.0);
	glutReshapeFunc(reshape);
	//glOrtho(0.0, 30.0, 0.0, 20.0, -1.0, 1.0);
	glOrtho(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT, -1.0, 1.0);
	//glOrtho(0.0f, glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT), 0.0f, 0.0f, 1.0f);
	glutDisplayFunc(display);
	glutMainLoop();


	return 0;
}

