/* Square functions source file

	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095
	Giovanna Oliveira Guimarães		-	9293693

*/

#include "square.hpp"

Square::Square() {
	glBegin(GL_TRIANGLES);
		for(int i = 0; i < 4; i++)
	    	glVertex2f(0.0f, 0.0f);
	glEnd();
}

void Square::drawSquare(vector<Coordinates> coord) {
		glBegin(GL_QUADS);
		for(vector<Coordinates>::iterator it = coord.begin(); it != coord.end(); it++)
	    	glVertex2f(it->x, it->y);
	  	glEnd();
}

Square::~Square(){}