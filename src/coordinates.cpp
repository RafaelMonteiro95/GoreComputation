/* Coordinates functions source file

	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095
	Giovanna Oliveira Guimarães		-	9293693

*/
#include "coordinates.hpp"

Coordinates::Coordinates() { 
	this->x = 0;
	this->y = 0;
}

Coordinates::Coordinates(float x, float y) {
	this->x = x;
	this->y = y;
}

Coordinates::~Coordinates(){}

void Coordinates::operator=(Coordinates& c){
	this->x = c.x;
	this->y = c.y;
}
