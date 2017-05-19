/* Camera header file

	Giovanna Oliveira Guimarães		-	9293693
	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095

*/

#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#define GROUND_LEVEL (1.0f)

#define X 0
#define Y 1
#define Z 2

class Camera {

public:

	float speed;
	float pos[3];
	float rot[3];

	Camera();
	virtual ~Camera();

	void checkPitch();
	void update();
	void zoomIn();
	void zoomOut();
	void strafeRight();
	void strafeLeft();
	void yawLeft();
	void yawRight();
	void pitchUp();
	void pitchDown();
};

#endif

