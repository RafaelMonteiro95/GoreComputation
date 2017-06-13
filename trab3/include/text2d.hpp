/* 2D text for glut header file

	Giovanna Oliveira Guimarães		-	9293693
	Lucas Alexandre Soares 			-	9293265
	Rafael Augusto Monteiro 		-	9293095
*/

#ifndef _TEXT_2D_
#define _TEXT_2D_

void renderBitmapString(float x, float y, void *font, const char *string);
void renderSpacedBitmapString(float x, float y, int spacing, void *font, const char *string);
void restorePerspectiveProjection();
void setOrthographicProjection();
void displayText(float x, float y, const char *mstring);

#endif