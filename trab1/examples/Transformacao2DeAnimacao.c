#include <GL/glut.h>

//GLfloat angle = 30.0f;

void draw(void){ 
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glColor3f(0.0f, 0.4f, 0.0f); 
   
  //glRotatef(-angle, 0.0f, 0.0f, 1.0f);

  // Desenha o triangulo
  glBegin(GL_TRIANGLES);
     glVertex2f(30.0f, 30.0f);
     glVertex2f(50.0f, 70.0f);
     glVertex2f(70.0f, 30.0f);
  glEnd();

  glTranslatef(80.0f, 30.0f, 0.0f);
  // glRotatef(angle, 0.0f, 0.0f, 1.0f);
  glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
  glScalef(1.5f, 1.5f, 0.0f);

  glColor3f(0.0f, 0.0f, 0.4f); 
    
  glBegin(GL_TRIANGLES);
     glVertex2f(30.0f, 30.0f);
     glVertex2f(50.0f, 70.0f);
     glVertex2f(70.0f, 30.0f);
  glEnd();

  // angle += 0.2f;

  glFlush();     
}

/*void movement(int value)
{
	glutPostRedisplay();
	glutTimerFunc(1, movement, 0);
}*/

// Programa Principal 
int main(int argc, char* argv[])
{
   glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1280, 720);
	glutCreateWindow("Exemplo Transformação e Animação");
	
	glutDisplayFunc(draw);
	// glutTimerFunc(1, movement, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//gluOrtho2D(Left, Right, Bottom, Top)
	gluOrtho2D(-200, 200, -200, 200);

	glutMainLoop();
}

