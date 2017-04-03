/* Triangle class file

	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095
	Giovanna Oliveira Guimarães		-	9293693

*/

#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <GL/glut.h>
#include <vector>

#include "coordinates.hpp"

using namespace std;

class Triangle {
public:
	Triangle();
	void drawTriangle(vector<Coordinates> coord);
	virtual ~Triangle();	
};

#endif