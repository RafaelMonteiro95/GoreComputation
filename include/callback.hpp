/* Callback functions header file

	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095
	Giovanna Oliveira Guimarães		-	9293693

*/

#ifndef _CALLBACK_HPP_
#define _CALLBACK_HPP_

#include "polygon.hpp"

typedef char int8;
typedef short int16;
typedef int int32;
typedef long int64;

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef unsigned long uint64;

void setPolygonsStupiFunacoq(Polygons::Polygon, int);
void Draw();
void KeyboardHandle(unsigned char, int, int );
void MouseHandle(int, int, int, int);
void ResizeHandle(int width, int height);
void IdleHandle();

#endif