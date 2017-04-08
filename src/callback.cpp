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

float destx = 0;
float desty = 0;

float objx[3] = {25.0f, 50.0f, 75.0f};
float objy[3] = {50.0f, 50.0f, 50.0f};

float stepx[3] = {0, 0, 0};
float stepy[3] = {0, 0, 0};

float speed[3] = {0.001, 0.003, 0.005};

void drawTriangles(){

	//for each polygon, draws it in the correct position using translation
	for(int i = 0; i < 3; i++){
		
		//pushing previous matrix
		glPushMatrix();

		//translates the new matrix one step closer to dest
		glTranslatef(objx[i] + stepx[i],
					 objy[i] + stepy[i],
			 		 0.0f);

		//draws the polygon
		glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 0.0f, 0.0f); // Define a cor vermelha para um dos vértices
			glVertex2f(0.0f, 5.0f);

			glColor3f(0.0f, 1.0f, 0.0f); // Define a cor verde para um dos vértices
			glVertex2f(-5.0f, -5.0f);

			glColor3f(0.0f, 0.0f, 1.0f); // Define a cor azul para um dos vértices
			glVertex2f(5.0f, -5.0f);
		glEnd();

		//updates the object position
		objx[i] += stepx[i];
		objy[i] += stepy[i];

		//returns to the default matrix
		glPopMatrix();
	}
}

void Draw(){

	ClearScreen();

	drawTriangles();

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
void MouseHandle(int button, int state, int x, int y){
	if(button == GLUT_LEFT_BUTTON && state == GLUT_UP){
		float winx = glutGet(GLUT_WINDOW_WIDTH);
		float winy = glutGet(GLUT_WINDOW_HEIGHT);
		
		//calculating screen position of click
		destx = 100*(((float)x)/winx);
		desty = 100-(100*(((float)y)/winy));

		//sets the new step size for each polygon 
		for(int i = 0; i < 3; i++){
			stepx[i] = (destx - objx[i]) * speed[i];
			stepy[i] = (desty - objy[i]) * speed[i];		
			
		}
	}
}

/* NOTE: nao ta funcionando ;-;*/
void ResizeHandle(int width, int height){

	// glViewport(0, 0, width, height);
	// glMatrixMode(GL_PROJECTION);
	// glLoadIdentity();


	// gluOrtho2D(0.0f, (width/winsizex)*100, 0.0f, (height/winsizey)*height);
	// cout << width << endl;
	// glMatrixMode(GL_MODELVIEW);
	// glutPostRedisplay();
	// ClearScreen(1.0f, 1.0f, 1.0f, 1.0f);
	// glFlush();
}


void IdleHandle(){

	//checking if the polygons are out of the screen
	for(int i = 0; i < 3; i++){
		if(objx[i] > 100 || objx[i] < 0 || objy[i] > 100 || objy[i] < 0){
			stepx[i] = 0.0f;
			stepy[i] = 0.0f;
			objx[i] = (25.0f)*(i+1);
			objy[i] = 50.0f;
		}
	}

	//draws changes
	glutPostRedisplay();
}