/* Graphics functions source file

	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095
	Giovanna Oliveira Guimarães		-	9293693

*/

#include <GL/glut.h>
#include "graphics.hpp"
#include "rgb_color.hpp"


/* Globals */
RGBColor *G_BGColor;	// Background color for the scene
/* End globals */

// Initialize display and variables
void initGL(){
	
	if(G_BGColor != NULL) delete G_BGColor;

	// Black
	G_BGColor = new RGBColor(0.0f, 0.0f, 0.0f, 1.0f);
}



void SetBackgroundColor(float r, float g, float b, float a){

	G_BGColor->r = r;
	G_BGColor->g = g;
	G_BGColor->b = b;
	G_BGColor->a = a;
}

void SetBackgroundColor(RGBColor *c){

	if(c == NULL) return;

	delete G_BGColor;
	G_BGColor = c;
}



/* Clear screen to global background color */
void ClearScreen(){
	ClearScreen(*G_BGColor);
}

/* Clear screen using RGBA as parameters */
void ClearScreen(float r, float g, float b, float a){

	// Clear color (black and full opaque)
	glClearColor(r, g, b, a);

	// Clear scene using clear color
	glClear(GL_COLOR_BUFFER_BIT);
}

/* Clear screen using a Color object */
void ClearScreen(RGBColor& c){

	// Clear color (black and full opaque)
	glClearColor(c.r, c.g, c.b, c.a);

	// Clear scene using clear color
	glClear(GL_COLOR_BUFFER_BIT);
}


