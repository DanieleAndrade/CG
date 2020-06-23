// OpenGL.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include<GLFW/glut.h>
#include<Windows.h>
#include <ctime>
#include <stdlib.h>

using namespace std;
int OffsetX = 0, OffsetY = 0;
float R = 0, G = 0, B = 1;
GLint V = 50, Ang = 0;
GLint DesLoca = -100;
float scaleX, scaleY;

void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-400, 400, -400, 400);

}


void lineSegment(void) {

	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//
	//Traça eixos X e Y
	glColor3f(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2i(0, -400);
	glVertex2i(0, 400);
	glVertex2i(-400, 0);
	glVertex2i(400, 0);
	glEnd();

	//gera retângulo da casa
	glColor3f(0, 0, 1);
	glRecti(50, 100, 100, 150);
	//ger triângulo da casa
	glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(50, 150);
	glVertex2f(100, 150);
	glVertex2f(75, 175);
	glEnd();

	//desenha casa redimensionada
	glLoadIdentity();
	glColor3f(0, 0, 1);
	glScalef(scaleX, scaleY, 1.0);
	glRecti(50, 100, 100, 150);

	glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(50, 150);
	glVertex2f(100, 150);
	glVertex2f(75, 175);
	glEnd();

	glFlush();

}

void Teclado(unsigned char key, int x, int y)
{
	if (key == 27) {
		exit(0);
	};
};

void Anima(int value);

// Chamada quando uma tecla especial eh pressionada
void specialKey(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		V = V + 1;
		break;
	case GLUT_KEY_DOWN:
		V = V - 1;
		if (V <= 0) { V = 1; };
		break;
	};
	cout << V << endl;
};

void mouseFunc(int button, int state, int x, int y) {

	srand(time(NULL));
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		B = (double)rand() / (double)RAND_MAX;
		R = (double)rand() / (double)RAND_MAX;
		G = (double)rand() / (double)RAND_MAX;
		glutPostRedisplay();
	};
}

void Anima(int value)
{

	DesLoca = DesLoca + 10;
	if (DesLoca < 250) { glutTimerFunc(1000, Anima, 1); }
	glutPostRedisplay();

}


// Programa Principal 
int main(int argc, char** argv)
{

	std::cout << "Informe a escala de redimensionamento do eixo X \n";
	std::cin >> scaleX;
	std::cout << "Informe a escala de redimensionamento do eixo Y \n";
	std::cin >> scaleY;

	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("REDIMENSIONAMENTO COM REFLEXÃO - Daniele");
	init();
	glutDisplayFunc(lineSegment);
	glutTimerFunc(V, Anima, 1);
	glutKeyboardFunc(Teclado);
	glutSpecialFunc(specialKey);
	glutMouseFunc(mouseFunc);
	glutMainLoop();

	return 0;

}
