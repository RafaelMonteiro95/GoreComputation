/* Camera source file

	Giovanna Oliveira Guimarães		-	9293693
	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include <GL/glut.h>

#include "camera2.hpp"

Camera::Camera(){

	speed = 0.3f;
	gravity = 0.098f;

	trasform = new Transform(new Vector3(0.0f, GROUND_LEVEL, -15.0f),
							new Vector3(0.0f, 0.0f, 0.0f),
							new Vector3(1.0f, 1.0f, 1.0f),);
}

Camera::~Camera(){}

void Camera::update() {
	
	if(g_camy < GROUND_LEVEL)
		g_camy = GROUND_LEVEL;

    glRotatef(rot[X],1.0,0.0,0.0);  //rotate our camera on teh  x-axis (left and right)
    glRotatef(rot[Y],0.0,1.0,0.0);  //rotate our camera on the  y-axis (up and down)
    glRotatef(rot[Z],0.0,0.0,1.0);  //rotate our camera on the  z-axis (dunno)
    glTranslated(-pos[X],-pos[Y],-pos[Z]); //translate the screen to the position of our camera
    
}

void Camera::zoomIn(){
	float rotxrad, rotyrad;
	rotyrad = (rot[Y] / 180 * 3.141592654f);
	rotxrad = (rot[X] / 180 * 3.141592654f); 
	pos[X] += float(sin(rotyrad)) * 0.2;
	pos[Z] -= float(cos(rotyrad)) * 0.2;
	pos[Y] -= float(sin(rotxrad)) * 0.2;
}

void Camera::zoomOut(){
	float rotxrad, rotyrad;
	rotyrad = (rot[Y] / 180 * 3.141592654f);
	rotxrad = (rot[X] / 180 * 3.141592654f); 
	pos[X] -= float(sin(rotyrad))* 0.2;
	pos[Z] += float(cos(rotyrad))* 0.2;
	pos[Y] += float(sin(rotxrad))* 0.2;
}

void Camera::strafeRight(){
	float rotyrad;
	rotyrad = (rot[Y] / 180 * 3.141592654f);
	pos[X] += float(cos(rotyrad)) * 0.2;
	pos[Z] += float(sin(rotyrad)) * 0.2;
}

void Camera::strafeLeft(){
	float rotyrad;
	rotyrad = (rot[Y] / 180 * 3.141592654f);
	pos[X] -= float(cos(rotyrad)) * 0.2;
	pos[Z] -= float(sin(rotyrad)) * 0.2;
}

void Camera::yawLeft(){
    rot[Y] -= 1;
}

void Camera::yawRight(){
    rot[Y] += 1;
}

void Camera::pitchUp(){
    rot[X] -= 1;
}

void Camera::pitchDown(){
    rot[X] += 1;
}

void Camera::checkPitch(){
	if(rot[X] > 90) rot[X] = 90;
	if(rot[X] < -90) rot[X] = 90;
}


