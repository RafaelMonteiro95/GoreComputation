/* Polygon class file

	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095
	Giovanna Oliveira Guimarães		-	9293693

*/

#ifndef _POLYGON_H_
#define _POLYGON_H_

#include <GL/glut.h>
#include <vector>

#include "coordinates.hpp"

using namespace std;

class Polygon {
public:
	Polygon(int vertexes);
	Polygon(Coordinates[] coord, int nVertexes);
	void drawPolygon(Coordinates[] coord, int nVertexes);
	virtual ~Polygon();

private:
	int nVertexes;
	Coordinates[] vertexes;
};

#endif