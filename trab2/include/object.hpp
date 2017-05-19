#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include "transform.hpp"

class Object {

public:

	float speed;
	Transform *transform;

	Object();
	Object(Transform *t);
	Object(Transform& t);
	Object(Vector3 *p, Vector3 *r, Vector3 *s);
	Object(Vector3& p, Vector3& r, Vector3& s);
	virtual ~Object();
}

#endif