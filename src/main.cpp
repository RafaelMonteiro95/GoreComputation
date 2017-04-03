/* Main source file - Homework assignment 1 - moving objects with OpenGL & GLUT

	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095
	Giovanna Oliveira Guimarães		-	9293693

*/

#include <iostream>
#include <GL/glut.h>

#include "callback.hpp"
#include "graphics.hpp"

using namespace std;

int main(int argc, char* argv[]){

	// Initialize glut
	glutInit(&argc, argv);

	// Initialize display mode
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);


	glutInitWindowSize(800, 600);
	glutCreateWindow("FreeGluteos");
	

	// Set callback functions
	glutDisplayFunc(&Draw);				// Draw on screen
	glutKeyboardFunc(&KeyboardHandle);	// Keyboard events
	glutMouseFunc(&MouseHandle);		// Mouse events
	glutReshapeFunc(&ResizeHandle);		// Window resize event

	// The parameters are (left, right, bottom, top)
	// This create a clipping area in OpenGL coordinates (not screen coordinate)
	gluOrtho2D(0.0, 100.0, 0.0, 100.0);

	// Start listening to glut events
	glutMainLoop();
	
	return 0;
}


