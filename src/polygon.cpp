/* Triangle functions source file

	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095
	Giovanna Oliveira Guimarães		-	9293693

*/

#include <GL/glut.h>
#include "polygon.hpp"

Polygon::Polygon(int vertexes) {
	this.nVertexes = vertexes;
	this->vertexes = new Coordinates[nVertexes];
}

void Polygon::setVertexes(Coordinates coord, int index) {

	this->vertexes[index] = coord;
}

Coordinates *Polygon::getVertexes(int index) {
	return this->Vertexes[index];
}

Coordinates *Polygon::getVertexes() {
	return this->Vertexes;
}

void Polygon::drawPolygon(Coordinates[] coord, int nVertexes) {
	glBegin(GL_POLYGON);
	for(int i = 0; i < nVertexes; i++)
    	glVertex2f(coord[i].x, coord[i].y);
  	glEnd();
}

Polygon::~Polygon() {
	delete[] this->vertexes;
}
