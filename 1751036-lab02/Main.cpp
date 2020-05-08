
#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"

#include <iostream>

#include "RGBColor.h"
#include "Shape.h"

#define WIDTH 1024
#define HEIGHT 720
#define MAX_STACK_CALL 1000

// Global variables
int colorType;
bool isDrawing, startDraw, polygonOn;
int* startX = new int, * startY = new int, * endX = new int, * endY = new int;
int* canvasX1 = new int, * canvasX2 = new int, * canvasY1 = new int, * canvasY2 = new int;
Shape* currentShape = NULL;


RGBColor GetPixel(GLint x, GLint y) {
	unsigned char* ptr = new unsigned char[3];

	glReadPixels(x, HEIGHT - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, ptr);

	RGBColor color;
	color.r = ptr[0];
	color.g = ptr[1];
	color.b = ptr[2];

	delete ptr;

	return color;
}

bool IsSameColor(RGBColor curr, RGBColor other) {
	if (curr.r == other.r && curr.g == other.g && curr.b == other.b) {
		return true;
	}
	return false;
}

void setPixel(GLint x, GLint y, RGBColor color) {
	unsigned char* ptr = new unsigned char[3];

	ptr[0] = color.r;
	ptr[1] = color.g;
	ptr[2] = color.b;

	glRasterPos2i(x, y);
	glDrawPixels(1, 1, GL_RGB, GL_UNSIGNED_BYTE, ptr);

	glFlush();
}

void setIsDrawing(bool draw) {
	isDrawing = draw;
}

void setStartDraw(bool sDraw) {
	startDraw = sDraw;
}

void boundaryFill(int x, int y, RGBColor F_Color, RGBColor B_Color, int count) {
	if (count >= MAX_STACK_CALL) return;

	++count;
	RGBColor currentColor;
	currentColor = GetPixel(x, y);

	if (!IsSameColor(currentColor, F_Color) && !IsSameColor(currentColor, B_Color)) {
		setPixel(x, y, F_Color);

		boundaryFill(x + 1, y, F_Color, B_Color, count);
		boundaryFill(x - 1, y, F_Color, B_Color, count);
		boundaryFill(x, y + 1, F_Color, B_Color, count);
		boundaryFill(x, y - 1, F_Color, B_Color, count);
		boundaryFill(x + 1, y + 1, F_Color, B_Color, count);
		boundaryFill(x - 1, y - 1, F_Color, B_Color, count);
		boundaryFill(x - 1, y + 1, F_Color, B_Color, count);
		boundaryFill(x + 1, y - 1, F_Color, B_Color, count);
	}
}

void brushing(int button, int state, int x, int y) {

	RGBColor F_Color = { colorPallete[colorType].r, colorPallete[colorType].g, colorPallete[colorType].b };

	RGBColor B_Color = { colorPallete[colorIndex(WHITE)].r, colorPallete[colorIndex(WHITE)].g, colorPallete[colorIndex(WHITE)].b };

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !isDrawing) {
		boundaryFill(x, y, F_Color, B_Color, 0);
		startDraw = false;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && isDrawing) {
		setStartDraw(true);
		*startX = x;
		*startY = y;
	}

	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP && isDrawing) {
		setStartDraw(false);
		*endX = x;
		*endY = y;
		currentShape->draw();
		if (!polygonOn)
			*startX = *startY = *endX = *endY = -1;
	}
}


void drawing(int x, int y) {
	if (startDraw && !polygonOn) {
		*endX = x;
		*endY = y;

		currentShape->draw();
	}

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		if (polygonOn) {
			currentShape->drawLastStroke();
			glutPostRedisplay();
			*startX = *startY = *endX = *endY = -1;
			delete currentShape;
			currentShape = new Polygonn(startX, endX, startY, endY);
		}

		break;
	}
}

void render(void) {
	glPointSize(2.0);
	glColor3ub(colorPallete[colorIndex(WHITE)].r, colorPallete[colorIndex(WHITE)].g, colorPallete[colorIndex(WHITE)].b);

	*canvasX1 = 0, * canvasX2 = 1024, * canvasY1 = 0, * canvasY2 = 720;
	Shape* rec = new Rectanglee(canvasX1, canvasX2, canvasY1, canvasY2);
	rec->draw();
	glFlush();
}

void mainMenuHandler(int choice) {
	if (currentShape) delete currentShape;

	switch (choice) {
	case 0:
		currentShape = new Line(startX, endX, startY, endY);
		polygonOn = false;
		setIsDrawing(true);
		break;
	case 1:
		currentShape = new Rectanglee(startX, endX, startY, endY);
		polygonOn = false;
		setIsDrawing(true);
		break;
	case 2:
		currentShape = new Circle(startX, endX, startY, endY);
		polygonOn = false;
		setIsDrawing(true);
		break;
	case 3:
		currentShape = new Ellip(startX, endX, startY, endY);
		polygonOn = false;
		setIsDrawing(true);
		break;
	case 4:
		currentShape = new Polygonn(startX, endX, startY, endY);
		polygonOn = true;
		setIsDrawing(true);
		break;
	case 6:	// Exit
		delete startX, startY, endX, endY, canvasX1, canvasX2, canvasY1, canvasY2, currentShape;
		exit(0);
		break;
	}
}

void colorMenuHandler(int choice) {
	colorType = choice;
	setIsDrawing(false);
}

void prepareMenu() {

	int tomau = glutCreateMenu(colorMenuHandler);
	for (int i = 0; i < colorName.size(); ++i) {
		glutAddMenuEntry(colorName[i].c_str(), i);
	}

	glutCreateMenu(mainMenuHandler);
	glutAddMenuEntry("Straight line", 0);
	glutAddMenuEntry("Rectangle", 1);
	glutAddMenuEntry("Circle", 2);
	glutAddMenuEntry("Ellipse", 3);
	glutAddMenuEntry("Polygon", 4);
	glutAddSubMenu("Paint", tomau);
	glutAddMenuEntry("Exit", 6);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(10, 10);
    glutInitWindowSize(WIDTH, HEIGHT);

	glewInit();

    glutCreateWindow("AnhThu Painter");
	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WIDTH, HEIGHT, 0);

	glClearColor(colorPallete[colorIndex(WHITE)].r, colorPallete[colorIndex(WHITE)].g, colorPallete[colorIndex(WHITE)].b, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

    glutDisplayFunc(render);

	currentShape = new Line(startX, endX, startY, endY);
	setIsDrawing(true);
	setStartDraw(false);
	polygonOn = false;

	prepareMenu();
    glutMouseFunc(brushing);
	glutPassiveMotionFunc(drawing);
	glutKeyboardFunc(keyboard);

    glutMainLoop();
    return 0;
}