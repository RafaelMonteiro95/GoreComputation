#include <GL/glut.h>

void draw(void) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(0.0f, 0.4f, 0.0f);


	glTranslatef(20.0f, 30.0f, 0.0f);
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glScalef(1.5f, 1.5f, 0.0f);

	// Desenha o triangulo
	glBegin(GL_TRIANGLES);
		glVertex2f(30.0f, 30.0f);
		glVertex2f(50.0f, 70.0f);
		glVertex2f(70.0f, 30.0f);
	glEnd();

	glPushMatrix();
	
	glTranslatef(10.0f, 30.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.4f);

	glBegin(GL_TRIANGLES);
		glVertex2f(30.0f, 30.0f);
		glVertex2f(50.0f, 70.0f);
		glVertex2f(70.0f, 30.0f);
	glEnd();

	glPopMatrix();

	glTranslatef(0.0f, -40.0f, 0.0f);
	glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);
	
	glColor3f(0.4f, 0.0f, 0.0f);

	glBegin(GL_TRIANGLES);
		glVertex2f(30.0f, 30.0f);
		glVertex2f(50.0f, 70.0f);
		glVertex2f(70.0f, 30.0f);
	glEnd();
	
	glFlush();
}

// Programa Principal 
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Exemplo Transformação e Animação");

	glutDisplayFunc(draw);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//gluOrtho2D(Left, Right, Bottom, Top)
	gluOrtho2D(-200, 200, -200, 200);

	glutMainLoop();
}

