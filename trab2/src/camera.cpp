/* Camera source file

	Giovanna Oliveira Guimarães		-	9293693
	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095

*/

#include <math.h>
#include <GL/glut.h>

#include "camera.hpp"

Camera::Camera(){

	speed = 0.3f;
	gravity = 0.098f;

	transform = new Transform(new Vector3(0.0f, GROUND_LEVEL, 15.0f),
							new Vector3(0.0f, 0.0f, 0.0f),
							new Vector3(1.0f, 1.0f, 1.0f));
}

Camera::~Camera(){
	delete transform;
}

void Camera::checkHeight(){
	if(transform->position->y < GROUND_LEVEL){
		transform->position->y = GROUND_LEVEL;
	}
}

void Camera::update() {
	
    glRotatef(transform->rotation->x, 1.0f, 0.0f, 0.0);  //rotate our camera on the  x-axis (left and right)
    glRotatef(transform->rotation->y, 0.0f, 1.0f, 0.0);  //rotate our camera on the  y-axis (up and down)
    glRotatef(transform->rotation->z, 0.0f, 0.0f, 1.0);  //rotate our camera on the  z-axis (dunno)
    glTranslated(-transform->position->x,
				 -transform->position->y,
				 -transform->position->z); //translate the screen to the position of our camera
    
}

void Camera::zoomIn(){
	float rotxrad, rotyrad;
	rotyrad = (transform->rotation->y / 180.0f * M_PI);
	rotxrad = (transform->rotation->x / 180.0f * M_PI); 
	transform->position->x += float(sin(rotyrad)) * speed;
	transform->position->z -= float(cos(rotyrad)) * speed;
	transform->position->y -= float(sin(rotxrad)) * speed;
	checkHeight();
}

void Camera::zoomOut(){
	float rotxrad, rotyrad;
	rotyrad = (transform->rotation->y / 180.0f * M_PI);
	rotxrad = (transform->rotation->x / 180.0f * M_PI); 
	transform->position->x -= float(sin(rotyrad))* speed;
	transform->position->z += float(cos(rotyrad))* speed;
	transform->position->y += float(sin(rotxrad))* speed;
	checkHeight();
}

void Camera::strafeRight(){
	float rotyrad;
	rotyrad = (transform->rotation->y / 180.0f * M_PI);
	transform->position->x += float(cos(rotyrad)) * speed;
	transform->position->z += float(sin(rotyrad)) * speed;
	checkHeight();
}

void Camera::strafeLeft(){
	float rotyrad;
	rotyrad = (transform->rotation->y / 180.0f * M_PI);
	transform->position->x -= float(cos(rotyrad)) * speed;
	transform->position->z -= float(sin(rotyrad)) * speed;
	checkHeight();
}

void Camera::yawLeft(){
    transform->rotation->y -= 1.0f;
}

void Camera::yawRight(){
    transform->rotation->y += 1.0f;
}

void Camera::pitchUp(){
    transform->rotation->x -= 1.0f;
    checkPitch();
}

void Camera::pitchDown(){
    transform->rotation->x += 1.0f;
    checkPitch();
}

void Camera::checkPitch(){
	if(transform->rotation->x > 90) transform->rotation->x = 90;
	if(transform->rotation->x < -90) transform->rotation->x = 90;
}


