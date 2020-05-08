#ifndef _SHAPE_
#define _SHAPE_

#include "Dependencies/glew/glew.h"
#include "Dependencies/freeglut/freeglut.h"
#include <math.h>

class Shape {
public:
	GLint *px1, *px2, *py1, *py2;

	Shape() {
		;
	}

	Shape(GLint* _x1, GLint* _x2, GLint* _y1, GLint* _y2) : px1(_x1), px2(_x2), py1(_y1), py2(_y2) {
		if (*px1 > -1 && *px2 > -1 && *py1 > -1 && *py2 > -1) {
			if (*px2 < *px1) {
				GLint *t = px1;
				px1 = px2;
				px2 = t;
			}
			if (*py2 < *py1) {
				GLint *t = py1;
				py1 = py2;
				py2 = t;
			}
		}

	}


	virtual void draw() = 0;

	virtual void drawLastStroke() = 0;

	~Shape() {
		;
	}
};

class Line : public Shape {
public:
	Line(GLint *_x1, GLint *_x2, GLint *_y1, GLint *_y2) : Shape(_x1, _x2, _y1, _y2) {
		;
	}

	void draw() {		
		if (*px1 > -1 && *px2 > -1 && *py1 > -1 && *py2 > -1) {

			GLint x1 = *px1, x2 = *px2, y1 = *py1, y2 = *py2;

			glLineWidth(2.0);
			glBegin(GL_LINES);
			glVertex2i(x1, y1);
			glVertex2i(x2, y2);
			glEnd();

			// MID POINT
			/*GLint x1, x2, y1, y2;


			if (*px1 <= *px2)
				x1 = *px1, x2 = *px2, y1 = *py1, y2 = *py2;
			else
				x1 = *px2, x2 = *px1, y1 = *py2, y2 = *py1;

			GLfloat dx, dy, d, const1, const2;
			GLfloat x, y;

			dx = x2 - x1;
			dy = abs(y2 - y1);
			d = dy - dx / 2;

			x = x1; y = y1;

			glBegin(GL_POINTS);

			glVertex2i(x, y);

			while (x < x2) {
				++x;

				if (d < 0) {
					d = d + dy;
				}
				else {
					d = d + dy - dx;
					if (y2 > y1)
						++y;
					else
						--y;
				}
				glVertex2i(x, y);
			}
			glEnd();*/
		}
	}

	void drawLastStroke() {
		;
	}
};

class Rectanglee : public Shape {
public:
	Rectanglee(GLint* _x1, GLint* _x2, GLint* _y1, GLint* _y2) : Shape(_x1, _x2, _y1, _y2) {
		;
	}

	void draw() {
		if (*px1 > -1 && *px2 > -1 && *py1 > -1 && *py2 > -1) {
			GLint x1, y1, x2, y2;

			if (*px1 <= *px2)
				x1 = *px1, x2 = *px2;
			else
				x1 = *px2, x2 = *px1;

			if (*py1 <= *py2)
				y1 = *py1, y2 = *py2;
			else
				y1 = *py2, y2 = *py1;

			glBegin(GL_POINTS);
			// Ox
			for (GLint x = x1; x <= x2; ++x) {
				glVertex2i(x, y1);
				glVertex2i(x, y2);
			}

			//Oy
			for (GLint y = y1; y <= y2; ++y) {
				glVertex2i(x1, y);
				glVertex2i(x2, y);
			}
			glEnd();

			glFlush();
		}
	}

	void drawLastStroke() {
		;
	}
};

class Circle : public Shape {
private:
	GLfloat cX, cY, radius;

public:
	Circle(GLint* _x1, GLint* _x2, GLint* _y1, GLint* _y2) : Shape(_x1, _x2, _y1, _y2) {
		;
	}

	void draw() {
		if (*px1 > -1 && *px2 > -1 && *py1 > -1 && *py2 > -1) {
			GLint x1 = *px1, x2 = *px2, y1 = *py1, y2 = *py2;

			cX = (x1 + x2) / 2;
			cY = (y1 + y2) / 2;
			radius = sqrt((x2 - cX) * (x2 - cX) + (y2 - cY) * (y2 - cY));

			float x = radius, y = 0, error = 0;

			glBegin(GL_POINTS);

			while (x >= y) {

				glVertex2f(cX + x, cY + y);
				glVertex2f(cX + y, cY + x);
				glVertex2f(cX - y, cY + x);
				glVertex2f(cX - x, cY + y);
				glVertex2f(cX - x, cY - y);
				glVertex2f(cX - y, cY - x);
				glVertex2f(cX + y, cY - x);
				glVertex2f(cX + x, cY - y);

				if (error <= 0) {
					y = y + 1;
					error = error + 2 * y + 1;
				}
				else {
					x = x - 1;
					error = error - 2 * x + 1;
				}
			}
			glEnd();
		}
	}

	void drawLastStroke() {
		;
	}
};

class Ellip : public Shape {
private:
	GLfloat cX, cY, a, b;

public:
	Ellip(GLint* _x1, GLint* _x2, GLint* _y1, GLint* _y2) : Shape(_x1, _x2, _y1, _y2) {
		;
	}

	void draw() {
		if (*px1 > -1 && *px2 > -1 && *py1 > -1 && *py2 > -1) {
			GLint x1 = *px1, x2 = *px2, y1 = *py1, y2 = *py2;

			cX = (x1 + x2) / 2;
			cY = (y1 + y2) / 2;
			a = (x2 - cX) * 2;
			b = (y2 - cY) * 2;

			float x, y, d1, d2, dx, dy;

			x = 0; y = b;

			d1 = b * b - a * a * b + 0.25 * a * a;

			dx = 2 * b * b * x;
			dy = 2 * a * a * y;

			glBegin(GL_POINTS);

			while (dx < dy) {
				glVertex2i(x + cX, y + cY);
				glVertex2i(-x + cX, y + cY);
				glVertex2i(x + cX, -y + cY);
				glVertex2i(-x + cX, -y + cY);

				if (d1 < 0) {
					dx += 2 * b * b;
					d1 += dx + b * b;
				}
				else {
					--y;
					dx += +2 * b * b;
					dy -= 2 * a * a;
					d1 += dx - dy + b * b;
				}
				++x;
			}

			d2 = (b * b) * (x + 0.5) * (x + 0.5) + (a * a) * (y - 1) * (y - 1) - a * a * b * b;

			while (y >= 0) {
				glVertex2i(x + cX, y + cY);
				glVertex2i(-x + cX, y + cY);
				glVertex2i(x + cX, -y + cY);
				glVertex2i(-x + cX, -y + cY);

				if (d2 > 0) {
					dy -= 2 * a * a;
					d2 += a * a - dy;
				}
				else {
					++x;
					dx += 2 * b * b;
					dy -= 2 * a * a;
					d2 += dx - dy + a * a;
				}
				--y;
			}

			glEnd();
		}
	}

	void drawLastStroke() {
		;
	}
};

class Polygonn : public Shape {
public:
	GLint sX, sY, mX, mY, eX, eY;

	Polygonn(GLint* _x1, GLint* _x2, GLint* _y1, GLint* _y2) : Shape(_x1, _x2, _y1, _y2) {
		mX = -1;
		mY = -1;
	}

	void draw() {
		if (*px1 > -1 && *px2 > -1 && *py1 > -1 && *py2 > -1) {

			if (mX == -1) {
				mX = *px1;
				sX = mX;
			}
			if (mY == -1) {
				mY = *py1;
				sY = mY;
			}
			eX = *px2, eY = *py2;
			
			glLineWidth(2.0);
			glBegin(GL_LINES);
			glVertex2i(mX, mY);
			glVertex2i(eX, eY);
			glEnd();
			mX = eX;
			mY = eY;
		}
	}

	void drawLastStroke() {
		glLineWidth(2.0);
		glBegin(GL_LINES);
		glVertex2i(sX, sY);
		glVertex2i(eX, eY);
		glEnd();
	}
};

#endif // !_SHAPE_
