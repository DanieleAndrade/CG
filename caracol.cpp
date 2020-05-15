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
	// Três primeiros argumentos corresponde a valores normalizados de R, G e B. O último parâmetro
	// é o "alpha value" que é utilzado para "blend operations", ou seja, determinar a cor resultante de dois
	// objetos que se sobrepõem.
	glClearColor(1.0, 1.0, 1.0, 0);
	// Nesse primeiro programa, será mostrada uma linha em duas dimensões em tela. Para tanto,
	// é necessário "dizer" ao OpenGL como projetar nossa figura na tela, pois projetar uma figura bi-dimensional
	// é tratado pelo OpenGL como um caso especial de uma visualização tridimensional. Os dois próximos comandos
	// especificam que será utilizado uma projeção ortogonal (projeção de uma figura no espaço em um plano) para
	// mapear o conteudo de uma área bidimensional retangular para a tela, sendo que a coordenada "x" variará de 0 a 200
	// e a "y" de 0 a 150. Dessa forma, define-se a coordenada "lower left-corner" para 0 e 0 e a "upper right-corner"
	// para 200 e 150, respectivamente x e y.
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
	// glClearColor atrubui uma cor à janela, mas não coloca a janela na tela. Para tal, deve-se executar
	// o comando abaixo. O parâmetro GL_COLOR_BUFFER_BIT indica que os bits do "color buffer (refresh buffer)", devem 
	// ser setados para os valores indicados no comando glClearColor. Toda vez que a janela precisar ser
	// redesenhada, quando for redimensionada, por exemplo, o glClear deve ser executado. Se colocar
	// no procedimento "Init" isso não ocorrerá e, ao redimensionar da janela, ela ficará preta. Faça o teste!
	glClear(GL_COLOR_BUFFER_BIT);
	// Configura esquema de cor para os objetos que se que mostrar em tela. No exemplo abaixo, deseja-se 
	// setar a cor do objeto para verde escuro. o "f" indica que são valore de ponto flutuande ("float")
	glColor3f(1, 0.4, 0.5);
	//

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
	// Inicializa GLUT. Parâmetros são opcionais.
	glutInit(&argc, argv);
	// Configurar opções para mostrar a janela. No caso abaixo, optou-se pelo "single refresh buffer" - GLUT_SINGLE, 
	// e queremos utilizar o sistema de cores RGB - GLUT_RGB. A "|" indica operação "OR". Contrapondo a "single refresh
	// buffer", pode-se ter "double refresh buffer" para animações.
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	// Configura a posição inicial o "upper left-corner" da janela (acima e à esquerda)
	glutInitWindowPosition(100, 100);
	// Configura a largura, primeiro parâmetro, e a altura da janela. Após mostrar a janela na tela
	// é possível reposicioná-la e redimensioná-la.
	glutInitWindowSize(500, 500);
	// Criar uma janela com um título
	glutCreateWindow("Hello Word, Daniele!");
	//Executa rotinas de inicialização
	init();
	// o procedimento lineSegment será "passado" para a janela criada. O procedimento "lineSegment" é denominado
	// de "display callback function" e esse procedimento é descrito com sendo "registrado" pela funcão
	// "glutDisplayFunc" como a rotina que será chamada sempre que a janela precisar ser mostrada novamente. Isso pode
	// ocorrer, por exemplo, se o usuário mover a janela. Nesse caso, "lineSegment" será novamente chamado.
	glutDisplayFunc(lineSegment);
	// Deve ser a última função de seu código. Mostra o gráfico inicial e coloca o programa em um loop que 
	// avalia inputs do usuário, tipo uso do mouse ou do teclado. Nesse primeiro exemplo, não haverá interação,
	// então o programa mostrará a figura até que a janela seja fechada.
	glutMainLoop();

	return 0;

}
