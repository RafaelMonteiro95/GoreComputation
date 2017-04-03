/* Triangle functions source file

	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095
	Giovanna Oliveira Guimarães		-	9293693

*/

#include "triangle.hpp"

Triangle::Triangle() {
	glBegin(GL_TRIANGLES);
		for(int i = 0; i < 3; i++)
	    	glVertex2f(0.0f, 0.0f);
	glEnd();
}

void Triangle::drawTriangle(vector<Coordinates> coord) {
		glBegin(GL_TRIANGLES);
		for(vector<Coordinates>::iterator it = coord.begin(); it != coord.end(); it++)
	    	glVertex2f(it->x, it->y);
	  	glEnd();
}

Triangle::~Triangle(){}
