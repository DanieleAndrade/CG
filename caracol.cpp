// OpenGL.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include<GLFW/glut.h>
#include<Windows.h>
#include<math.h>

using namespace std;
int xInicial, yInicial, xFinal, yFinal;
const double TWO_PI = 6.2831853;
GLuint baseInicial = 300;
GLuint wTamPad;
GLdouble theta;

void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, 1280, 0, 680);

}

void DesenhaLinha(int XI, int YI, int XE, int YE) {

	int Dx = XE - XI;
	int Dy = YE - YI;
	int steps, k;

	float xIncrement, yIncrement, x = XI, y = YI;

	if (fabs(Dx) > fabs(Dy))
	{
		steps = fabs(Dx);
	}
	else
	{
		steps = fabs(Dy);
	};

	xIncrement = float(Dx) / steps;
	yIncrement = float(Dy) / steps;

	glBegin(GL_POINTS);
	glVertex2i(round(x), round(y));
	glEnd();

	for (k = 0; k < steps; k++)
	{
		x += xIncrement;
		y += yIncrement;
		glBegin(GL_POINTS);
		glVertex2i(round(x), round(y));
		glEnd();
	};

	glFlush();
}

void lineSegment(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0.4, 0.5);

	GLint i;
	wTamPad = 300;
	int linhas = 150;
	xInicial = 640;
	yInicial = 340;

	for (i = 0; i < linhas; i++) {
		theta = TWO_PI * i / linhas;
		xFinal = xInicial + wTamPad * cos(theta);
		yFinal = yInicial + wTamPad * sin(theta);

		wTamPad = wTamPad - (baseInicial / linhas);
		
		DesenhaLinha(xInicial, yInicial, xFinal, yFinal);
	}

	
}

// Programa Principal 
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Hello Word, Daniele!");
	init();
	glutDisplayFunc(lineSegment);
	glutMainLoop();

	return 0;

}
