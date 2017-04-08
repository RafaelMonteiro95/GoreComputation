/* Graphics functions header file

	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095
	Giovanna Oliveira Guimarães		-	9293693

*/

#ifndef _GRAPHICS_HPP_
#define _GRAPHICS_HPP_

#include "rgb_color.hpp"

using namespace Colors;

void initGL();

void SetBackgroundColor();
void SetBackgroundColor(float r, float g, float b, float a);
void SetBackgroundColor(Colors::RGBColor c);

void ClearScreen();
void ClearScreen(float r, float g, float b, float a);
void ClearScreen(Colors::RGBColor& c);

#endif