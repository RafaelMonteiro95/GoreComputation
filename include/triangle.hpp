/* Triangle class file

	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095
	Giovanna Oliveira Guimarães		-	9293693

*/

#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include "coordinates.hpp"

using namespace std;

class Triangle {
public:
	Triangle();
	void drawTriangle(Coordinates[] coord, int);
	Coordinates *getVertexes();
	Coordinates *getVertexes();
	virtual ~Triangle();

private:
	Coordinates[3] vertexes;
};

#endif