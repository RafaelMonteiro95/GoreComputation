/* Triangle functions source file

	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095
	Giovanna Oliveira Guimarães		-	9293693

*/

#include <GL/glut.h>
#include "polygon.hpp"

Polygon::Polygon(int vertexes) {
	this->nVertexes = vertexes;
	this->vertexes = new Coordinates[nVertexes];
}

void Polygon::setVertex(Coordinates coord, int index) {

	this->vertexes[index] = coord;
}

Coordinates *Polygon::getVertexes(int index) {
	return &(this->vertexes[index]);
}

Coordinates *Polygon::getVertexes() {
	return this->vertexes;
}

void Polygon::drawPolygon(Coordinates coord[], int nVertexes) {
	
	glBegin(GL_POLYGON);	// Star OpenGL routine
	
	// Set polygon vertexes
	for(int i = 0; i < nVertexes; i++)
    	glVertex2f(coord[i].x, coord[i].y);

  	glEnd();	// End OpenGL routine
  	glFlush();	// Draw
}

Polygon::~Polygon() {
	delete[] this->vertexes;
}
