/* Color class header file

	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095
	Giovanna Oliveira Guimarães		-	9293693

*/

#ifndef _RGB_COLOR_H_
#define _RGB_COLOR_H_

namespace Colors {
	class RGBColor {

	public:
		float r, g, b, a;

		RGBColor();
		RGBColor(float r, float g, float b, float a);
		virtual ~RGBColor();
	};
}

#endif
