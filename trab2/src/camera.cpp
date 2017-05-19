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

#include "camera.hpp"

#define randRange(max) ( ((float) (rand()/RAND_MAX)) * max )
#define GROUND_LEVEL (1.0f)

typedef struct { float x; float y; float z; } vec3;
typedef struct { vec3 position; vec3 rotation; vec3 scale; } transform;

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

transform snowMen[36];
transform batata[36];
transform PotatoIceCream[36];

float g_gravity = 0.098f;

// Camera translation speed
float g_speed = 0.3f;

// XZ position of the camera
float g_camx = 0.0f, g_camy = GROUND_LEVEL, g_camz = 5.0f;

// Actual vector representing the camera's direction
float g_directionx = 0.0f, g_directiony = 0.0f, g_directionz = -1.0f;
// Angle of rotation for the camera direction
float g_angle = 0.0;

const GLfloat cyan[] = {0.0f, 0.8f, 0.8f, 1.0f};
const GLfloat red[] = {0.9f, 0.1f, 0.2f, 1.0f};
const GLfloat green[] = {0.0f, 0.1f, 0.0f, 1.0f};
const GLfloat blue[] = {0.0f, 0.0f, 1.0f, 1.0f};
const GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};
const GLfloat white[] = {1.0f, 1.0f, 1.0f, 1.0f};

GLfloat color[] = {0.0f, 0.0f, 0.0f, 1.0f};

bool setSpeed(float speed){
	if(speed < 0) return false;
	g_speed = speed;
	return true;
}

void processSpecialKeys() {

	if(skeys[GLUT_KEY_UP]){
		g_camx += g_directionx*g_speed;
		g_camz += g_directionz*g_speed;
	}
	
	if(skeys[GLUT_KEY_DOWN]){
		g_camx -= g_directionx*g_speed;
		g_camz -= g_directionz*g_speed;
	}
	
	if(skeys[GLUT_KEY_LEFT]){
		g_angle -= 0.036f;
		g_directionx = sin(g_angle);
		g_directionz = -cos(g_angle);
	}
	
	if(skeys[GLUT_KEY_RIGHT]){
		g_angle += 0.036f;
		g_directionx = sin(g_angle);
		g_directionz = -cos(g_angle);
	}
}

void processKeys() {

	// Movement
	if(keys['w']){
		g_camx += g_directionx*g_speed;
		g_camz += g_directionz*g_speed;
	}
	
	if(keys['a']){
		g_angle -= 0.036f;
		g_directionx = sin(g_angle);
		g_directionz = -cos(g_angle);
	}
	
	if(keys['s']){
		g_camx -= g_directionx*g_speed;
		g_camz -= g_directionz*g_speed;
	}
	
	if(keys['d']){
		g_angle += 0.036f;
		g_directionx = sin(g_angle);
		g_directionz = -cos(g_angle);
	}
	
	if(keys[' ']){
		g_camy += g_speed;
	} else {
		g_camy -= g_gravity;
	}
	
	// Translate 
	if(keys['e']){
	
	}
	
	// Rotate 
	if(keys['r']){
	
	}
	
	// Scale 
	if(keys['t']){
	
	}

	if(keys['+']){
		g_speed += 0.01f;
	}

	if(keys['-']){
		g_speed -= 0.01f;
	}

	// Cleanup glut before exiting
	if(keys[27]) glutDestroyWindow(g_WindowHandle), exit(0);
}

void drawBatata() {

	// Draw Body
	glColor3f(0.7f, 0.2f, 0.5f);
	glNormal3d(0, 1, 0);
	color[0] = 0.5f;
	color[1] = 0.2f;
	color[2] = 0.7f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	glTranslatef(0.0f, 0.75f, 0.0f);
	glutSolidTeapot(0.7f);
}

void drawSnowMan() {

	glColor3f(0.5f, 0.5f, 0.5f);
	glNormal3d(0, 1, 0);
	color[0] = 0.3f;
	color[1] = 0.3f;
	color[2] = 0.3f;
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
	// glColor3f(1.0f, 0.6f, 1.0f);
	glNormal3d(0, 1, 0);
	
	color[0] = 1.0f;
	color[1] = 0.0f;
	color[2] = 1.0f;

	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
	glutSolidSphere(0.75f, 20, 20);
}

void Update(void){

	processKeys();
	processSpecialKeys();
	renderScene();

	if(g_camy < GROUND_LEVEL){
		g_camy = GROUND_LEVEL;
	}
}

void initObject(){

	// Reset transformations
	glLoadIdentity();

	// Draw 36 SnowMen
	for(int i = -3; i < 3; i++){
		for(int j = -3; j < 3; j++) {
			
			glPushMatrix();
			
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
			
			drawSnowMan();
			glPopMatrix();
		}
	}

	// Draw 36 object Batata
	for(int i = -3; i < 3; i++){
		for(int j=-3; j < 3; j++) {
			
			glPushMatrix();
			
			int index = (j+3) + (i+3)*6;
			batata[index].position.x = i*3.0;
			batata[index].position.y = 0.0;
			batata[index].position.z = j*3.0;
			glTranslatef(batata[index].position.x, 
						batata[index].position.y, 
						batata[index].position.z);
			
			drawBatata();
			glPopMatrix();
		}
	}

	// Draw 36 object PotatoIceCream
	for(int i = -3; i < 3; i++){
		for(int j=-3; j < 3; j++) {
			
			glPushMatrix();
			
			int index = (j+3) + (i+3)*6;
			
			PotatoIceCream[index].position.x = i*22.0;
			PotatoIceCream[index].position.y = 0.0;
			PotatoIceCream[index].position.z = j*22.0;
			glTranslatef(PotatoIceCream[index].position.x, 
						PotatoIceCream[index].position.y, 
						PotatoIceCream[index].position.z);

			drawPotatoIceCream();
			glPopMatrix();
		}
	}

	glutSwapBuffers();
}

void renderScene(void) {

	srand(time(NULL));

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	// Iterate through all objects
	for (int i = 0; i < 36; i++){

		glPushMatrix();

		m = {
			{, , , (1-batata[index].scale.x)*batata[index].position.x},
			{, , , (1-batata[index].scale.y)*batata[index].position.y},
			{, , , (1-batata[index].scale.z)*batata[index].position.z},
			{0, 0, 0, 1}
		}
		glLoadMatrix();			

		PotatoIceCream[index].position.x = i*22.0;
		PotatoIceCream[index].position.y = 0.0;
		PotatoIceCream[index].position.z = j*22.0;
		glTranslatef(PotatoIceCream[index].position.x, 
					PotatoIceCream[index].position.y, 
					PotatoIceCream[index].position.z);

		drawPotatoIceCream();
		glPopMatrix();
	}


	// Set the camera
	gluLookAt( g_camx, g_camy,  g_camz,
			g_camx + g_directionx, g_camy + g_directiony, g_camz + g_directionz,
			0.0f, 1.0f, 0.0f);

    // Draw ground
	glBegin(GL_QUADS);
		glColor3f(255.0f, 255.0f, 255.0f);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();

    

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
