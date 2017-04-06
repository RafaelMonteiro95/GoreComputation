/* Circle class file

	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095
	Giovanna Oliveira Guimarães		-	9293693

*/

#ifndef _CIRCLE_H_
#define _CIRCLE_H_

#include <GL/glut.h>
#include "coordinates.hpp"

using namespace std;

class Circle {
public:
	Circle();
	void drawCircle(Coordinates circle, float radius);
	virtual ~Circle();	
};

#endif