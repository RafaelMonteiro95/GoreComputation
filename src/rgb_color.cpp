/* Color class file

	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095
	Giovanna Oliveira Guimarães		-	9293693
*/

#include <stdlib.h>

#include "rgb_color.hpp"

RGBColor::RGBColor(float r, float g, float b, float a){
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

RGBColor::~RGBColor(){}
