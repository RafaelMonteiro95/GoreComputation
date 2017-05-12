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

int main(int argc, char* argv[]){

	// Initialize glut and display
	glutInit(&argc, argv);
	initGL();

	// Creating a p
	Polygons::Polygon *p1 = new Polygons::Polygon(3);
	p1->setVertex(new Coord::Coordinates(0.0, 5.0), 0);
	p1->setVertex(new Coord::Coordinates(0.0, -5.0), 1);
	p1->setVertex(new Coord::Coordinates(5.0, 0.0), 2);

	p1->setVertexColor(new Colors::RGBColor(1.0f, 0.0f, 0.0f, 1.0f), 0);
	p1->setVertexColor(new Colors::RGBColor(0.0f, 1.0f, 0.0f, 1.0f), 1);
	p1->setVertexColor(new Colors::RGBColor(0.0f, 0.0f, 1.0f, 1.0f), 2);

	//creating a square
	Polygons::Polygon *p2 = new Polygons::Polygon(4);
	p2->setVertex(new Coord::Coordinates(5.0, 5.0), 0);
	p2->setVertex(new Coord::Coordinates(5.0, -5.0), 1);
	p2->setVertex(new Coord::Coordinates(-5.0, -5.0), 2);
	p2->setVertex(new Coord::Coordinates(-5.0, 5.0), 3);

	p2->setVertexColor(new Colors::RGBColor(1.0f, 0.0f, 0.0f, 1.0f), 0);
	p2->setVertexColor(new Colors::RGBColor(0.0f, 1.0f, 0.0f, 1.0f), 1);
	p2->setVertexColor(new Colors::RGBColor(0.0f, 0.0f, 1.0f, 1.0f), 2);
	p2->setVertexColor(new Colors::RGBColor(0.0f, 1.0f, 0.0f, 1.0f), 3);

	//no idea what this is
	Polygons::Polygon *p3 = new Polygons::Polygon(5);
	p3->setVertex(new Coord::Coordinates(0.0, 7.0), 0);
	p3->setVertex(new Coord::Coordinates(5.0, 3.0), 1);
	p3->setVertex(new Coord::Coordinates(2.0, -4.0), 2);
	p3->setVertex(new Coord::Coordinates(-2.0, -4.0), 3);
	p3->setVertex(new Coord::Coordinates(-5.0, 3.0), 4);

	// 0, 5, 2, -3, -5
	// 5, 3, -3, -3, 3 
	
	p3->setVertexColor(new Colors::RGBColor(1.0f, 0.0f, 0.0f, 1.0f), 0);
	p3->setVertexColor(new Colors::RGBColor(0.0f, 1.0f, 0.0f, 1.0f), 1);
	p3->setVertexColor(new Colors::RGBColor(0.0f, 0.0f, 1.0f, 1.0f), 2);
	p3->setVertexColor(new Colors::RGBColor(0.0f, 1.0f, 0.0f, 1.0f), 3);
	p3->setVertexColor(new Colors::RGBColor(1.0f, 0.0f, 0.0f, 1.0f), 4);


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
	glutIdleFunc(&IdleHandle);

	setPolygons(p1, 0);
	setPolygons(p2, 1);
	setPolygons(p3, 2);

	// The parameters are (left, right, bottom, top)
	// This create a clipping area in OpenGL coordinates (not screen coordinate)
	gluOrtho2D(CLIP_AREA_LEFT, CLIP_AREA_RIGHT, CLIP_AREA_BOTTOM, CLIP_AREA_TOP);

	// Start listening to glut events
	glutMainLoop();

	delete p1;
	delete p2;
	delete p3;
	
	return 0;
}


