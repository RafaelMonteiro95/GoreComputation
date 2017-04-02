#include<GL\glut.h>

void Draw(void) {
	// Define a cor de fundo da cena
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Aplica a cor de fundo
	glClear(GL_COLOR_BUFFER_BIT);

	// Define a cor inicial de desenho
	glColor3f(1.0f, 0.0f, 0.0f);

	// Define os vertices de um triângulo
	glBegin(GL_TRIANGLES);
		glVertex2f(10.0f, 10.0f);
		glVertex2f(90.0f, 10.0f);
		glVertex2f(50.0f, 30.0f);
	glEnd();

	// Define os vertices de uma linha
	glBegin(GL_LINES);
		glVertex2f(110.0f, 10.0f);
		glVertex2f(110.0f, 30.0f);
	glEnd();

	// Define os vertices de um pentágono
	glBegin(GL_POLYGON);
		glVertex2f(160.0f, 30.0f);
		glVertex2f(130.0f, 20.0f);
		glVertex2f(145.0f, 10.0f);
		glVertex2f(175.0f, 10.0f);
		glVertex2f(190.0f, 20.0f);
	glEnd();
	
	// Define os vértices de um trapézio com linhas
	glBegin(GL_LINE_LOOP);
		glVertex2f(10, -30.0f);
		glVertex2f(60, -30.0f);
		glVertex2f(40, -10.0f);
		glVertex2f(30, -10.0f);
	glEnd();

	// Define os vértices um line strip
	glBegin(GL_LINE_STRIP);
		glVertex2f(80, -30.0f);
		glVertex2f(120, -30.0f);
		glVertex2f(80, -10.0f);
		glVertex2f(120, -10.0f);
	glEnd();
	
	// Define os vértices de um quadrilátero
	glBegin(GL_QUADS);
		// Como fazer?
		glVertex2f(140.0f, -30.0f);
		glVertex2f(190.0f, -30.0f);
		glVertex2f(190.0f, -10.0f);
		glVertex2f(140.0f, -10.0f);
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