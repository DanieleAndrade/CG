
#include <windows.h>
#include <GL/glew.h>
#include <GLFW/glut.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <array>
#include <time.h>


GLfloat angle, fAspect;
GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;
int x_ini, y_ini, bot;

using namespace std;

void Desenha(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0f, 0.0f, 0.0f);

	glBegin(GL_LINE_LOOP);
	glVertex3f(-1, 0, -1); 
	glVertex3f(-1, 0, 1); 
	glVertex3f(1, 0, 1); 
	glVertex3f(1, 0, -1); 
	glEnd();
	
	glBegin(GL_LINE_LOOP);
	glVertex3f(-1, 0, 1);
	glVertex3f(-1, 2, 1);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-1, 0, -1);
	glVertex3f(-1, 2, -1);
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(1, 0, 1);
	glVertex3f(1, 2, 1);
	glEnd();
	
	glBegin(GL_LINE_LOOP);
	glVertex3f(1, 0, -1); 
	glVertex3f(1, 2, -1); 
	glEnd();

	glBegin(GL_LINE_LOOP);
	glVertex3f(-1, 2, -1); 
	glVertex3f(-1, 2, 1);
	glVertex3f(1, 2, 1);
	glVertex3f(1, 2, -1); 
	glEnd();

	glFlush();
}

void PosicionaObservador(void)
{

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-obsX, -obsY, -obsZ);
	glRotatef(rotX, 1, 0, 0);
	glRotatef(rotY, 0, 1, 0);
}

void EspecificaParametrosVisualizacao(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle, fAspect, 0.1, 1200);

	PosicionaObservador();
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	if (h == 0) h = 1;
	glViewport(0, 0, w, h);

	fAspect = (GLfloat)w / (GLfloat)h;

	EspecificaParametrosVisualizacao();
}

void Teclado(unsigned char tecla, int x, int y)
{
	if (tecla == 27)
	{
		exit(0);
	}
}

void TeclasEspeciais(int tecla, int x, int y)
{
	switch (tecla)
	{
	case GLUT_KEY_HOME:	if (angle >= 10)  angle -= 5;
		break;
	case GLUT_KEY_END:	if (angle <= 150) angle += 5;
		break;
	case GLUT_KEY_UP:
		fAspect = fAspect + 0.01;
		break;
	case GLUT_KEY_DOWN:
		fAspect = fAspect - 0.01;
		break;
	case GLUT_KEY_RIGHT:
		obsX = obsX + 0.1;
		obsY = obsY + 0.1;
		break;

	case GLUT_KEY_LEFT:
		obsX = obsX - 0.1;
		obsY = obsY - 0.1;

		break;
	};
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();


}

void GerenciaMouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		x_ini = x;
		y_ini = y;
		obsX_ini = obsX;
		obsY_ini = obsY;
		obsZ_ini = obsZ;
		rotX_ini = rotX;
		rotY_ini = rotY;
		bot = button;
	}
	else bot = -1;
}

#define SENS_ROT	5.0
#define SENS_OBS	15.0
#define SENS_TRANSL	30.0
void GerenciaMovim(int x, int y)
{
	
	if (bot == GLUT_LEFT_BUTTON)
	{
	
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		
		rotY = rotY_ini - deltax / SENS_ROT;
		rotX = rotX_ini - deltay / SENS_ROT;
	}

	else if (bot == GLUT_RIGHT_BUTTON)
	{
		
		int deltaz = y_ini - y;
		
		obsZ = obsZ_ini + deltaz / SENS_OBS;
	}
	
	else if (bot == GLUT_MIDDLE_BUTTON)
	{
		
		int deltax = x_ini - x;
		int deltay = y_ini - y;
		
		obsX = obsX_ini + deltax / SENS_TRANSL;
		obsY = obsY_ini - deltay / SENS_TRANSL;
	}
	PosicionaObservador();
	glutPostRedisplay();
}


void Inicializa(void)
{
	
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	angle = 60;

	rotX = 0;
	rotY = 0;
	obsX = obsY = 0;
	obsZ = 5;
}


int main(void)
{
	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowPosition(5, 5);

	glutInitWindowSize(450, 450);

	glutCreateWindow("Cubo - Daniele");

	glutDisplayFunc(Desenha);

	glutReshapeFunc(AlteraTamanhoJanela);

	glutMouseFunc(GerenciaMouse);

	glutMotionFunc(GerenciaMovim);

	glutKeyboardFunc(Teclado);

	glutSpecialFunc(TeclasEspeciais);

	Inicializa();

	glutMainLoop();

	return 0;
}
