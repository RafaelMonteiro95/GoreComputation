/* Color class file

	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095
	Giovanna Oliveira Guimarães		-	9293693
*/

#include <stdlib.h>

#include "rgb_color.hpp"

using namespace Colors;

RGBColor::RGBColor(){

	this->r = 0.0f;
	this->g = 0.0f;
	this->b = 0.0f;
	this->a = 0.0f;
}

RGBColor::RGBColor(float r, float g, float b, float a){
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

RGBColor::~RGBColor(){}
