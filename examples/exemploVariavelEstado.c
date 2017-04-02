#include<GL\glut.h>

void Draw(void) {
	// Define a cor de fundo da cena
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Aplica a cor de fundo
	glClear(GL_COLOR_BUFFER_BIT);

	// Define os vértices de um quadrilátero e sua cor
	glBegin(GL_QUADS);
		glColor3f(0.0f, 0.0f, 0.4f); // definição da cor de desenho
		glVertex2f(50.0f, 20.0f);
		glVertex2f(50.0f, -20.0f);

		// glColor3f(0.0f, 1.0f, 0.0f); Descomente para que o quadrilátero comece com a cor azul e termine verde
		glVertex2f(150.0f, -20.0f);
		glVertex2f(150.0f, 20.0f);
	glEnd();

	// Envia os dados para serem desenhados
	glFlush();
}

int main(int argc, char* argv[])
{
	// Inicializa a gut
	glutInit(&argc, argv);

	// Define o modo de inicialização do display
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Define o tamanho da janela
	glutInitWindowSize(640, 480);

	// Define o nome da Janela e a cria
	glutCreateWindow("Exemplo OpenGL");

	// Define qual a função callback de desenho
	glutDisplayFunc(Draw);

	// Define os pontos de corte das coordenadas de tela/rasterização nas coordenadas globais
	gluOrtho2D(0, 200, -40, 40);

	// Loop da glut
	glutMainLoop();
}