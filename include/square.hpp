/* Square class file

	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095
	Giovanna Oliveira Guimarães		-	9293693

*/

#ifndef _SQUARE_H_
#define _SQUARE_H_

#include <GL/glut.h>
#include <vector>

#include "coordinates.hpp"

using namespace std;

class Square {
public:
	Square();
	void drawSquare(vector<Coordinates> coord);
	virtual ~Square();	
};

#endif