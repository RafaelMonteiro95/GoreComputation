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
#define SMOOTH true
#define FLAT false

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

bool shading_mode = SMOOTH;

Camera* cam;

// Color
GLfloat white[] = {1.0, 1.0, 1.0};
GLfloat purple[] = {1.0, 0.0, 1.0};
GLfloat red[] = {1.0, 0.0, 0.0};

//list of scene objects.
sceneObject objects[3];

// Map our light defines to GL_LIGHTX defines (they dont start at 0 to index 
// vectors)
GLenum gl_lights[] = {GL_LIGHT0, GL_LIGHT1, GL_LIGHT2};
#define getLight(number) (gl_lights[number])

// Our lights defines
#define MAX_LIGHTS	3
 #define LIGHT0 	0
 #define LIGHT1 	1
 #define LIGHT2 	2

// Our attributes defines
#define N_ATT		5
 #define ANGLE		0
 #define AMBIENT	1
 #define DIFFUSE	2
 #define SPECULAR	3
 #define POSITION	4

// Dont ask, just accept
/* 3D vector that stores the attributes of each light. If you don't understand
just accept it. */
GLfloat lights[MAX_LIGHTS][N_ATT][4] = {{
										{1.0f, 1.0f, 0.2f, 0.0f},
										{1.0f, 0.8f, 0.6f, 1.0f},
										{0.3f, 0.3f, 0.3f, 1.0f},
										{1.0f, 0.5f, 0.2f, 1.0f},
										{1.0f, 0.5f, 0.2f, 1.0f}
									},
									{
										{1.0f, 1.0f, 0.2f, 0.0f},
										{1.0f, 0.8f, 0.6f, 1.0f},
										{0.3f, 0.3f, 0.3f, 1.0f},
										{1.0f, 0.5f, 0.2f, 1.0f},
										{1.0f, 0.5f, 0.2f, 1.0f}
									},
									{
										{1.0f, 1.0f, 0.2f, 0.0f},
										{1.0f, 0.8f, 0.6f, 1.0f},
										{0.3f, 0.3f, 0.3f, 1.0f},
										{1.0f, 0.5f, 0.2f, 1.0f},
										{1.0f, 0.5f, 0.2f, 1.0f}
									}};

// Max values for each attribute
GLfloat maxs[] = {1.0f, 1.0f, 1.0f, 1.0f, 500.0f};
// Step for changing each attribute
GLfloat step[] = {0.1f, 0.1f, 0.1f, 0.1f, 1.0f};

// Actual selected light source
int selectedLight = LIGHT0;
// Actual selected attribute
int selectedAttribute = ANGLE;

void updateLightning(void);

void InitLightning(){
	
	// OpenGL lightning
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lights[LIGHT0][AMBIENT]);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lights[LIGHT0][ANGLE]);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lights[LIGHT0][AMBIENT]);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lights[LIGHT0][DIFFUSE]);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lights[LIGHT0][SPECULAR]);
	glLightfv(GL_LIGHT0, GL_POSITION, lights[LIGHT0][POSITION]);

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

void DisplayDebugInfo(){
    
    char str[255];
    char str2[255];

    sprintf(str, "Camera pos: (%.2f, %.2f, %.2f)", cam->transform->position->x,
    										 cam->transform->position->y,
    										 cam->transform->position->z);
    displayText(5.0f, 30.0f, str);

    // TODO
    sprintf(str, "Selected light %d attribute ", selectedLight);
     
	if(selectedAttribute == ANGLE)
		strcat(str, "ANGLE");
	else if(selectedAttribute == AMBIENT)
		strcat(str, "AMBIENT");
	else if(selectedAttribute == DIFFUSE)
		strcat(str, "DIFFUSE");
	else if(selectedAttribute == SPECULAR)
		strcat(str, "SPECULAR");
	else if(selectedAttribute == POSITION)
		strcat(str, "POSITION");
	
    displayText(5.0f, 50.0f, str);

    sprintf(str, "(%.1f, %.1f, %.1f, %.1f)",
		lights[selectedLight][selectedAttribute][0],
		lights[selectedLight][selectedAttribute][1],
		lights[selectedLight][selectedAttribute][2],
		lights[selectedLight][selectedAttribute][3]);
    displayText(330.0f, 50.0f, str);
	
	bool light0 = glIsEnabled(GL_LIGHT0);
	bool light1 = glIsEnabled(GL_LIGHT1);
	bool light2 = glIsEnabled(GL_LIGHT2);
    sprintf(str, "Light source 1 is %s", light0 ? "enabled" : "disabled");
    displayText(830.0f, 30.0f, str);
    sprintf(str, "Light source 2 is %s", light0 ? "enabled" : "disabled");
    displayText(830.0f, 50.0f, str);
    sprintf(str, "Light source 3 is %s", light0 ? "enabled" : "disabled");
    displayText(830.0f, 70.0f, str);
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

		glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, lights[LIGHT0][ANGLE]);
		glLightfv(GL_LIGHT0, GL_AMBIENT, lights[LIGHT0][AMBIENT]);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lights[LIGHT0][DIFFUSE]);
		glLightfv(GL_LIGHT0, GL_SPECULAR, lights[LIGHT0][SPECULAR]);
		glLightfv(GL_LIGHT0, GL_POSITION, lights[LIGHT0][POSITION]);

	} else if(glIsEnabled(GL_LIGHT1)){
		
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lights[LIGHT1][ANGLE]);
		glLightfv(GL_LIGHT1, GL_AMBIENT, lights[LIGHT1][AMBIENT]);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, lights[LIGHT1][DIFFUSE]);
		glLightfv(GL_LIGHT1, GL_SPECULAR, lights[LIGHT1][SPECULAR]);
		glLightfv(GL_LIGHT1, GL_POSITION, lights[LIGHT1][POSITION]);

	} else if(glIsEnabled(GL_LIGHT2)){

		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, lights[LIGHT2][ANGLE]);
		glLightfv(GL_LIGHT2, GL_AMBIENT, lights[LIGHT2][AMBIENT]);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, lights[LIGHT2][DIFFUSE]);
		glLightfv(GL_LIGHT2, GL_SPECULAR, lights[LIGHT2][SPECULAR]);
		glLightfv(GL_LIGHT2, GL_POSITION, lights[LIGHT2][POSITION]);
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

    DisplayDebugInfo();

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
			lights[selectedLight][selectedAttribute][0] += step[indexi];
			if(lights[selectedLight][selectedAttribute][0] > maxs[indexi]) 
				lights[selectedLight][selectedAttribute][0] = maxs[indexi];
			break;
		case 'x':
			lights[selectedLight][selectedAttribute][1] += step[indexi];
			if(lights[selectedLight][selectedAttribute][1] > maxs[indexi]) 
				lights[selectedLight][selectedAttribute][1] = maxs[indexi];
			break;
		case 'c':
			lights[selectedLight][selectedAttribute][2] += step[indexi];
			if(lights[selectedLight][selectedAttribute][2] > maxs[indexi]) 
				lights[selectedLight][selectedAttribute][2] = maxs[indexi];
			break;
		case 'v': 
			lights[selectedLight][selectedAttribute][3] += step[indexi];
			if(lights[selectedLight][selectedAttribute][3] > maxs[indexi]) 
				lights[selectedLight][selectedAttribute][3] = maxs[indexi];
			break;

		case 'Z':
			lights[selectedLight][selectedAttribute][0] -= step[indexi];
			if(lights[selectedLight][selectedAttribute][0] < -maxs[indexi]) 
				lights[selectedLight][selectedAttribute][0] = -maxs[indexi];
			break;
		case 'X':
			lights[selectedLight][selectedAttribute][1] -= step[indexi];
			if(lights[selectedLight][selectedAttribute][1] < -maxs[indexi]) 
				lights[selectedLight][selectedAttribute][1] = -maxs[indexi];
			break;
		case 'C':
			lights[selectedLight][selectedAttribute][2] -= step[indexi];
			if(lights[selectedLight][selectedAttribute][2] < -maxs[indexi]) 
				lights[selectedLight][selectedAttribute][2] = -maxs[indexi];
			break;
		case 'V': 
			lights[selectedLight][selectedAttribute][3] -= step[indexi];
			if(lights[selectedLight][selectedAttribute][3] < -maxs[indexi]) 
				lights[selectedLight][selectedAttribute][3] = -maxs[indexi];
			break;

		case 'F': 
			if(shading_mode == SMOOTH){
				glShadeModel(GL_FLAT);
				shading_mode = FLAT;
			} else if(shading_mode == FLAT){
				glShadeModel(GL_SMOOTH);
				shading_mode = SMOOTH;
			}
			break;

		case 'q': 
			glIsEnabled(getLight(selectedLight))   ? 
				glDisable(getLight(selectedLight)) : 
				glEnable(getLight(selectedLight));
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
			selectedLight--;
			if(selectedLight < 0) selectedLight = MAX_LIGHTS-1;
			break;

		case GLUT_KEY_F2:
			selectedLight++;
			if(selectedLight > MAX_LIGHTS-1) selectedLight = 0;
			break;

		case GLUT_KEY_F3:
			selectedAttribute--;
			if(selectedAttribute < 0) selectedAttribute = N_ATT-1;
			break;

		case GLUT_KEY_F4:
			selectedAttribute++;
			if(selectedAttribute > N_ATT-1) selectedAttribute = 0;
			break;

		default:
			skeys[key] = true; 
			break;
	}
}
