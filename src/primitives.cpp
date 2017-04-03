/* Primitives functions source file

	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095
	Giovanna Oliveira Guimarães		-	9293693

*/

#include <GL/glut.h>
#include <vector>
#include <cmath>

using namespace std;

//#include "primitives.hpp"
#include "coordinates.hpp"

void drawTriangle(vector<coordinates> coord) {
	glBegin(GL_TRIANGLES);
	for(vector<coordinates>::iterator it = coord.begin(); it != coord.end(); it++)
    	glVertex2f(it->x, it->y);
  	glEnd();
}

void drawSquare(vector<coordinates> coord) {
	glBegin(GL_QUADS);
		for(vector<coordinates>::iterator it = coord.begin(); it != coord.end(); it++)
    		glVertex2f(it->x, it->y);                
	glEnd();
}

//void drawCircle(coordinates center, float radius) {

//