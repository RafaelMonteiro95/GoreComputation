/* Color class file

	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095
	Giovanna Oliveira Guimarães		-	9293693

*/

#include "rgb_color.hpp"

RGBColor::RGBColor(float r, float g, float b, float a){

	RGBColor *color = malloc(sizeof(RGBColor));

	color->r = r;
	color->g = g;
	color->b = b;
	color->a = a;

	return color;
}