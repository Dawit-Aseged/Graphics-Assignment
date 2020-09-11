#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>

const float THICKNESS = 20;
const float WINDOW_WIDTH = THICKNESS * 68;
const float WINDOW_HEIGHT = THICKNESS * 38;

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

void drawBar(Point bottomLeft, Point topRight) {
	glBegin(GL_POLYGON);

	glVertex2d(bottomLeft.X, bottomLeft.Y);
	glVertex2d(bottomLeft.X + (topRight.X - bottomLeft.X), bottomLeft.Y);
	glVertex2d(bottomLeft.X + (topRight.X - bottomLeft.X), topRight.Y);
	glVertex2d(bottomLeft.X, topRight.Y);

	glEnd();
}

void drawRectangle(Point bottomLeft, Point topRight, float width) {

	Point barV1 = { bottomLeft.X, bottomLeft.Y };
	Point barV2 = { bottomLeft.X + width, topRight.Y };

	drawBar(barV1, barV2);

	barV1 = { bottomLeft.X, topRight.Y - width };
	barV2 = { topRight.X, topRight.Y };

	drawBar(barV1, barV2);

	barV1 = { topRight.X - width, topRight.Y };
	barV2 = { topRight.X, bottomLeft.Y };

	drawBar(barV1, barV2);

	barV1 = { bottomLeft.X, bottomLeft.Y };
	barV2 = { topRight.X, bottomLeft.Y + width };

	drawBar(barV1, barV2);

	
}

void handleKeypress(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
	}
}

void drawDownRight(Point pt) {
	Point barV1 = { pt.X, pt.Y };
	Point barV2 = { pt.X + THICKNESS, pt.Y + (THICKNESS * 3) };
	drawBar(barV1, barV2);

	barV2 = { pt.X + (THICKNESS * 4), pt.Y + THICKNESS };
	drawBar(barV1, barV2);
}

void drawRightDown(Point pt) {

	
	Point barV1 = { pt.X, pt.Y };
	Point barV2 = { pt.X + (THICKNESS * 4), pt.Y + THICKNESS };
	drawBar(barV1, barV2);

	barV1 = { barV2.X - THICKNESS, barV2.Y - (THICKNESS * 3) };
	drawBar(barV1, barV2);
}

void drawUpRight(Point pt) {
	
	Point barV1 = { pt.X, pt.Y };
	Point barV2 = { pt.X + THICKNESS, barV1.Y + (THICKNESS * 4) };
	drawBar(barV1, barV2);

	barV1 = barV2 - THICKNESS;
	barV2 = { barV2.X + (THICKNESS * 2), barV2.Y };
	drawBar(barV1, barV2);

}

void drawRightUp(Point pt) {
	Point barV1 = { pt.X, pt.Y };
	Point barV2 = { pt.X + (THICKNESS * 3), pt.Y + THICKNESS };
	drawBar(barV1, barV2);
	
	barV1 = barV2 - THICKNESS;
	barV2 = { barV2.X, barV2.Y + (THICKNESS * 3) };
	drawBar(barV1, barV2);


}
void display(void) {

	glClear(GL_COLOR_BUFFER_BIT);


	glColor3f(0.29, 0.25, 0.25);
	
	Point bottomLeftBorder = { 0 ,0 };
	Point topRightBorder = { WINDOW_WIDTH, WINDOW_HEIGHT };
	drawRectangle(bottomLeftBorder, topRightBorder, THICKNESS);

	glColor3f(0.94, 0.91, 0.87);
	Point bottomLeftInnerBorder = bottomLeftBorder + (THICKNESS * 3);
	Point topRightInnerBorder = { WINDOW_WIDTH - bottomLeftInnerBorder.X, WINDOW_HEIGHT - bottomLeftInnerBorder.Y };
	drawRectangle(bottomLeftInnerBorder, topRightInnerBorder, THICKNESS);

	Point innerBottom = bottomLeftInnerBorder + THICKNESS + THICKNESS / 2;
	Point innerTop = { WINDOW_WIDTH - innerBottom.X, WINDOW_HEIGHT - innerBottom.Y };
	
	int innerThick = 5 * THICKNESS;
	drawRectangle(innerBottom, innerTop, innerThick);

	// Primary L shape on the bottom left corner
	glColor3f(0.18, 0.15, 0.14);
	Point barV1 = innerBottom + THICKNESS;
	Point barV2 = { barV1.X + THICKNESS, barV1.Y + innerThick };
	drawBar(barV1, barV2);

	barV2 = { barV1.X + (THICKNESS * 3), barV1.Y + THICKNESS };
	drawBar(barV1, barV2);

	// Making the missing part of T on the bottom left
	
	barV1 = innerBottom + (THICKNESS * 3);
	barV2 = { barV1.X + (THICKNESS * 2), barV1.Y + THICKNESS };
	drawBar(barV1, barV2);
	
	for (int i = 0; i < 4; i++) {
		/*
		This loop draws the following figures on the right side
			1. _____		2.	|
				    |			|________
		*/
		drawDownRight({ innerBottom.X + THICKNESS, innerBottom.Y + (THICKNESS * ((6 * i) + 5)) });
		if(i != 3)
			drawRightDown({ innerBottom.X, innerBottom.Y + (THICKNESS * ((6 * i) + 9)) });
	}
	for (int i = 0; i < 9; i++) {
		/*
		This loop draws the following figures on the top side
			1.	 _____			2.		
				|						|
				|						|
				|				   _____|	
		*/
		drawUpRight({ innerBottom.X + (THICKNESS * ((6 * i) + 1)), innerTop.Y - (THICKNESS * 5) });
		drawRightUp({ innerBottom.X + (THICKNESS * ((6 * i) + 3)), innerTop.Y - (THICKNESS * 4) });
	}
	
	// Makes the missing part of T - Top Right
	barV1 = { innerTop.X - (THICKNESS * 5), innerTop.Y - (THICKNESS * 4) };
	barV2 = { barV1.X + (THICKNESS * 2), barV1.Y + THICKNESS };
	drawBar(barV1, barV2);


	// Making the weird L shape on the top right corner
	barV1 = { innerTop.X - (THICKNESS * 4), innerTop.Y - (THICKNESS * 2) };
	barV2 = innerTop - THICKNESS;
	drawBar(barV1, barV2);
	
	barV1 = { barV2.X - THICKNESS, barV2.Y - (THICKNESS * 4) };
	drawBar(barV1, barV2);
	
	for (int i = 0; i < 4; i++) {
		// This loop draws the left side of the mat
		drawRightDown({ innerTop.X - (THICKNESS * 5), innerTop.Y - (THICKNESS * ((6 * i) + 6)) });
		if (i != 3)
			drawDownRight({ innerTop.X - (THICKNESS * 4), innerTop.Y - (THICKNESS * ((6 * i) + 10)) });
	}

	for (int i = 0; i < 9; i++) {
		drawRightUp({ innerBottom.X + (THICKNESS * ((6 * i) + 7)), innerBottom.Y + THICKNESS });
		drawUpRight({ innerBottom.X + (THICKNESS * ((6 * i) + 5)), innerBottom.Y });
	}
	glFlush();
}


void reshape(int width, int height)
{
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Carpet");
	//glutFullScreen();
	glutKeyboardFunc(handleKeypress);
	glClearColor(0.18, 0.15, 0.14, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0.0,10.0,0.0,10.0,-1.0,1.0);
	//glutReshapeFunc(reshape);
	//glOrtho(0.0, 30.0, 0.0, 20.0, -1.0, 1.0);
	glOrtho(0.0, WINDOW_WIDTH, 0.0, WINDOW_HEIGHT, -1.0, 1.0);
	//glOrtho(0.0f, glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT), 0.0f, 0.0f, 1.0f);
	glutDisplayFunc(display);
	glutMainLoop();


	return 0;
}

