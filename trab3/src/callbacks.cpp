/* Camera source file

	Giovanna Oliveira Guimarães		-	9293693
	Lucas Alexandre Soares 			-	9293265
	Rafael Augusto Monteiro 		-	9293095
*/

#include <stdio.h>
#include <string.h>
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

// Color
GLfloat white[] = {1.0, 1.0, 1.0};
GLfloat purple[] = {1.0, 0.0, 1.0};
GLfloat red[] = {1.0, 0.0, 0.0};

//list of scene objects.
sceneObject objects[3];

#define N_ATT	5
GLfloat angle[]		= {1.0f, 1.0f, 0.2f, 0.0f}; // last value isnt used, its just for my convenience 
GLfloat ambient[]	= {1.0f, 0.8f, 0.6f, 1.0f};
GLfloat diffuse[]	= {0.3f, 0.3f, 0.3f, 1.0f};
GLfloat specular[]	= {1.0f, 0.5f, 0.2f, 1.0f};
GLfloat position[]	= {1.0f, 0.5f, 0.2f, 1.0f}; // last value isnt used, its just for my convenience 

GLfloat step = 0.1f;
GLfloat *debug_vectors[N_ATT];
int indexi = 0;
GLfloat *selected = angle;

void InitLightning(){
	
	// OpenGL lightning

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, angle);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_POSITION, position);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glShadeModel(GL_SMOOTH);
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
	debug_vectors[4] = position;

	selected = debug_vectors[indexi];
	
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
}

void displayText(float x, float y, const char *mstring){

	//drawing some text
	setOrthographicProjection();

	glPushMatrix();
	glLoadIdentity();
	glColor3f(1.0f, 1.0f, 1.0f);//needs to be called before RasterPos
	renderBitmapString(x, y, GLUT_BITMAP_HELVETICA_18, mstring);
	glPopMatrix();

	restorePerspectiveProjection();
}

void debugprintcoisas(){
    
    char str[255];
    
    sprintf(str, "Camera pos: (%.2f, %.2f, %.2f)", cam->transform->position->x,
    										 cam->transform->position->y,
    										 cam->transform->position->z);
    displayText(5.0f, 30.0f, str);

	if(indexi == 0){
		sprintf(str, "Selected angle [%d]", indexi);
	} else if(indexi == 1){
		sprintf(str, "Selected ambient [%d]", indexi);
	} else if(indexi == 2){
		sprintf(str, "Selected diffuse [%d]", indexi);
	} else if(indexi == 3){
		sprintf(str, "Selected specular [%d]", indexi);
	} else if(indexi == 4){
		sprintf(str, "Selected lightpos [%d]", indexi);
	}

    displayText(5.0f, 50.0f, str);

    sprintf(str, "(%.1f, %.1f, %.1f, %.1f)", selected[0],
    								 selected[1],
    								 selected[2],
    								 selected[3]);
    displayText(200.0f, 50.0f, str);
}

// GlutIdleFunc callback. Processes keys and redraw scene
void update(void){

	processKeys();
	processSpecialKeys();

	glutPostRedisplay();
	updateLightning();
}

void updateLightning(void){
	if(glIsEnabled(GL_LIGHT0)){

		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, angle);
		glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT0, GL_POSITION, position);

	    glEnable(GL_COLOR_MATERIAL);
	    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
		glShadeModel(GL_SMOOTH);

	} else if(glIsEnabled(GL_LIGHT1)){
		
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, angle);
		glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT1, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT1, GL_POSITION, position);

	} else if(glIsEnabled(GL_LIGHT2)){

		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, angle);
		glLightfv(GL_LIGHT2, GL_AMBIENT, ambient);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT2, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT2, GL_POSITION, position);
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
    		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, purple);
    		selectedObject - TEAPOT == 0 ? drawTeapot(objects[i].transform, true): drawTeapot(objects[i].transform, false);
    		break;

    	case TORUS:
    		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, purple);
    		selectedObject - TORUS == 0 ? drawTorus(objects[i].transform, true): drawTorus(objects[i].transform, false);
    		break;

    	case CUBE:
    		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128);
            glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, purple);
    		selectedObject - CUBE == 0 ? drawCube(objects[i].transform, true): drawCube(objects[i].transform, false);
    		break;

		default:
			break;
		}

		glPopMatrix();
    }

    debugprintcoisas();

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
void keyboardUp(unsigned char key, int x, int y){ (void) x, (void) y, keys[key] = false; }
void keyboardDown(unsigned char key, int x, int y){
	
	(void) x, (void) y;

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

		case 'z':
			selected[0] += step;
			if(selected[0] > 1.0f) selected[0] = 1.0f;
		break;
		case 'x':
			selected[1] += step;
			if(selected[1] > 1.0f) selected[1] = 1.0f;
		break;
		case 'c':
			selected[2] += step;
			if(selected[2] > 1.0f) selected[2] = 1.0f;
		break;
		case 'v': 
			if(indexi != 0) {
				selected[3] += step;
				if(selected[3] > 1.0f) selected[3] = 1.0f;
			}
		break;

		case 'Z':
			selected[0] -= step;
			if(selected[0] < -1.0f) selected[0] = -1.0f;
		break;
		case 'X':
			selected[1] -= step;
			if(selected[1] < -1.0f) selected[1] = -1.0f;
		break;
		case 'C':
			selected[2] -= step;
			if(selected[2] < -1.0f) selected[2] = -1.0f;
		break;
		case 'V': 
			if(indexi != 0) {
				selected[3] -= step;
				if(selected[3] < -1.0f) selected[3] = -1.0f;
			}
		break;

		// Enable/Disable lightning
		// TODO
		case '0':
			selected[0] -= step;
			if(selected[0] < -1.0f) selected[0] = -1.0f;
		break;
		case 'E':
			selected[1] -= step;
			if(selected[1] < -1.0f) selected[1] = -1.0f;
		break;
		case 'D':
			selected[2] -= step;
			if(selected[2] < -1.0f) selected[2] = -1.0f;
		break;
		case 'S':
			selected[2] -= step;
			if(selected[2] < -1.0f) selected[2] = -1.0f;
		break;

			
		default:
			keys[key] = true;
			break;
	}
}

void specialUp(int key, int x, int y){ (void) x, (void) y, skeys[key] = false; }
void specialDown(int key, int x, int y){ 
	
	(void) x, (void) y;

	switch(key){

		// Debug lightning
		case GLUT_KEY_F1:
			indexi--;
			if(indexi < 0) indexi = N_ATT-1;
			selected = debug_vectors[indexi];			
			break;

		case GLUT_KEY_F2:
			indexi++;
			if(indexi > N_ATT-1) indexi = 0;
			selected = debug_vectors[indexi];
			break;

		default:
			skeys[key] = true; 
			break;
	}
}
