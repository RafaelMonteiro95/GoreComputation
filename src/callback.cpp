/* Callback functions source file

	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095
	Giovanna Oliveira Guimarães		-	9293693

*/

#include <GL/glut.h>
#include <iostream>
#include "callback.hpp"
#include "graphics.hpp"
#include "coordinates.hpp"

using namespace std;

float dest_x = 90;
float dest_y = 90;

void drawTriangle(){
	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f); // Define a cor vermelha para um dos vértices
		glVertex2f(10.f, 10.0f);

		glColor3f(0.0f, 1.0f, 0.0f); // Define a cor verde para um dos vértices
		glVertex2f(90.0f, 10.0f);

		glColor3f(0.0f, 0.0f, 1.0f); // Define a cor azul para um dos vértices
		glVertex2f(dest_x, dest_y);
	glEnd();
}

void Draw(){
	
	ClearScreen();

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
	if(button == GLUT_LEFT_BUTTON && state == GLUT_UP){
		float winx = glutGet(GLUT_WINDOW_WIDTH);
		float winy = glutGet(GLUT_WINDOW_HEIGHT);
		

		dest_x = 100*(((float)xx)/winx);
		dest_y = 100*(((float)yy)/winy);
	}
}

void ResizeHandle(int width, int height){

	glViewport(0, 0, width, height);
	gluOrtho2D(0.0f, (float) width, 0.0f, (float) height);
	ClearScreen(1.0f, 1.0f, 1.0f, 1.0f);
	glFlush();
}