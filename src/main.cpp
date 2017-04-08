/* Main source file - Homework assignment 1 - moving objects with OpenGL & GLUT

	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095
	Giovanna Oliveira Guimarães		-	9293693
*/

#include <iostream>
#include <GL/glut.h>

#include "free_gluteos.hpp"

/* Application defines */
#define CLIP_AREA_LEFT 		0.0
#define CLIP_AREA_RIGHT 	100.0
#define CLIP_AREA_BOTTOM 	0.0
#define CLIP_AREA_TOP 		100.0

#define DEFAULT_WINDOW_WIDTH	800
#define DEFAULT_WINDOW_HEIGHT	600

/* End application defines */

using namespace std;

#include "free_gluteos.hpp"

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
	glutIdleFunc(NULL);

	Polygons::Polygon *triangle1 = new Polygons::Polygon(3);
	triangle1->setVertex(new Coord::Coordinates(0.0, 0.0), 0);
	triangle1->setVertex(new Coord::Coordinates(10.0, 0.0), 0);
	triangle1->setVertex(new Coord::Coordinates(0.0, 10.0), 0);


	Polygons::Polygon *triangle2 = new Polygons::Polygon(3);
	triangle2->setVertex(new Coord::Coordinates(100.0, 100.0), 1);
	triangle2->setVertex(new Coord::Coordinates(100.0, 10.0), 1);
	triangle2->setVertex(new Coord::Coordinates(10.0, 100.0), 1);

	Polygons::Polygon *triangle3 = new Polygons::Polygon(3);
	triangle3->setVertex(new Coord::Coordinates(50.0, 50.0), 2);
	triangle3->setVertex(new Coord::Coordinates(50.0, 60.0), 2);
	triangle3->setVertex(new Coord::Coordinates(60.0, 50.0), 2);

	setPolygonsStupiFunacoq(triangle1, 0);
	setPolygonsStupiFunacoq(triangle2, 1);
	setPolygonsStupiFunacoq(triangle3, 2);

	// The parameters are (left, right, bottom, top)
	// This create a clipping area in OpenGL coordinates (not screen coordinate)
	gluOrtho2D(CLIP_AREA_LEFT, CLIP_AREA_RIGHT, CLIP_AREA_BOTTOM, CLIP_AREA_TOP);

	// Start listening to glut events
	glutMainLoop();
	
	return 0;
}


