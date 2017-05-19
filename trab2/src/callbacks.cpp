/* Camera source file

	Giovanna Oliveira Guimarães		-	9293693
	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095

*/

#include <math.h>
#include <GL/glut.h>

#include "camera2.hpp"
#include "callbacks.hpp"

#define randRange(max) ( ((float) (rand()/RAND_MAX)) * max )
#define GROUND_LEVEL (1.0f)

Camera *cam;

typedef struct { float x; float y; float z; } PointNoVertice;

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

int g_WindowHandle; // Real declaration of global window handler
bool keys[255] = {0}; // keypress state
bool skeys[255] = {0}; // special keypress state

PointNoVertice snowMen[36];
PointNoVertice batata[36];
PointNoVertice PotatoIceCream[36];

void myInit(){
	cam = new Camera();
}

void myCleanup(){
	delete cam;
}

void processSpecialKeys() {

	if(skeys[GLUT_KEY_UP]){
		cam->pitchUp();
	}
	
	if(skeys[GLUT_KEY_DOWN]){
		cam->pitchDown();
	}
	
	if(skeys[GLUT_KEY_LEFT]){
		cam->yawLeft();
	}
	
	if(skeys[GLUT_KEY_RIGHT]){
		cam->yawRight();
	}
}

void processKeys() {

	// Movement
	if(keys['w']){
		cam->zoomIn();
	}
	
	if(keys['s']){
		cam->zoomOut();
	}
	
	if(keys['a']){
		cam->strafeLeft();
	}
	
	if(keys['d']){
		cam->strafeRight();
	}

	if(keys['+']) {
		cam->speed += 0.05f;
		if(cam->speed > 2.0f)
			cam->speed = 2.0f;
	}
	if(keys['-']) {
		cam->speed -= 0.05f;
		if(cam->speed < 0.01f)
			cam->speed = 0.01f;
	}

	// Cleanup glut before exiting
	if(keys[ASCII_ESC]) glutDestroyWindow(g_WindowHandle), myCleanup(), exit(0);
}

void drawBatata() {

	// Draw Body
	glColor3f(0.8f, 0.2f, 0.5f);
	glTranslatef(0.0f ,0.75f, 0.0f);
	// glutSolidSphere(0.75f,20,20);
	glutSolidTeapot(0.7f);
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
	glTranslatef(0.0f, 2.00f, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(0.8, -5, 20, 5);

	// Draw pOTATO
	glColor3f(1.0f, 0.6f, 1.0f);
	glutSolidSphere(0.75f, 20, 20);
}

void Update(void){

	processKeys();
	processSpecialKeys();
	renderScene();

}

void renderScene(void) {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	// Set the camera
	cam->update();
	// gluLookAt( g_camx, g_camy,  g_camz,
			// g_camx + g_directionx, g_camy + g_directiony, g_camz + g_directionz,
			// 0.0f, 1.0f, 0.0f);

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

	// Draw 36 object Batata
	for(int i = -3; i < 3; i++){
		for(int j=-3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i*(3.0 + randRange(31.0)), 0, j*(3.0 + randRange(51.0)));
			drawBatata();
			glPopMatrix();
		}
	}

	// Draw 36 object PotatoIceCream
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

void keyboardUp(unsigned char key, int x, int y){ keys[key] = false; }
void keyboardDown(unsigned char key, int x, int y){ keys[key] = true; }
void specialUp(int key, int x, int y){ skeys[key] = false; }
void specialDown(int key, int x, int y){ skeys[key] = true; }
