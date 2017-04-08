/* Coordinates class file

	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095
	Giovanna Oliveira Guimarães		-	9293693

*/

#ifndef _COORDINATES_H_
#define _COORDINATES_H_

namespace Coord {
	class Coordinates {
		
	public:
		float x, y;

		Coordinates();
		Coordinates(float x, float y);
		virtual ~Coordinates();
	};
}

#endif

