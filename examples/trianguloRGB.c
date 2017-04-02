#include <GL/glut.h>

void Draw(void) {
	// Define a cor de fundo da cena
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Aplica a cor de fundo
	glClear(GL_COLOR_BUFFER_BIT);

	// Define os vértices de um triângulo
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f); // Define a cor vermelha para um dos vértices
		glVertex2f(20.0f, -30.0f);

		glColor3f(0.0f, 1.0f, 0.0f); // Define a cor verde para um dos vértices
		glVertex2f(180.0f, -30.0f);

		glColor3f(0.0f, 0.0f, 1.0f); // Define a cor azul para um dos vértices
		glVertex2f(100.0f, 30.0f);
	glEnd();

	// Envia os dados para serem desenhados
	glFlush();
}

// Função responsável por tratar eventos de mouse
void Mouse(int button, int state, int x, int y)
{
	// Se o botão utilizado for o direito, a função exit(0) será executada.
	if (button == GLUT_RIGHT_BUTTON)
	{
		exit(0);
	}
}

// Função responsável por tratar eventos de teclado
void Keyboard(unsigned char key, int x, int y)
{
	// Se a tecla cujo código ASCII é 102 (letra f) for pressionada
	// a função glutFullScreen() chamada
	if (key == 102)
	{
		glutFullScreen();
	}

	// Se a tecla cujo código ASCII é 27 (ESC) for pressionada
	// a função glutReshapeWindow será chamada
	if (key == 27)
	{
		glutReshapeWindow(200, 200);
	}
}


int main(int argc, char* argv[])
{
	// Inicializa a gut
	glutInit(&argc, argv);

	// Define o modo de inicialização do display
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	// Define o centro da tela como posição inicial da janela
	glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) - 640) / 2, (glutGet(GLUT_SCREEN_HEIGHT) - 480) / 2);

	// Define o tamanho da janela
	glutInitWindowSize(640, 480);

	// Define o nome da Janela e a cria
	glutCreateWindow("Exemplo OpenGL");

	// Define qual a função callback de desenho
	glutDisplayFunc(Draw);

	// Define a função callback responsável por tratar eventos de teclado
	glutKeyboardFunc(Keyboard);
	
	// Define a função callback responsável por tratar eventos de mouse
	glutMouseFunc(Mouse);

	// Define os pontos de corte das coordenadas de tela/rasterização nas coordenadas globais
	gluOrtho2D(0, 200, -40, 40);

	// gluOrtho2D(0, 200, 40, -40); descomente este trecho e comente o trecho acima para 
	// inveter o eixo y

	// Loop da glut
	glutMainLoop();
}