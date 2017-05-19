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

// #include "camera.hpp"

#define GROUND_LEVEL (1.0f)

#define X 0
#define Y 1
#define Z 2

class Camera {
	public:

		float speed;
		float pos[3];
		float rot[3];

		void checkPitch(){
			if(rot[X] > 90) rot[X] = 90;
			if(rot[X] < -90) rot[X] = 90;
		}

		Camera(){
			speed = 0.3f;
			pos[X] = 0.0f;
			pos[Y] = 0.0f;
			pos[Z] = 0.0f;
			rot[X] = 0.0f;
			rot[Y] = 0.0f;
			rot[Z] = 0.0f;
		}

		void update() {
		    glRotatef(rot[X],1.0,0.0,0.0);  //rotate our camera on teh  x-axis (left and right)
		    glRotatef(rot[Y],0.0,1.0,0.0);  //rotate our camera on the  y-axis (up and down)
		    glRotatef(rot[Z],0.0,0.0,1.0);  //rotate our camera on the  z-axis (dunno)
		    glTranslated(-pos[X],-pos[Y],-pos[Z]); //translate the screen to the position of our camera
		}

		void zoomIn(){
			float rotxrad, rotyrad;
			rotyrad = (rot[Y] / 180 * 3.141592654f);
			rotxrad = (rot[X] / 180 * 3.141592654f); 
			pos[X] += float(sin(rotyrad)) * 0.2;
			pos[Z] -= float(cos(rotyrad)) * 0.2;
			pos[Y] -= float(sin(rotxrad)) * 0.2;
		}

		void zoomOut(){
			float rotxrad, rotyrad;
			rotyrad = (rot[Y] / 180 * 3.141592654f);
			rotxrad = (rot[X] / 180 * 3.141592654f); 
			pos[X] -= float(sin(rotyrad))* 0.2;
			pos[Z] += float(cos(rotyrad))* 0.2;
			pos[Y] += float(sin(rotxrad))* 0.2;
		}

		void strafeRight(){
			float rotyrad;
			rotyrad = (rot[Y] / 180 * 3.141592654f);
			pos[X] += float(cos(rotyrad)) * 0.2;
			pos[Z] += float(sin(rotyrad)) * 0.2;
		}

		void strafeLeft(){
			float rotyrad;
			rotyrad = (rot[Y] / 180 * 3.141592654f);
			pos[X] -= float(cos(rotyrad)) * 0.2;
			pos[Z] -= float(sin(rotyrad)) * 0.2;
		}

		void yawLeft(){
		    rot[Y] -= 1;
		}

		void yawRight(){
		    rot[Y] += 1;
		}

		void pitchUp(){
		    rot[X] -= 1;
		}

		void pitchDown(){
		    rot[X] += 1;
		}

};