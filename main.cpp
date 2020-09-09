#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>

const float WINDOW_WIDTH = 1000.0;
const float WINDOW_HEIGHT = 400.0;
const int COLUMNS = 10;
const float BOX_WIDTH = WINDOW_HEIGHT / COLUMNS; // The width of each pixel like box

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

	
};

struct PolygonLocation {
	Point vertices[4];

	PolygonLocation(Point p[4]) {
		for (int i = 0; i < 4; i++)
			vertices[i] = p[i];
	}
	
};

struct Line {
	double slope; 
	double intercept;
};

void drawSquare(Point px, int width) {
	glBegin(GL_POLYGON);

	glVertex2f(px.X, px.Y);
	glVertex2f(px.X + width, px.Y);
	glVertex2f(px.X + width, px.Y + width);
	glVertex2f(px.X, px.Y + width);

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

// Returns the slope made by the two point
double getSlope(Point p1, Point p2) {
	return ((p2.Y - p1.Y) / (p2.X - p1.X));
}

// Returns a line made from two points
Line getLine(Point p1, Point p2) {
	double slope = getSlope(p1, p2);
	double intercept = p1.Y - (slope * p1.X);
	Line ln;
	ln.intercept = intercept;
	ln.slope = slope;
	return ln;
}

// Gets the Y-Coordinate from a line and an X-Coordinate
double getYCoordinate(Line ln, double x) {
	return ((ln.slope * x) + ln.intercept);
}

// Calculates the distance between two points
double getDistance(Point p1, Point p2) {
	double height = abs(p1.Y - p2.Y);
	double width = abs(p1.X -p2.X);

	return (sqrt(pow(height, 2) + pow(width, 2)));
}


void drawPixelatedSquare(PolygonLocation square) {


	glColor3f(0.10, 0.20, 0.11);
	for (int i = 0; i < 4; i++) {
		
		Point current = square.vertices[i];
		if (i != 3) {
			Line ln = getLine(square.vertices[i], square.vertices[i + 1]);
			while (getDistance(current, square.vertices[i+1]) > (BOX_WIDTH / 2))
			{
				int distance = getDistance(current, square.vertices[i + 1]);

				drawSquare(current, BOX_WIDTH);
				if (current.X < square.vertices[i + 1].X)
					current.X += BOX_WIDTH / 2;
				else
					current.X -= BOX_WIDTH / 2;
				current.Y = getYCoordinate(ln, current.X);
			}
		}
		else {
			Line ln = getLine(square.vertices[i], square.vertices[0]);
			while (getDistance(current, square.vertices[0]) > BOX_WIDTH / 2)
			{
				drawSquare(current, BOX_WIDTH);
				if (current.X < square.vertices[0].X)
					current.X += BOX_WIDTH / 2;
				else
					current.X -= BOX_WIDTH / 2;
				current.Y = getYCoordinate(ln, current.X);
			}
		}
	}

	/*
	double jumpFactor = glutGet(GLUT_SCREEN_WIDTH) / 2;
	while (counter < square.vertex2  ) {
		std::cout << "X1: " << counter.X << "  X2: " << square.vertex2.X << std::endl;
		std::cout << "Y1: " << counter.Y << "  Y2: " << square.vertex2.Y << std::endl;

	//	bigSquare(counter, 2);
		counter.X += 0.5;
		counter.Y += 0.5;
	}
	*/
}

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.25, 0.44, 0.57);


	
	// The center point isn't exactly on the center. 
	// The X-axis is centerd 
	// The y-axis is down by half the box size to ensure that the region touches the ceiling 


	// Center big one
	Point center = { WINDOW_WIDTH / 2, (WINDOW_HEIGHT / 2 - (BOX_WIDTH / 2)) };
	double radius = WINDOW_HEIGHT * 0.45;
	Point centerSquare []= {
		{ center.X - radius		, center.Y },
		{ center.X				, center.Y - radius },
		{ center.X + radius		, center.Y },
		{ center.X				, center.Y + radius }
	};
	drawPixelatedSquare(centerSquare);


	// Smaller Center

	radius = WINDOW_HEIGHT * 0.15;
	Point tinySquare[] = {
		{ center.X - radius		, center.Y },
		{ center.X				, center.Y - radius },
		{ center.X + radius		, center.Y },
		{ center.X				, center.Y + radius }
	};
	drawPixelatedSquare(tinySquare);



	// Bottom Left
	center = { WINDOW_WIDTH / 5, -(WINDOW_HEIGHT / 8) };
	radius = WINDOW_HEIGHT * 0.45;
	Point bottomLeft[] = {
		{ center.X - radius		, center.Y },
		{ center.X				, center.Y - radius },
		{ center.X + radius		, center.Y },
		{ center.X				, center.Y + radius }
	};
	drawPixelatedSquare(bottomLeft);

	// Bottom Left Tiny

	radius = WINDOW_HEIGHT * 0.15;
	Point bottomLeftTiny[] = {
		{ center.X - radius		, center.Y },
		{ center.X				, center.Y - radius },
		{ center.X + radius		, center.Y },
		{ center.X				, center.Y + radius }
	};
	drawPixelatedSquare(bottomLeftTiny);


	// Top Left

	center = { WINDOW_WIDTH / 5, (WINDOW_HEIGHT) };
	radius = WINDOW_HEIGHT * 0.45;
	Point topLeft[] = {
		{ center.X - radius		, center.Y },
		{ center.X				, center.Y - radius },
		{ center.X + radius		, center.Y },
		{ center.X				, center.Y + radius }
	};
	drawPixelatedSquare(topLeft);

	// Top Left Tiny

	radius = WINDOW_HEIGHT * 0.15;
	Point topLeftTiny[] = {
		{ center.X - radius		, center.Y },
		{ center.X				, center.Y - radius },
		{ center.X + radius		, center.Y },
		{ center.X				, center.Y + radius }
	};
	drawPixelatedSquare(topLeftTiny);


	// Top Right

	center = { WINDOW_WIDTH * 0.8, (WINDOW_HEIGHT) };
	radius = WINDOW_HEIGHT * 0.45;
	Point topRight[] = {
		{ center.X - radius		, center.Y },
		{ center.X				, center.Y - radius },
		{ center.X + radius		, center.Y },
		{ center.X				, center.Y + radius }
	};
	drawPixelatedSquare(topRight);

	// Top Right Tiny

	radius = WINDOW_HEIGHT * 0.15;
	Point topRightTiny[] = {
		{ center.X - radius		, center.Y },
		{ center.X				, center.Y - radius },
		{ center.X + radius		, center.Y },
		{ center.X				, center.Y + radius }
	};
	drawPixelatedSquare(topRightTiny);



	// Bottom Right
	center = { WINDOW_WIDTH * 0.8, -(WINDOW_HEIGHT / 8) };
	radius = WINDOW_HEIGHT * 0.45;
	Point bottomRight[] = {
		{ center.X - radius		, center.Y },
		{ center.X				, center.Y - radius },
		{ center.X + radius		, center.Y },
		{ center.X				, center.Y + radius }
	};
	drawPixelatedSquare(bottomRight);

	// Bottom Right Tiny

	radius = WINDOW_HEIGHT * 0.15;
	Point bottomRightTiny[] = {
		{ center.X - radius		, center.Y },
		{ center.X				, center.Y - radius },
		{ center.X + radius		, center.Y },
		{ center.X				, center.Y + radius }
	};
	drawPixelatedSquare(bottomRightTiny);


	// Center Left
	center = { -(WINDOW_WIDTH / 8) , (WINDOW_HEIGHT / 2 - (BOX_WIDTH / 2)) };
	radius = WINDOW_HEIGHT * 0.45;
	Point centerLeft[] = {
		{ center.X - radius		, center.Y },
		{ center.X				, center.Y - radius },
		{ center.X + radius		, center.Y },
		{ center.X				, center.Y + radius }
	};
	drawPixelatedSquare(centerLeft);

	
	// Center Right
	center = { (WINDOW_WIDTH * 1.125) , (WINDOW_HEIGHT / 2 - (BOX_WIDTH / 2)) };
	radius = WINDOW_HEIGHT * 0.45;
	Point centerRight[] = {
		{ center.X - radius		, center.Y },
		{ center.X				, center.Y - radius },
		{ center.X + radius		, center.Y },
		{ center.X				, center.Y + radius }
	};
	drawPixelatedSquare(centerRight);
	
	/*
	
	-> Grid Sample <-

	int columns = 20;
	double squareWidth = WINDOW_WIDTH / columns;

	int rows = WINDOW_HEIGHT / squareWidth;
	for (int i = 0; i < columns; i++) {
		for (int j = 0; j < rows; j++){
			if (i % 2 == j % 2) {
				Point pt = { (i * squareWidth), (j * squareWidth) };
				drawSquare(pt, squareWidth);
			}
		}

	}
	*/


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
	glClearColor(0.95, 0.95, 0.95, 0.0);
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

