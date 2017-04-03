/* Graphics functions header file

	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095
	Giovanna Oliveira Guimarães		-	9293693

*/

#ifndef _GRAPHICS_HPP_
#define _GRAPHICS_HPP_

#include "rgb_color.hpp"

void initGL();

void SetBackgroundColor();
void SetBackgroundColor(float r, float g, float b, float a);
void SetBackgroundColor(RGBColor c);

void ClearScreen();
void ClearScreen(float r, float g, float b, float a);
void ClearScreen(RGBColor& c);

#endif