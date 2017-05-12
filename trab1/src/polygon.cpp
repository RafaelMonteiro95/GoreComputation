/* Triangle functions source file

	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095
	Giovanna Oliveira Guimarães		-	9293693

*/

#include <stdio.h>
#include <GL/glut.h>

#include "polygon.hpp"

using namespace Polygons;
using namespace Colors;

Polygon::Polygon(int vertexes) {
	this->nVertexes = vertexes; 
	this->vertexes = new Coord::Coordinates[nVertexes];
	this->color = new Colors::RGBColor[nVertexes];
}

void Polygon::setVertex(Coord::Coordinates *coord, int index) {

	this->vertexes[index].x = coord->x;
	this->vertexes[index].y = coord->y;
}

void Polygon::setVertexColor(RGBColor *color, int index) {

	this->color[index].r = color->r;
	this->color[index].g = color->g;
	this->color[index].b = color->b;
	this->color[index].a = color->a;
}

Coord::Coordinates *Polygon::getVertexes(int index) {
	return &(this->vertexes[index]);
}

Coord::Coordinates *Polygon::getVertexes() {
	return this->vertexes;
}

void Polygon::drawPolygon() {

	glBegin(GL_POLYGON);
		// Set polygon vertexes
		for(int i = 0; i < this->nVertexes; i++){
			glColor3f(this->color[i].r, this->color[i].b, this->color[i].g); // Define a cor vermelha para um dos vértices
			glVertex2f(this->vertexes[i].x, this->vertexes[i].y);
		}
	glEnd();
}

Polygon::~Polygon() {
	delete[] this->vertexes;
}
