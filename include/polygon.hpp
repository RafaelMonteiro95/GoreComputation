/* Polygon class file

	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095
	Giovanna Oliveira Guimarães		-	9293693

*/

#ifndef _POLYGON_H_
#define _POLYGON_H_

#include <GL/glut.h>

#include "coordinates.hpp"

namespace Polygons {

	class Polygon {
	public:
		Polygon(int vertexes);
		void setVertex(Coord::Coordinates *coord, int index);
		Coord::Coordinates *getVertexes(int index);
		Coord::Coordinates *getVertexes();
		void drawPolygon();
		virtual ~Polygon();

	private:
		int nVertexes;
		Coord::Coordinates *vertexes;
	};

}

#endif