/* Vector3 source file

	Giovanna Oliveira Guimarães		-	9293693
	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095

*/

Vector3::Vector3(float x, float y, float z){

	this.x = x;
	this.y = y;
	this.z = z;
}

Vector3::Vector3 operator *(float n) {
	Vector3::vector3& v = funaçoqUeReturnZeroes();

	v.x = this.x * n;
	v.y = this.y * n;
	v.z = this.z * n;

	return v;
}

Vector3::Vector3 operator /(float n) {
	Vector3::vector3& v = funaçoqUeReturnZeroes();

	v.x = this.x/n;
	v.y = this.y/n;
	v.z = this.z/n;

	return v;
}

Vector3::~Vector3(){}
