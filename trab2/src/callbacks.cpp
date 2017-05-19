/* Camera source file

	Giovanna Oliveira Guimarães		-	9293693
	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095

*/

#include <math.h>
#include <GL/glut.h>

#include "camera.hpp"
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

Transform *snowman;
Transform *teapot;
Transform *icecream;

const GLfloat cyan[] = {0.0f, 0.8f, 0.8f, 1.0f};
const GLfloat red[] = {0.9f, 0.1f, 0.2f, 1.0f};
const GLfloat green[] = {0.0f, 0.1f, 0.0f, 1.0f};
const GLfloat blue[] = {0.0f, 0.0f, 1.0f, 1.0f};
const GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};
const GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};

GLfloat color[] = {0.0f, 0.0f, 0.0f, 1.0f};

void myInit(){

	cam = new Camera();

	snowman = new Transform(5.0f, 0.0f, 0.0f,
							0.0f, 0.0f, 0.0f,
							0.0f, 0.0f, 0.0f);
	teapot = new Transform(0.0f, 0.0f, 0.0f,
							0.0f, 0.0f, 0.0f,
							0.0f, 0.0f, 0.0f);
	icecream = new Transform(-5.0f, 0.0f, 0.0f,
							0.0f, 0.0f, 0.0f,
							0.0f, 0.0f, 0.0f);

	// drawSnowman();

	// glPushMatrix();
	// drawTeapot();
	// glPopMatrix();

	// glPushMatrix();
	// drawTeapot();
	// glPopMatrix();

}

void myCleanup(){
	delete cam;
	delete snowman;
	delete teapot;
	delete icecream;
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

	if(keys['=']) {
		cam->speed += 0.02f;
		if(cam->speed > 2.0f)
			cam->speed = 2.0f;
	}
	if(keys['-']) {
		cam->speed -= 0.02f;
		if(cam->speed < 0.01f)
			cam->speed = 0.01f;
	}

	// Cleanup glut before exiting
	if(keys[ASCII_ESC]) glutDestroyWindow(g_WindowHandle), myCleanup(), exit(0);
}

void applyTransform(Transform* obj){
	glTranslatef(obj->position->x, obj->position->y + 0.7, obj->position->z);
	glScalef(obj->scale->x + 1, obj->scale->y + 1, obj->scale->z + 1);

	glRotatef(obj->rotation->x, 1.0f, 0.0f, 0.0f);
	glRotatef(obj->rotation->x, 0.0f, 1.0f, 0.0f);
	glRotatef(obj->rotation->x, 0.0f, 0.0f, 1.0f);
}

void drawTeapot(Transform* teapot) {

	glPushMatrix();

	// Apllies transformations
	applyTransform(teapot);

	// Draws obj
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidTeapot(0.7f);

	glPopMatrix();

}

void drawSnowman(Transform* snowman) {

	glPushMatrix();

	applyTransform(snowman);

	glColor3f(0.2f, 0.3f, 0.9f);
	glNormal3d(0, 1, 0);
	color[0] = 0.6f;
	color[1] = 0.3f;
	color[2] = 0.9f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);

	// Draw Body
	glTranslatef(0.0f ,0.75f, 0.0f);
	glutSolidSphere(0.75f,20,20);

	// Draw Head
	glTranslatef(0.0f, 1.0f, 0.0f);
	glutSolidSphere(0.4f,20,20);

	// Draw Eyes
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.05f, 0.10f, 0.36f);
	glutSolidSphere(0.1f,20,20);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.1f,20,20);
	glPopMatrix();

	// Draw Nose
	glColor3f(1.0f, 0.5f , 0.5f);
	glNormal3d(0, 1, 0);
	color[0] = 1.0f;
	color[1] = 0.5f;
	color[2] = 0.5f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	glutSolidCone(0.08f,0.8f,10,2);

}

void drawIcecream(Transform* icecream) {

	applyTransform(icecream);

	// Draw icecream Cone	
	glColor3f(0.6f, 0.2f, 0.3f);
	glNormal3d(0, 1, 0);
	color[0] = 1.0f;
	color[1] = 1.2f;
	color[2] = 1.3f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);

	// glTranslatef(0.0f, 2.5f, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(0.8, -2.5, 20, 5);

	// Draw icecream
	glColor3f(1.0f, 0.6f, 1.0f);
	glutSolidSphere(0.75f, 20, 20);
}

void drawTorus(Transform* torus){

	applyTransform(torus);

	glNormal3d(0, 1, 0);
	color[0] = 1.0f;
	color[1] = 1.2f;
	color[2] = 1.3f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);

	glRotatef(90,1,0,0);

	glColor3f(0.0f, .5f, 0.5f);
	glutSolidTorus(0.4f, 0.7f, 20, 20);
}

void drawCube(Transform* cube){

	applyTransform(cube);

	glNormal3d(0, 1, 0);
	color[0] = 1.0f;
	color[1] = 1.2f;
	color[2] = 1.3f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);


	glColor3f(0.3f, 0.5f, 0.0f);
	glutSolidCube(1.5f);

}

void drawGround(){
	glBegin(GL_QUADS);

	glColor3f(255.0f, 255.0f, 255.0f);
	glVertex3f(-100.0f, 0.0f, -100.0f);

	glColor3f(255.0f, 0.0f, 255.0f);
	glVertex3f(-100.0f, 0.0f,  100.0f);

	glColor3f(255.0f, 255.0f, 0.0f);
	glVertex3f( 100.0f, 0.0f,  100.0f);

	glColor3f(0.0f, 255.0f, 255.0f);
	glVertex3f( 100.0f, 0.0f, -100.0f);

	glEnd();
}

void update(void){

	processKeys();
	processSpecialKeys();

	glutPostRedisplay();
}

void renderScene(void) {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	// Set the camera
	cam->update();

    // Draw ground
    drawGround();

    // Draw a Snowman
	// drawSnowman();
	drawTeapot(teapot);
	drawTorus(icecream);
	drawCube(icecream);
	// glPopMatrix();

	// Draw a icecream cone
	// glPushMatrix();
	// glTranslatef(-5, 0, 0);
	// drawIcecream();
	// glPopMatrix();

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
