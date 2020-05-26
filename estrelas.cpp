#include <stdlib.h>
#include<GLFW/glut.h>
#include<math.h>
#include <iostream>

using namespace std;

typedef struct {
	float x;
	float y;
} coordenadas_triangulo;

coordenadas_triangulo coordenadas[6];


int quantidade_estrelas;
const double TWO_PI = 6.2831853;
GLdouble theta;


static void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1280, 0, 720);
}


double defineCor() {
	double cor;
	cor = (double)rand() / ((double)RAND_MAX + 1);
	return cor;
}

void geraTriangulos(GLsizei altura, GLuint tamanhoBase, int x) {

	int d = (coordenadas[1].x - coordenadas[2].x) / 2;
	int dp = sqrt(pow(d, 2) + pow(altura * 2, 2));

	glBegin(GL_TRIANGLES);
	glEdgeFlag(GL_FALSE);
	glVertex2f(coordenadas[2].x, coordenadas[2].y);
	glEdgeFlag(GL_TRUE);
	glVertex2f(coordenadas[1].x, coordenadas[1].y);
	glVertex2f(x, coordenadas[1].y + altura);
	glEnd();

	glBegin(GL_TRIANGLES);
	glEdgeFlag(GL_FALSE);
	glVertex2f(coordenadas[1].x, coordenadas[1].y);
	glEdgeFlag(GL_TRUE);
	glVertex2f(coordenadas[0].x, coordenadas[0].y);
	glVertex2f(coordenadas[1].x + (dp), coordenadas[1].y);
	glEnd();

	glBegin(GL_TRIANGLES);
	glEdgeFlag(GL_FALSE);
	glVertex2f(coordenadas[2].x, coordenadas[2].y);
	glEdgeFlag(GL_TRUE);
	glVertex2f(coordenadas[3].x, coordenadas[3].y);
	glVertex2f(coordenadas[2].x - (dp), coordenadas[1].y);
	glEnd();

	glBegin(GL_TRIANGLES);
	glEdgeFlag(GL_FALSE);
	glVertex2f(coordenadas[3].x, coordenadas[3].y);
	glEdgeFlag(GL_TRUE);
	glVertex2f(coordenadas[4].x, coordenadas[4].y);
	glVertex2f(coordenadas[2].x - (dp), coordenadas[4].y);
	glEnd();

	glBegin(GL_TRIANGLES);
	glEdgeFlag(GL_FALSE);
	glVertex2f(coordenadas[4].x, coordenadas[4].y);
	glEdgeFlag(GL_TRUE);
	glVertex2f(coordenadas[5].x, coordenadas[5].y);
	glVertex2f(x, coordenadas[5].y - altura);
	glEnd();

	glBegin(GL_TRIANGLES);
	glEdgeFlag(GL_FALSE);
	glVertex2f(coordenadas[5].x, coordenadas[5].y);
	glEdgeFlag(GL_TRUE);
	glVertex2f(coordenadas[0].x, coordenadas[0].y);
	glVertex2f(coordenadas[5].x + (dp), coordenadas[5].y);
	glEnd();
}

void geraHexagono(GLsizei altura, GLuint tamanhoBase) {

	glColor3f(defineCor(), defineCor(), defineCor());
	glBegin(GL_POLYGON);

	//gera x com valor entre 50 a 1200
	int x = (rand() % 1200) + 50;

	//gera y com valor entre 50 a 700
	int y = (rand() % 700) + 50;

	//recebe os valores das pontas do hexagono para gerar os triangulos
	int coordenadaX;
	int coordenadaY;
	GLint k;

	for (k = 0; k < 6; k++) {
		theta = TWO_PI * k / 6;
		coordenadaX = x + tamanhoBase * cos(theta);
		coordenadaY = y + tamanhoBase * sin(theta);

		coordenadas[k].x = coordenadaX;
		coordenadas[k].y = coordenadaY;

		//gera o hexagono
		glVertex2f(coordenadaX, coordenadaY);
	}
	glEnd();

	geraTriangulos(altura, tamanhoBase, x);

	glFlush();
}

void lineSegment() {
	int quantidade = 0;
	GLuint tamanhoBase;
	GLuint altura;

	for (int quantidade = 0; quantidade < quantidade_estrelas; quantidade++) {
		tamanhoBase = (rand() % 100) + 10;
		altura = sqrt(pow(tamanhoBase, 2) + pow(tamanhoBase / 2, 2));
		geraHexagono(altura, tamanhoBase);
	}
}

int main(int argc, char** argv)
{
	std::cout << "Digite a quantidade de estrelas\n";
	std::cin >> quantidade_estrelas;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1280, 780);
	glutCreateWindow("VP2");
	init();
	glutDisplayFunc(lineSegment);
	glutMainLoop();

	return 0;
}
