/* Camera source file

	Giovanna Oliveira Guimarães		-	9293693
	Lucas Alexandre Soares 			-	9293265
	Rafael Augusto Monteiro 			-	9293095

*/

#include <stdio.h>
#include <string.h>
#include <string>
#include <math.h>
#include <GL/glut.h>

#include "vector3.hpp"
#include "camera.hpp"
#include "callbacks.hpp"
#include "draw.hpp"
#include "text2d.hpp"

//defining scene objects types
#define TEAPOT 0
#define TORUS 1
#define CUBE 2
#define NEXT 1
#define PREVIOUS -1

typedef int OBJECT_TYPE;

/* Each scene object contains a reference to it's transform properties
and a OBJECT_TYPE, which is used to call the correct drawing function defined in draw.hpp*/
typedef struct _sceneObject{
	Transform* transform;
	OBJECT_TYPE type;
} sceneObject;

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
int selectedObject = 0; // object that will handle transformations
bool keys[255] = {0}; // keypress state
bool skeys[255] = {0}; // special keypress state

Camera* cam;

//list of scene objects.
sceneObject objects[3];

GLfloat angle[]		= {1.0f, 1.0f, 0.2f};
GLfloat ambient[]	= {1.0f, 0.8f, 0.6f, 1.0f};
GLfloat diffuse[]	= {0.3f, 0.3f, 0.3f, 1.0f};
GLfloat specular[]	= {1.0f, 0.5f, 0.2f, 1.0f};

GLfloat step = 0.2f;
GLfloat *selected = angle;
GLfloat *debug_vectors[4];
int indexi = 1;

using namespace std;

void InitLightning(){
	
	// OpenGL lightning

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, angle);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

void myInit(){

	cam = new Camera();

	//object 0 is a Teapot located in (5,0,0)
	objects[0].transform = new Transform(5.0f, 0.0f, 0.0f,
								0.0f, 0.0f, 0.0f,
								0.0f, 0.0f, 0.0f);
	objects[0].type = TEAPOT;

	//object 1 is a Torus located in (0,0,0)
	objects[1].transform = new Transform(0.0f, 0.0f, 0.0f,
								0.0f, 0.0f, 0.0f,
								0.0f, 0.0f, 0.0f);
	objects[1].type = TORUS;

	//object 2 is a Cube located in (-5,0,0)
	objects[2].transform = new Transform(-5.0f, 0.0f, 0.0f,
								0.0f, 0.0f, 0.0f,
								0.0f, 0.0f, 0.0f);
	objects[2].type = CUBE;

	// DEBUG
	debug_vectors[0] = angle;
	debug_vectors[1] = ambient;
	debug_vectors[2] = diffuse;
	debug_vectors[3] = specular;
	InitLightning();
}


// function that deletes "camera" and "sceneObject" objects
void myCleanup(){
	delete cam;

	for(int i = 0; i < 3; i++){
		delete objects[i].transform;
	}
}

// function that processes special key buttons (such as arrows)
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

void selectObject(int which){
	selectedObject += which;
	if(selectedObject > 2) selectedObject = 0;
	if(selectedObject < 0) selectedObject = 2;
}

// function that processes normal button presses (such as 'w', 'a', 's' and 'd')
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

	//increases camera speed when plus is pressed
	if(keys['=']) {
		cam->speed += 0.02f;
		if(cam->speed > 2.0f)
			cam->speed = 2.0f;
	}
	//decreases camera speed when minus is pressed 
	if(keys['-']) {
		cam->speed -= 0.02f;
		if(cam->speed < 0.01f)
			cam->speed = 0.01f;
	}

	// translate right
	if(keys['i']){
		objects[selectedObject].transform->position->x += 0.3f;
	}

	// translate left
	if(keys['u']){
		objects[selectedObject].transform->position->x -= 0.3f;
	}

	// rotate right
	if(keys['k']){
		objects[selectedObject].transform->rotation->x += 10.0f;
	}

	// rotate left
	if(keys['j']){
		objects[selectedObject].transform->rotation->x -= 10.0f;
	}

	// scale up
	if(keys['m']){
		objects[selectedObject].transform->scale->x += 0.1f;
		objects[selectedObject].transform->scale->y += 0.1f;
		objects[selectedObject].transform->scale->z += 0.1f;
	}

	// scale down
	if(keys['n']){
		objects[selectedObject].transform->scale->x -= 0.1f;
		objects[selectedObject].transform->scale->y -= 0.1f;
		objects[selectedObject].transform->scale->z -= 0.1f;
	}

	// Cleanup glut before exiting
	if(keys[ASCII_ESC]) glutDestroyWindow(g_WindowHandle), myCleanup(), exit(0);


	// Debug alter lightning
	if(skeys[GLUT_KEY_F1]){
		indexi--;
		if(indexi < 0) indexi = 3;
		selected = debug_vectors[indexi];
	}

	if(skeys[GLUT_KEY_F2]){
		indexi++;
		if(indexi > 3) indexi = 0;
		selected = debug_vectors[indexi];
	}

	if(keys['z']) {
		selected[0] += step;
		if(selected[0] > 1.0f) selected[0] = 1.0f;
	}
	if(keys['x']) {
		selected[1] += step;
		if(selected[1] > 1.0f) selected[1] = 1.0f;
	}
	if(keys['c']) {
		selected[2] += step;
		if(selected[2] > 1.0f) selected[2] = 1.0f;
	}
	if(keys['v'] && indexi != 0) {
		selected[3] += step;
		if(selected[3] > 1.0f) selected[3] = 1.0f;
	}

	if(keys['Z']) {
		selected[0] -= step;
		if(selected[0] < -1.0f) selected[0] = -1.0f;
	}
	if(keys['X']) {
		selected[1] -= step;
		if(selected[1] < -1.0f) selected[1] = -1.0f;
	}
	if(keys['C']) {
		selected[2] -= step;
		if(selected[2] < -1.0f) selected[2] = -1.0f;
	}
	if(keys['V'] && indexi != 0) {
		selected[3] -= step;
		if(selected[3] < -1.0f) selected[3] = -1.0f;
	}
}

void displayText(float x, float y, const char *mstring){

	//drawing some text
	setOrthographicProjection();

	glPushMatrix();
	glLoadIdentity();
	// renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, mstring);
	renderBitmapString(5, 30, GLUT_BITMAP_8_BY_13, "Lighthouse3D");
	glPopMatrix();

	restorePerspectiveProjection();
}

// GlutIdleFunc callback. Processes keys and redraw scene
void update(void){

	static int count;

	processKeys();
	processSpecialKeys();

	glutPostRedisplay();
	InitLightning();
	
	displayText(5.0f, 30.0f, "teste string");
	if(count % 60 == 0){
		count = 0;
		printf("cam position: (%f, %f, %f)\n", cam->transform->position->x,
										 cam->transform->position->y,
										 cam->transform->position->z);
	}
}

// GlutDisplayFunc callback. Clears screen and draws the scene
void renderScene(void) {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	// Set the camera
	cam->update();

    // Draw ground
    drawGround();

    // Draws scene objects
    for(int i = 0; i < 3; i++){

		glPushMatrix();

    	switch(objects[i].type){
    	case TEAPOT:
    		selectedObject - TEAPOT == 0 ? drawTeapot(objects[i].transform, true): drawTeapot(objects[i].transform, false);
    		break;

    	case TORUS:
    		selectedObject - TORUS == 0 ? drawTorus(objects[i].transform, true): drawTorus(objects[i].transform, false);
    		break;

    	case CUBE:
    		selectedObject - CUBE == 0 ? drawCube(objects[i].transform, true): drawCube(objects[i].transform, false);
    		break;

		default:
			break;
		}

		glPopMatrix();
    }

	//swap buffers, outputting all drawings done
	glutSwapBuffers();
}

// glutReshapeFunc callback. Corrects the aspect ratio when the window size changes
void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0) h = 1;

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

// sets key presses when some key is pressed
void keyboardUp(unsigned char key, int x, int y){ keys[key] = false; }
void keyboardDown(unsigned char key, int x, int y){
	switch(key){

		case 't':
			selectObject(PREVIOUS);
			break;

		case 'y':
			selectObject(NEXT);
			break;

		case ' ':
			myCleanup();
			myInit();
			selectedObject = 0;
			break;
			
		default:
			keys[key] = true;
			break;
	}
}

void specialUp(int key, int x, int y){ skeys[key] = false; }
void specialDown(int key, int x, int y){ skeys[key] = true; }
