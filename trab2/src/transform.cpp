/* Transform source file

	Giovanna Oliveira Guimarães		-	9293693
	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095

*/

#include "transform.hpp"

Transform::Transform(Vector3& position, Vector3& rotation, Vector3& scale){

	this->position = new Vector3(position);
	this->rotation = new Vector3(rotation);
	this->scale = new Vector3(scale);
}

Transform::Transform(Vector3 *position, Vector3 *rotation, Vector3 *scale){

	this->position = new Vector3(position);
	this->rotation = new Vector3(rotation);
	this->scale = new Vector3(scale);
}

Transform::Transform(float px, float py, float pz, 
					float rx, float ry, float rz, 
					float sx, float sy, float sz){

	this->position = new Vector3(px, py, pz);
	this->rotation = new Vector3(rx, ry, rz);
	this->scale = new Vector3(sx, sy, sz);
}

Transform::~Transform(){

	delete this->position;
	delete this->rotation;
	delete this->scale;
}
