/* Triangle functions source file

	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095
	Giovanna Oliveira Guimarães		-	9293693

*/

#include "triangle.hpp"

Triangle::Triangle() {
	this->vertex1 = new Coordinates(0.0f, 0.0f);
	this->vertex2 = new Coordinates(0.0f, 0.0f);
	this->vertex3 = new Coordinates(0.0f, 0.0f);
}

Triangle::Triangle(vector<Coordinates> coord) {
	for(vector<Coordinates>::iterator it = coord.begin(); it != coord.end(); it++)
	    	
}


Triangle::Triangle(Coordinates[] coord) {
	for(vector<Coordinates>::iterator it = coord.begin(); it != coord.end(); it++)
	   this->vertexes  new Coordinates[;
}

void Triangle::drawTriangle(vector<Coordinates> coord) {
		glBegin(GL_TRIANGLES);
		for(vector<Coordinates>::iterator it = coord.begin(); it != coord.end(); it++)
	    	glVertex2f(it->x, it->y);
	  	glEnd();
}

Triangle::~Triangle() {}
