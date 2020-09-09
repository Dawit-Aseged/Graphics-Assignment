#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>

const float WINDOW_WIDTH = 800.0;
const float WINDOW_HEIGHT = 600.0;
const double PIXEL_WIDTH = 0.5;

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

	bool operator < (Point p) {
		if (X < p.X )
			return true;
		else
			return false;
	}
	
};

struct PolygonLocation {
	Point vertex1;
	Point vertex2;
	Point vertex3;
	Point vertex4;

	
};

void drawPixel(Point px) {
	glBegin(GL_POLYGON);

	glVertex2f(px.X, px.Y);
	glVertex2f(px.X + PIXEL_WIDTH, px.Y);
	glVertex2f(px.X + PIXEL_WIDTH, px.Y + PIXEL_WIDTH);
	glVertex2f(px.X, px.Y + PIXEL_WIDTH);

	glEnd();
}
//MegaPixel get
void handleKeypress(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
	}
}

void Rectangle(double bottomLeftVertexX, double bottomLeftVertexY, double topRightVertexX, double topRightVertexY)
{
	double x1 = bottomLeftVertexX;
	double y1 = bottomLeftVertexY;
	double x2 = topRightVertexX;
	double y2 = topRightVertexY;


	glBegin(GL_POLYGON);
	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
	glEnd();
}

void FourSidedPolygon(double blx, double bly, double brx, double bry, double tlx, double tly, double trx, double Try)
{
	glBegin(GL_POLYGON);
	glVertex2f(blx, bly);
	glVertex2f(brx, bry);
	glVertex2f(tlx, tly);
	glVertex2f(trx, Try);
	glEnd();
}

void squiglyLine(double x, double y)
{
	Rectangle(0.5 + x, 1.5 + y, 2.0 + x, 7.0 + y);
	Rectangle(2.0 + x, 7.0 + y, 7.0 + x, 5.5 + y);
	Rectangle(5.5 + x, 3.5 + y, 7.0 + x, 7.0 + y);
	Rectangle(2.5 + x, 3.5 + y, 5.5 + x, 5.0 + y);
	Rectangle(2.5 + x, 1.5 + y, 4.0 + x, 4.5 + y);
	Rectangle(2.5 + x, 3.0 + y, 9.0 + x, 1.5 + y);
	Rectangle(7.5 + x, 3.0 + y, 9.0 + x, 7.0 + y);
	/*
	//For an elongated squigly line
	Rectangle(x+0.5, 9.5-y, x+2.0, 15.0-y);
	Rectangle(x+1.0, 13.5-y, x+8.0, 15.0-y);
	Rectangle(x+6.5, 12.0-y, x+8.0, 15.0-y);
	Rectangle(x+3.0, 11.5-y, x+8.0, 13.0-y);
	Rectangle(x+2.5, 9.5-y, x+4.0, 13.0-y);
	Rectangle(x+3.0, 9.5-y, x+10.0, 11.0-y);
	Rectangle(x+8.5, 10.0-y, x+10.0, 15.0-y);
	*/
}

void inverseSquiglyLine(double x, double y)
{
	Rectangle(0.5 + x, 1.5 + y, 2.0 + x, 7.0 + y);
	Rectangle(0.5 + x, 1.5 + y, 7.0 + x, 3.0 + y);
	Rectangle(5.5 + x, 3.0 + y, 7.0 + x, 5.0 + y);
	Rectangle(2.5 + x, 3.5 + y, 7.0 + x, 5.0 + y);
	Rectangle(2.5 + x, 5.0 + y, 4.0 + x, 7.0 + y);
	Rectangle(4.0 + x, 5.5 + y, 9.0 + x, 7.0 + y);
	Rectangle(7.5 + x, 1.5 + y, 9.0 + x, 7.0 + y);
}

void bigSquare(Point p, int width) {
	for (int i = 0; i < width ; i++) {
		for (int j = 0; j < width ; j++) {
			Point px = { p.X + (i * PIXEL_WIDTH), p.Y + (j * PIXEL_WIDTH) };
			drawPixel(px);
		}
	}
}

void drawPixelatedSquare(PolygonLocation square) {
	Point counter = square.vertex1;
	double jumpFactor = glutGet(GLUT_SCREEN_WIDTH) / 2;
	while (counter < square.vertex2  ) {
		std::cout << "X1: " << counter.X << "  X2: " << square.vertex2.X << std::endl;
		std::cout << "Y1: " << counter.Y << "  Y2: " << square.vertex2.Y << std::endl;

		bigSquare(counter, 2);
		counter.X += 0.5;
		counter.Y += 0.5;
	}
}

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.25, 0.44, 0.57);


	//Rectangle(6.0, 4.5, 7.5, 1.5);
	double width = glutGet(GLUT_SCREEN_WIDTH);
	double height = glutGet(GLUT_SCREEN_HEIGHT);

	Point vertex1 = { width * 0.25, height * 0.5 };
	Point vertex2 = { width * 0.5, height * 0.75 };
	Point vertex3 = { width * 0.75, height * 0.5 };
	Point vertex4 = { width * 0.5, height * 0.25 };

//	drawPixelatedSquare({ vertex1, vertex2, vertex3, vertex4 });
	
	//bigSquare(10, 10, 15);
	
	double bigPixelWidth = 2;
	int count = 0;
	while((count * bigPixelWidth - 20) <= width) {
		
		for (int j = 0; j < height / 100; j++) {
			Point px = { count * bigPixelWidth, j * bigPixelWidth };
			if (count % 2 == j % 2) {
				glColor3f(0.25, 0.44, 0.57);
				bigSquare(px, bigPixelWidth * 2);
			}
			else {
				glColor3f(0.99, 0.44, 0.66);
				bigSquare(px, bigPixelWidth * 2);
			}
				
				//drawPixel(px);
		}
		count++;
		
	}
	std::cout << "Count:- " << count << std::endl;
	/*

	glBegin(GL_TRIANGLES);

	glVertex2f(0.0f, 600.0f);
	glVertex2f(800.0f, 600.0f);
	glVertex2f(400.0f, 0.0f);
	
	glEnd();
	*/
	/*
	squiyLine(0, 6);
	squiglyLine(7, 6);
	squiglyLine(14, 6);
	squiglyLine(21, 6);
	Rectangle(0.5, 7.0, 2.0, 8.5);//Spacer between first squigly lines
	inverseSquiglyLine(0, 0);
	inverseSquiglyLine(7, 0);
	inverseSquiglyLine(14, 0);
	inverseSquiglyLine(21, 0);
	*/
	//squiglyLine(0,6.5);
	//squiglyLine(8,0);
	//squiglyLine(8,6.5);
	//squiglyLine(16,0);
	//squiglyLine(16, 6.5);




	glFlush();
}

void reshape(int width, int height)
{
	glViewport(0, 0, 800, 400);
	
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Carpet");
	//glutFullScreen();
	glutKeyboardFunc(handleKeypress);
	glClearColor(0.95, 0.95, 0.95, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0.0,10.0,0.0,10.0,-1.0,1.0);
	//glutReshapeFunc(reshape);
	glOrtho(0.0, 30.0, 0.0, 20.0, -1.0, 1.0);
	//glOrtho(0.0, WINDOW_WIDTH, WINDOW_HEIGHT, 0.0, -1.0, 1.0);
	//glOrtho(0.0f, glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT), 0.0f, 0.0f, 1.0f);
	glutDisplayFunc(display);
	glutMainLoop();


	return 0;
}

