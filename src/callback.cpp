/* Callback functions source file

	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095
	Giovanna Oliveira Guimarães		-	9293693

*/

#include <GL/glut.h>
#include <iostream>

#include "free_gluteos.hpp"

using namespace std;

#define FALSE 0
#define TRUE 1

float G_dest_x = 90;
float G_dest_y = 90;

float G_curx = 90;
float G_cury = 90;

int G_activeRedisplay = FALSE;

Polygons::Polygon *p1, *p2, *p3;

void setPolygonsStupiFunacoq(Polygons::Polygon *p, int i) {
	if(i == 0) {
		p1 = p;
	} else if(i == 1) {
		p2 = p;
	} else if(i == 2) {
		p3 = p;
	}
}

void drawTriangle(){
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f); // Define a cor vermelha para um dos vértices
		glVertex2f(10.f, 10.0f);

		glColor3f(0.0f, 1.0f, 0.0f); // Define a cor verde para um dos vértices
		glVertex2f(90.0f, 10.0f);

		glColor3f(0.0f, 0.0f, 1.0f); // Define a cor azul para um dos vértices
		glVertex2f(G_curx, G_cury);
	glEnd();
}

void Draw(){

	ClearScreen();

	p1->drawPolygon();
	p2->drawPolygon();
	p3->drawPolygon();

	glFlush();
}

/* KeyboardHandle

	uint8 key 	- Which keyboard key was pressed
	int x 		- Mouse pointer x coordinate
	int y 		- Mouse pointer y coordinate
*/
void KeyboardHandle(unsigned char key, int x, int y){
	if (key == 27) exit(0);
}

/* MouseHandle

	int button 	- Which mouse button was clicked (LEFT_CLICK, RIGHT_CLICK, 
				  MIDDLE_CLICK)
	int state 	- The button stat (BUTTON_DOWN or BUTTON_UP)
	int x 		- Screen x coordinate
	int y 		- Screen y coordinate
*/
void MouseHandle(int button, int state, int xx, int yy){
	printf("TO CLICANO [%d, %d]\n", xx, yy);
	if(button == GLUT_LEFT_BUTTON && state == GLUT_UP){
		float winx = glutGet(GLUT_WINDOW_WIDTH);
		float winy = glutGet(GLUT_WINDOW_HEIGHT);
		

		G_dest_x = 100*(((float)xx)/winx);
		G_dest_y = 100-(100*(((float)yy)/winy));
	}

	glutIdleFunc(&IdleHandle);
	glutPostRedisplay();
}

/* NOTE: nao ta funcionando ;-;*/
void ResizeHandle(int width, int height){

	// gluOrtho2D(0.0f, (width/winsizex)*100, 0.0f, (height/winsizey)*height);
	// glMatrixMode(GL_MODELVIEW);
	// ClearScreen(0.6f, 0.0f, 0.20f, 1.0f);
	// glutPostRedisplay();
}

float step = 0.1;

void IdleHandle(){

/*	if(G_curx < G_dest_x){
		G_curx += step;
	}
	if(G_curx > G_dest_x){
		G_curx -= step;
	}

	if(G_cury < G_dest_y){
		G_cury += step;
	}
	if(G_cury > G_dest_y){
		G_cury -= step;
	}
*/
	glutPostRedisplay();
}