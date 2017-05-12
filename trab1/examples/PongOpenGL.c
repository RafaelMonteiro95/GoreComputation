/* programa TELEJOGO */
/* Prof. Marco Antonio G. de Carvalho, UNICAMP-2006 */
/* Adaptado por Renato Rodrigues Oliveira da Silva, ICMC-USP-2009 */
/* Adaptado por Nícolas Roque dos Santos, ICMC-USP-2017 */
/* EXEMPLO DE ANIMACAO */

#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define DIREITA 1
#define ESQUERDA 0
#define PI 3.1415926535897932384

GLfloat movebola = 0;
GLint direcao = DIREITA;

void iniciaParametrosVisualizacao(void) {
	//Fundo da cena preto
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 600, 0, 400);
}

void display(void) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	
	glLineWidth(15.0);
	//Desenha a borda da cena
	glBegin(GL_LINE_LOOP);
		glVertex2i(2, 2);  glVertex2i(599, 2);
		glVertex2i(599, 399); glVertex2i(2, 399);
	glEnd();

	//Desenha as raquetes
	glBegin(GL_LINES);
		glVertex2i(100, 190);  glVertex2i(100, 240);
		glVertex2i(500, 190);  glVertex2i(500, 240);
	glEnd();

	glBegin(GL_POLYGON);
		for (float i = 0; i < 2 * PI; i += 0.1f)
		{
			glVertex2f(movebola + 10.0f * (float) cos(i) + 200.0f, 10.0f * (float) sin(i) + 210.0f);
		}
	glEnd();

	//Troca os buffers de video
	glutSwapBuffers();
	glFlush();
}

void bola(int passo)
{
	//Se estiver se movendo para a direita
	if (direcao == DIREITA) {
		movebola += 1.0f;
		// Se alcancou a outra raquete, muda de direcao
		if (movebola >= 290.0f) direcao = ESQUERDA;
	}
	else {
		movebola -= 1.0f;
		if (movebola <= -90.0f) direcao = DIREITA;
	}
	//Forca o GLUT a pintar a cena novamente
	glutPostRedisplay();
	//Aciona novamente o timer
	glutTimerFunc(1, bola, 1);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	//glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(600, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("PONG");

	iniciaParametrosVisualizacao();
	glutDisplayFunc(display);
	glutTimerFunc(1, bola, 1);
	glutMainLoop();
	return 0;
}


