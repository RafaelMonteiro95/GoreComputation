/* Triangle functions source file

	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095
	Giovanna Oliveira Guimarães		-	9293693

*/

#include <GL/glut.h>
#include "polygon.hpp"

using namespace Polygons;

Polygon::Polygon(int vertexes) {
	this->nVertexes = vertexes; 
	this->vertexes = new Coord::Coordinates[nVertexes];
}

void Polygon::setVertex(Coord::Coordinates *coord, int index) {

	this->vertexes[index].x = coord->x;
	this->vertexes[index].y = coord->y;
}

Coord::Coordinates *Polygon::getVertexes(int index) {
	return &(this->vertexes[index]);
}

Coord::Coordinates *Polygon::getVertexes() {
	return this->vertexes;
}

void Polygon::drawPolygon() {
	
	glBegin(GL_POLYGON);	// Star OpenGL routine
	
	// Set polygon vertexes
	for(int i = 0; i < this->nVertexes; i++)
    	glVertex2f(this->vertexes[i].x, this->vertexes[i].y);

  	glEnd();	// End OpenGL routine
  	glFlush();	// Draw
}

Polygon::~Polygon() {
	delete[] this->vertexes;
}
