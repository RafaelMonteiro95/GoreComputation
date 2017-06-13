/* 2D text for glut source file

	Giovanna Oliveira Guimarães		-	9293693
	Lucas Alexandre Soares 			-	9293265
	Rafael Augusto Monteiro 		-	9293095
*/

#include <GL/glut.h>
#include "text2d.hpp"

/* DONT END STRING WITH A \n VAI DA RUIM DEMAIS*/
void renderBitmapString(float x, float y, void *font, const char *string) {

	const char *c;
	glRasterPos2f(x, y);

	int i = 0;

	for (c=string; *c != '\0'; c++) {
		i++;
		if(*c == '\n'){
			i = 0;
			y += 20;
			c++;
			glRasterPos2f(x, y);
		}
		glutBitmapCharacter(font, *c);
	}
}

void renderSpacedBitmapString(float x, float y, int spacing, void *font, const char *string) {

	const char *c;
	int x1=x;

	for (c=string; *c != '\0'; c++) {

		glRasterPos2f(x1,y);
		glutBitmapCharacter(font, *c);
		x1 = x1 + glutBitmapWidth(font,*c) + spacing;
	}
}

void restorePerspectiveProjection() {

	glMatrixMode(GL_PROJECTION);
	// restore previous projection matrix
	glPopMatrix();

	// get back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void setOrthographicProjection() {

	// switch to projection mode
	glMatrixMode(GL_PROJECTION);

	// save previous matrix which contains the
	//settings for the perspective projection
	glPushMatrix();

	// reset matrix
	glLoadIdentity();

	// set a 2D orthographic projection
	gluOrtho2D(0, 1400, 900, 0);

	// switch back to modelview mode
	glMatrixMode(GL_MODELVIEW);
}

void displayText(float x, float y, const char *mstring){

	//drawing some text
	setOrthographicProjection();

	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);//needs to be called before RasterPos
	renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, mstring);
	glPopMatrix();

	restorePerspectiveProjection();
}
