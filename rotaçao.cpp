
#include <stdlib.h>
#include<iostream>
#include <GLFW/glut.h>

using namespace std;

GLfloat Ang;
GLint Dir, V;
const int ENTER = 13;
const int ESC = 27;


void Desenha(void)
{

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);

	glRotatef(Ang, 0.0f, 0.0f, 1.0f);
	glColor3f(0, 0, 1);
	
	glBegin(GL_QUADS);
	glVertex2f(15.0f, -15.0f);
	glVertex2f(15.0f, 1.0f);
	glVertex2f(30.0f, 1.0f);
	glVertex2f(30.0f, -15.0f);
	glEnd();

	glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLES);
	glVertex2f(15.0f, 1.0f);
	glVertex2f(22.0f, 12.0f);
	glVertex2f(30.0f, 1.0f);
	glEnd();


	glutSwapBuffers();
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	GLsizei largura, altura;
	if (h == 0) h = 1;

	cout << w << endl;
	cout << h << endl;
	largura = w;
	altura = h;

	glViewport(0, 0, largura, altura);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (largura <= altura)
		gluOrtho2D(-50.0f, 50.0f, -50.0f * altura / largura, 50.0f * altura / largura);
	else
		gluOrtho2D(-50.0f * largura / altura, 50.0f * largura / altura, -50.0f, 50.0f);
}
void Anima(int value)
{
	Ang = Ang + Dir;
	glutPostRedisplay();
	glutTimerFunc(V, Anima, 1);
}


void Teclado(unsigned char key, int x, int y)
{
	cout << char(key);
	if (key == ESC)
		exit(0);
	if (key == ENTER) {
		Dir = Dir * -1;
		V = V - 10;
		glutTimerFunc(V, Anima, 1);
	}

}

void Inicializa(void)
{

	glClearColor(1, 1, 1, 1);
	Ang = 0;
	Dir = 10;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-50.0f, 50.0f, -50.0f, 50.0f);

}

// Programa Principal 
int main(void)
{
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	V = 1000;
	glutInitWindowPosition(5, 5);
	glutInitWindowSize(450, 450);

	glutCreateWindow("Rotação - Daniele");

	glutDisplayFunc(Desenha);
	glutTimerFunc(V, Anima, 1);
	glutKeyboardFunc(Teclado);
	Inicializa();
	glutMainLoop();

	return 0;
}
