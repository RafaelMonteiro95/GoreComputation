/* Callback functions source file

	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095
	Giovanna Oliveira Guimarães		-	9293693

*/

#include <GL/glut.h>

#include "callback.hpp"
#include "graphics.hpp"
#include "coordinates.hpp"

void Draw(){
	
	ClearScreen();



	glFlush();
}

/* KeyboardHandle

	uint8 key 	- Which keyboard key was pressed
	int x 		- Mouse pointer x coordinate
	int y 		- Mouse pointer y coordinate
*/
void KeyboardHandle(uint8 key, int x, int y){ /* TODO */}

/* MouseHandle

	int button 	- Which mouse button was clicked (LEFT_CLICK, RIGHT_CLICK, 
				  MIDDLE_CLICK)
	int state 	- The button stat (BUTTON_DOWN or BUTTON_UP)
	int x 		- Screen x coordinate
	int y 		- Screen y coordinate
*/
void MouseHandle(int button, int state, int x, int y){

}

/* NOTE: nao ta funcionando ;-;*/
void ResizeHandle(int width, int height){

	glViewport(0, 0, width, height);
	gluOrtho2D(0.0f, (float) width, 0.0f, (float) height);
	ClearScreen(1.0f, 1.0f, 1.0f, 1.0f);
	glFlush();
}