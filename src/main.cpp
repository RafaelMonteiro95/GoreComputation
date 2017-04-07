/* Main source file - Homework assignment 1 - moving objects with OpenGL & GLUT

	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095
	Giovanna Oliveira Guimarães		-	9293693
*/

#include <iostream>
#include <GL/glut.h>

#include "rgb_color.hpp"
#include "callback.hpp"
#include "graphics.hpp"


/* Application defines */
#define CLIP_AREA_LEFT 		0.0
#define CLIP_AREA_RIGHT 	100.0
#define CLIP_AREA_BOTTOM 	0.0
#define CLIP_AREA_TOP 		100.0

#define DEFAULT_WINDOW_WIDTH	800
#define DEFAULT_WINDOW_HEIGHT	600

/* End application defines */

using namespace std;

#include "callback.hpp"

int x = 0;
int y = 0;

int main(int argc, char* argv[]){

	// Initialize glut and display
	glutInit(&argc, argv);
	initGL();

	// Initialize display mode
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);

	glutInitWindowSize(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
	glutCreateWindow(argv[0]);

	// Initialize window
	ClearScreen();
	glFlush();

	// Set callback functions
	glutDisplayFunc(&Draw);				// Draw on screen
	glutKeyboardFunc(&KeyboardHandle);	// Keyboard events
	glutMouseFunc(&MouseHandle);		// Mouse events
	glutReshapeFunc(&ResizeHandle);		// Window resize event

	// The parameters are (left, right, bottom, top)
	// This create a clipping area in OpenGL coordinates (not screen coordinate)
	gluOrtho2D(CLIP_AREA_LEFT, CLIP_AREA_RIGHT, CLIP_AREA_BOTTOM, CLIP_AREA_TOP);

	// Start listening to glut events
	glutMainLoop();
	
	return 0;
}


