/* Camera source file

	Giovanna Oliveira Guimarães		-	9293693
	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095

*/

#include "camera.hpp"
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>


#define randRange(max) ( ((float) (rand()/RAND_MAX)) * max )

enum ascii_codes {

	ASCII_NUL,
	ASCII_SOH,
	ASCII_STX,
	ASCII_ETX,
	ASCII_EOT,
	ASCII_ENQ,
	ASCII_ACK,
	ASCII_BEL,
	ASCII_BS,
	ASCII_HT,
	ASCII_LF,
	ASCII_VT,
	ASCII_FF,
	ASCII_CR,
	ASCII_SO,
	ASCII_SI,
	ASCII_DLE,
	ASCII_DC1,
	ASCII_DC2,
	ASCII_DC3,
	ASCII_DC4,
	ASCII_NAK,
	ASCII_SYN,
	ASCII_ETB,
	ASCII_CAN,
	ASCII_EM,
	ASCII_SUB,
	ASCII_ESC,
	ASCII_FS,
	ASCII_GS,
	ASCII_RS,
	ASCII_US,
	ASCII_DEL = 127
};

// Camera translation speed
float g_speed = 0.5f;

// Angle of rotation for the camera direction
float g_angle = 0.0;

// Actual vector representing the camera's direction
float g_directionx = 0.0f, g_directionz = -1.0f;

// XZ position of the camera
float g_camx = 0.0f, g_camz = 5.0f;

bool setSpeed(float speed){
	if(speed < 0) return false;
	g_speed = speed;
	return true;
}

void drawBatata() {

	glColor3f(0.9f, 0.5f, 0.3f);

	// Draw Body
	glTranslatef(0.0f ,0.75f, 0.0f);
	glutSolidSphere(0.75f,20,20);

	// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f,20,20);

	// Draw Eyes
	glPushMatrix();
	glColor3f(0.2f,0.3f,0.7f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f,10,10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f,10,10);
	glPopMatrix();

	// Draw Nose
	glColor3f(0.5f, 1.0f , 0.5f);
	glutSolidCone(0.08f,0.5f,10,2);
}

void drawSnowMan() {

	glColor3f(1.0f, 1.0f, 1.0f);

	// Draw Body
	glTranslatef(0.0f ,0.75f, 0.0f);
	glutSolidSphere(0.75f,20,20);

	// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f,20,20);

	// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f,0.0f,0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f,10,10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f,10,10);
	glPopMatrix();

	// Draw Nose
	glColor3f(1.0f, 0.5f , 0.5f);
	glutSolidCone(0.08f,0.5f,10,2);
}

void drawPotatoIceCream() {

	// Draw Icecream Cone
	glColor3f(0.3f + randRange(0.1), 0.2f + randRange(0.2) , 0.3f + randRange(0.2));
	glutSolidCone(0.8, -5, 20, 5);

	// Draw Body
	glColor3f(randRange(1.0), 0.6f + randRange(0.2), 1.0f);
	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidSphere(0.75f, 20, 20);

	// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.25f, 20, 20);

	// Draw Eyes
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(0.05f, 0.10f, 0.18f);
	glutSolidSphere(0.05f, 10, 10);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.05f, 10, 10);
	glPopMatrix();

}

void renderScene(void) {

	srand(time(NULL));

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	// Set the camera
	gluLookAt( g_camx, 1.0f,  g_camz,
			g_camx + g_directionx, 1.0f, g_camz + g_directionz,
			0.0f, 1.0f, 0.0f);

    // Draw ground
	glColor3f(0.9f, 0.9f, 0.9f);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();

    // Draw 36 SnowMen
	for(int i = -3; i < 3; i++){
		for(int j=-3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i*(7.0 + randRange(3.0)), 0, j*(7.0 + randRange(5.0)));
			drawSnowMan();
			glPopMatrix();
		}
	}

	// Draw 36 object 2
	for(int i = -3; i < 3; i++){
		for(int j=-3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i*(3.0 + randRange(31.0)), 0, j*(3.0 + randRange(51.0)));
			drawBatata();
			glPopMatrix();
		}
	}

	// Draw 36 object 3
	for(int i = -3; i < 3; i++){
		for(int j=-3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i*(13.0 + randRange(3.0)), 0, j*(13.0 + randRange(5.0)));
			drawPotatoIceCream();
			glPopMatrix();
		}
	}

	glutSwapBuffers();
}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float _w = w, _h = h;
	float ratio = _w/_h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void processSpecialKeys(int key, int xx, int yy) {

	switch (key) {
	case GLUT_KEY_LEFT :
		g_angle -= 0.01f;
		g_directionx = sin(g_angle);
		g_directionz = -cos(g_angle);
		break;
	case GLUT_KEY_RIGHT :
		g_angle += 0.01f;
		g_directionx = sin(g_angle);
		g_directionz = -cos(g_angle);
		break;
	case GLUT_KEY_UP :
		g_camx += g_directionx*g_speed;
		g_camz += g_directionz*g_speed;
		break;
	case GLUT_KEY_DOWN :
		g_camx -= g_directionx*g_speed;
		g_camz -= g_directionz*g_speed;
		break;
	}
}

void processNormalKeys(unsigned char key, int g_camx, int y) {
	if (key == ASCII_ESC){
		glutDestroyWindow(g_handle);
		exit(0);
	}
}

