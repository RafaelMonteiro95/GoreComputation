#ifndef _TEXT_2D_
#define _TEXT_2D_

void renderBitmapString(float x, float y, void *font, const char *string);
void renderSpacedBitmapString(float x, float y, int spacing, void *font, const char *string);
void restorePerspectiveProjection();
void setOrthographicProjection();

#endif