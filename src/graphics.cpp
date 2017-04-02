/* Graphics functions source file

	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095
	Giovanna Oliveira Guimarães		-	9293693

*/

#include <GL/glut.h>

#include "graphics.hpp"
#include "rgb_color.hpp"


/* Clear screen to black */
void ClearScreen(){

	// Clear color (black and full opaque)
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Clear scene using clear color
	glClear(GL_COLOR_BUFFER_BIT);
}

/* Clear screen using RGBA as parameters */
void ClearScreen(float r, float g, float b, float a){

	// Clear color (black and full opaque)
	glClearColor(r, g, b, a);

	// Clear scene using clear color
	glClear(GL_COLOR_BUFFER_BIT);
}

void ClearScreen(RGBColor c){

	// Clear color (black and full opaque)
	glClearColor(c->r, c->g, c->b, c->a);

	// Clear scene using clear color
	glClear(GL_COLOR_BUFFER_BIT);
}
