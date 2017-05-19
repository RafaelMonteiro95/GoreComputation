/* Transform header file

	Giovanna Oliveira Guimarães		-	9293693
	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095

*/

#ifndef _TRANSFORM_HPP_
#define _TRANSFORM_HPP_

class Transform {

public:

	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

	Transform(Vector3 position, Vector3 rotation, Vector3 scale);
	virtual ~Transform();
};

#endif

