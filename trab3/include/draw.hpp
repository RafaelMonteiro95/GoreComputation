#ifndef _DRAW_HPP_
#define _DRAW_HPP_

#include "transform.hpp"

void drawSun(Transform* sun);
void drawSnowman(Transform* snowman, GLfloat color[3]);
void drawIcecream(Transform* icecream, GLfloat color[3]);
void drawTorus(Transform* torus, GLfloat color[3]);
void drawCube(Transform* cube, GLfloat color[3]);
void drawSphere(Transform* sphere, GLfloat color[3]);
void drawTeapot(Transform* teapot, GLfloat color[3]);
void drawSky();
void drawGround();

#endif