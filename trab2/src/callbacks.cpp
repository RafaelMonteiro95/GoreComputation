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

Transform *snowMen;
Transform *batata;
Transform *PotatoIceCream;

const GLfloat cyan[] = {0.0f, 0.8f, 0.8f, 1.0f};
const GLfloat red[] = {0.9f, 0.1f, 0.2f, 1.0f};
const GLfloat green[] = {0.0f, 0.1f, 0.0f, 1.0f};
const GLfloat blue[] = {0.0f, 0.0f, 1.0f, 1.0f};
const GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};
const GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};

GLfloat color[] = {0.0f, 0.0f, 0.0f, 1.0f};

void myInit(){

	cam = new Camera();

	snowMen = new Transform[36];
	batata = new Transform[36];
	PotatoIceCream = new Transform[36];

	// Draw 36 SnowMen
	for(int i = -3; i < 3; i++){
		for(int j = -3; j < 3; j++) {
			
			glPushMatrix();
			glTranslatef(i*7.0, 0, j*7.0);
			
			int index = (j+3) + (i+3)*6;
			
			/* This is the object's pivot point */
			/* Set object position */
			snowMen[index].position.x = i*7.0;
			snowMen[index].position.y = 0.0;
			snowMen[index].position.z = j*7.0;
			
			/* Set object rotation */
			snowMen[index].rotation.x = 0.0f;
			snowMen[index].rotation.y = 0.0f;
			snowMen[index].rotation.z = 0.0f;
			
			/* Set object scale */
			snowMen[index].scale.x = 1.0f;
			snowMen[index].scale.y = 1.0f;
			snowMen[index].scale.z = 1.0f;

			/* Move object to starting position */
			glTranslatef(snowMen[index].position.x,
						snowMen[index].position.y,
						snowMen[index].position.z);
			
			glPopMatrix();
		}
	}

	// Draw 36 PotatoIceCream
	for(int i = -3; i < 3; i++){
		for(int j = -3; j < 3; j++) {
			
			glPushMatrix();
			glTranslatef(i*3.0, 0, j*3.0);
			
			int index = (j+3) + (i+3)*6;
			
			/* This is the object's pivot point */
			/* Set object position */
			PotatoIceCream[index].position.x = i*3.0;
			PotatoIceCream[index].position.y = 0.0;
			PotatoIceCream[index].position.z = j*3.0;
			
			/* Set object rotation */
			PotatoIceCream[index].rotation.x = 0.0f;
			PotatoIceCream[index].rotation.y = 0.0f;
			PotatoIceCream[index].rotation.z = 0.0f;
			
			/* Set object scale */
			PotatoIceCream[index].scale.x = 1.0f;
			PotatoIceCream[index].scale.y = 1.0f;
			PotatoIceCream[index].scale.z = 1.0f;

			/* Move object to starting position */
			glTranslatef(PotatoIceCream[index].position.x,
						PotatoIceCream[index].position.y,
						PotatoIceCream[index].position.z);
			
			drawSnowMan();
			glPopMatrix();
		}
	}

	// Draw 36 batata
	for(int i = -3; i < 3; i++){
		for(int j = -3; j < 3; j++) {
			
			glPushMatrix();
			glTranslatef(i*17.0, 0, j*17.0);
			
			int index = (j+3) + (i+3)*6;
			
			/* This is the object's pivot point */
			/* Set object position */
			batata[index].position.x = i*17.0;
			batata[index].position.y = 0.0;
			batata[index].position.z = j*17.0;
			
			/* Set object rotation */
			batata[index].rotation.x = 0.0f;
			batata[index].rotation.y = 0.0f;
			batata[index].rotation.z = 0.0f;
			
			/* Set object scale */
			batata[index].scale.x = 1.0f;
			batata[index].scale.y = 1.0f;
			batata[index].scale.z = 1.0f;

			/* Move object to starting position */
			glTranslatef(batata[index].position.x,
						batata[index].position.y,
						batata[index].position.z);
			
			drawSnowMan();
			glPopMatrix();
		}
	}
}

void myCleanup(){
	delete cam;
	delete[] snowMen;
	delete[] batata;
	delete[] PotatoIceCream;
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
	glNormal3d(0, 1, 0);
	color[0] = 0.0f;
	color[1] = 0.0f;
	color[2] = 0.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);

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

	// Draw shit
	glColor3f(0.9f, 0.3f , 0.33f);
	glNormal3d(0.2f, 0.3f, 0.6f);
	color[0] = 1.0f;
	color[1] = 0.5f;
	color[2] = 0.5f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	glTranslatef(0.0f ,1.0f, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(0.6, -1, 10, 5);
}

void drawPotatoIceCream() {

	// Draw Icecream Cone	
	glColor3f(0.3f, 0.2f, 0.3f);
	glNormal3d(0, 1, 0);
	color[0] = 1.0f;
	color[1] = 0.0f;
	color[2] = 0.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);

	glTranslatef(0.0f, 5.00f, 0.0f);
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

// void initObject(){

	// Reset transformations
	glLoadIdentity();

	// Set the camera
	cam->update();
	// gluLookAt( g_camx, g_camy,  g_camz,
			// g_camx + g_directionx, g_camy + g_directiony, g_camz + g_directionz,
			// 0.0f, 1.0f, 0.0f);

    // Draw ground
	glBegin(GL_QUADS);
		glColor3f(20.0f, 20.0f, 20.0f);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();

    // Draw 36 SnowMen
	for(int i = -3; i < 3; i++){
		for(int j = -3; j < 3; j++) {
			
			glPushMatrix();
			glTranslatef(i*(7.0 + randRange(3.0)), 0, j*(7.0 + randRange(5.0)));
			
			// int index = (j+3) + (i+3)*6;
			
			// /* This is the object's pivot point */
			// /* Set object position */
			// snowMen[index].position.x = i*7.0;
			// snowMen[index].position.y = 0.0;
			// snowMen[index].position.z = j*7.0;
			
			// /* Set object rotation */
			// snowMen[index].rotation.x = 0.0f;
			// snowMen[index].rotation.y = 0.0f;
			// snowMen[index].rotation.z = 0.0f;
			
			// /* Set object scale */
			// snowMen[index].scale.x = 1.0f;
			// snowMen[index].scale.y = 1.0f;
			// snowMen[index].scale.z = 1.0f;

			// /* Move object to starting position */
			// glTranslatef(snowMen[index].position.x,
			// 			snowMen[index].position.y,
			// 			snowMen[index].position.z);
			
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
