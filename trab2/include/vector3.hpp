/* Vector3 header file

	Giovanna Oliveira Guimarães		-	9293693
	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095

*/

#ifndef _VECTOR3_HPP_
#define _VECTOR3_HPP_

class Vector3 {

public:

	float x;
	float y;
	float z;

	Vector3(float x, float y, float z);
	Vector3 operator *(float n);
	Vector3 operator /(float n);
	virtual ~Vector3();

	// Vector3& operator+(Vector3& v1, Vector3& v2){
		
	// }
};

#endif

