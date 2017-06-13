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
#include "math_globals.hpp"

//defining scene objects types
#define TEAPOT 0
#define TORUS 1
#define CUBE 2
#define SPHERE 3
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
	GLfloat color[3];
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

bool showControls = true;
bool showDebug = false;
bool needUpdateLight = true;
bool shading_mode = SMOOTH;

Camera* cam;
Transform* sun;

// Color
GLfloat red[] 	 = {0.3f, 0.1f, 0.1f};
GLfloat green[]  = {0.1f, 0.3f, 0.1f};
GLfloat blue[] 	 = {0.1f, 0.1f, 0.5f};
GLfloat white[]  = {1.0f, 1.0f, 1.0f};
GLfloat black[]  = {0.0f, 0.0f, 0.0f};
GLfloat gray[]   = {0.5f, 0.5f, 0.5f};
GLfloat cyan[] 	 = {0.1f, 0.8f, 1.0f};
GLfloat pink[]	 = {0.3f, 0.1f, 0.3f};
GLfloat purple[] = {0.1f, 0.0f, 0.3f};
GLfloat yellow[] = {1.0f, 1.0f, 0.2f};
GLfloat brown[]  = {0.3f, 0.1f, 0.0f};

//list of scene objects.
sceneObject objects[3];
sceneObject lightSources[3];

// Map our light defines to GL_LIGHTX defines (they dont start at 0 to index 
// vectors)
GLenum gl_lights[] = {GL_LIGHT0, GL_LIGHT1, GL_LIGHT2};
#define getLight(number) (gl_lights[number])

// Our lights defines
#define MAX_LIGHTS	3
enum LIGHTS{
	LIGHT0,
	LIGHT1,
	LIGHT2
};

// Our attributes defines
#define N_ATT		4
enum ATTRIBUTES{
	AMBIENT,
	DIFFUSE,
	SPECULAR,
	POSITION
};

// Dont ask, just accept
/* 3D vector that stores the attributes of each light. If you don't understand
just accept it. */
GLfloat lights[MAX_LIGHTS][N_ATT][4] = {{/* Light source 0 - light is at infinity by default  */
										{1.0f, 0.0f, 0.0f, 1.0f},	// Attribute AMBIENT
										{0.8f, 0.8f, 0.8f, 1.0f},	// Attribute DIFFUSE
										{1.0f, 1.0f, 1.0f, 1.0f},	// Attribute SPECULAR
										{0.0f, 0.0f, 1.0f, 0.0f}	// Attribute POSITION
									},
									{	/* Light source 1	  */
										{0.0f, 1.0f, 0.0f, 1.0f},	// Attribute AMBIENT
										{0.8f, 0.0f, 0.8f, 1.0f},	// Attribute DIFFUSE
										{1.0f, 1.0f, 1.0f, 1.0f},	// Attribute SPECULAR
										{0.0f, 1.0f, 0.0f, 0.0f}	// Attribute POSITION
									},
									{	/* Light source 2	  */
										{0.0f, 0.0f, 1.0f, 1.0f},	// Attribute AMBIENT
										{0.8f, 0.0f, 0.8f, 1.0f},	// Attribute DIFFUSE
										{1.0f, 1.0f, 1.0f, 1.0f},	// Attribute SPECULAR
										{1.0f, 1.0f, 0.0f, 0.0f}	// Attribute POSITION
									}};

// Max values for each attribute
GLfloat maxs[] = {1.0f, 1.0f, 1.0f, 500.0f};
// Step for changing each attribute
GLfloat step[] = {0.1f, 0.1f, 0.1f, 0.3f};

// Actual selected light source
int selectedLight = LIGHT0;
// Actual selected attribute
int selectedAttribute = AMBIENT;

void updateLightning(void);

void InitLightning(){
	
	// OpenGL lightning
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lights[LIGHT0][AMBIENT]);

	glLightfv(GL_LIGHT0, GL_AMBIENT, lights[LIGHT0][AMBIENT]);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lights[LIGHT0][DIFFUSE]);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lights[LIGHT0][SPECULAR]);
	glLightfv(GL_LIGHT0, GL_POSITION, lights[LIGHT0][POSITION]);

	glLightfv(GL_LIGHT1, GL_AMBIENT, lights[LIGHT1][AMBIENT]);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lights[LIGHT1][DIFFUSE]);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lights[LIGHT1][SPECULAR]);
	glLightfv(GL_LIGHT1, GL_POSITION, lights[LIGHT1][POSITION]);

	glLightfv(GL_LIGHT2, GL_AMBIENT, lights[LIGHT2][AMBIENT]);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, lights[LIGHT2][DIFFUSE]);
	glLightfv(GL_LIGHT2, GL_SPECULAR, lights[LIGHT2][SPECULAR]);
	glLightfv(GL_LIGHT2, GL_POSITION, lights[LIGHT2][POSITION]);

    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHT2);
}

void myInit(){

	cam = new Camera();

	//object 0 is a Teapot located in (5,0,0)
	objects[0].transform = new Transform(5.0f, 2.0f, 0.0f,
								0.0f, 0.0f, 0.0f,
								0.0f, 0.0f, 0.0f);
	memcpy(objects[0].color, red, sizeof(GLfloat)*3);
	objects[0].type = TEAPOT;

	//object 1 is a Torus located in (0,0,0)
	objects[1].transform = new Transform(0.0f, 2.0f, 0.0f,
								0.0f, 0.0f, 0.0f,
								0.0f, 0.0f, 0.0f);
	memcpy(objects[1].color, pink, sizeof(GLfloat)*3);
	objects[1].type = TORUS;

	//object 2 is a Cube located in (-5,0,0)
	objects[2].transform = new Transform(-5.0f, 2.0f, 0.0f,
								0.0f, 0.0f, 0.0f,
								0.0f, 0.0f, 0.0f);
	memcpy(objects[2].color, green, sizeof(GLfloat)*3);
	objects[2].type = CUBE;

	sun = new Transform(0.0f, -5.0f, -50.0f,
				0.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 0.0f);


	lightSources[0].transform = new Transform(lights[LIGHT0][POSITION][0], lights[LIGHT0][POSITION][1], lights[LIGHT0][POSITION][2],
								0.0f, 0.0f, 0.0f,
								0.0f, 0.0f, 0.0f);
	lightSources[0].type = SPHERE;
	lightSources[1].transform = new Transform(lights[LIGHT1][POSITION][0], lights[LIGHT1][POSITION][1], lights[LIGHT1][POSITION][2],
								0.0f, 0.0f, 0.0f,
								0.0f, 0.0f, 0.0f);
	lightSources[1].type = SPHERE;
	lightSources[2].transform = new Transform(lights[LIGHT2][POSITION][0], lights[LIGHT2][POSITION][1], lights[LIGHT2][POSITION][2],
								0.0f, 0.0f, 0.0f,
								0.0f, 0.0f, 0.0f);
	lightSources[2].type = SPHERE;
	InitLightning();
}


// function that deletes "camera" and "sceneObject" objects
void myCleanup(){
	delete cam;
	delete sun;

	for(int i = 0; i < 3; i++)
		delete objects[i].transform;
}

void selectObject(int which){
	selectedObject += which;
	if(selectedObject > 2) selectedObject = 0;
	if(selectedObject < 0) selectedObject = 2;
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

	// Cleanup glut before exiting
	if(keys[ASCII_ESC]) 
		glutDestroyWindow(g_WindowHandle), myCleanup(), exit(0);
}

void DisplayDebugInfo(){
    
    char str[255];
    char str2[255];
    GLfloat *selectedAtt = lights[selectedLight][selectedAttribute];

    /* Display Camera */
    sprintf(str, "Camera pos: (%.2f, %.2f, %.2f)\n", cam->transform->position->x,
    										 cam->transform->position->y,
    										 cam->transform->position->z);
    displayText(5.0f, 40.0f, str);

    /* Display Light and its attributes*/
    char lightstr[255] = "Selected light X attribute ";
    lightstr[15] = selectedLight + '0';
     
	// Add attribute name
	if(selectedAttribute == AMBIENT)
		strcat(lightstr, "AMBIENT");
	else if(selectedAttribute == DIFFUSE)
		strcat(lightstr, "DIFFUSE");
	else if(selectedAttribute == SPECULAR)
		strcat(lightstr, "SPECULAR");
	else if(selectedAttribute == POSITION)
		strcat(lightstr, "POSITION");
	
	// Add attribute value
    sprintf(str, " (%.1f, %.1f, %.1f, %.1f)",
		selectedAtt[0], selectedAtt[1], selectedAtt[2], selectedAtt[3]);

    strcat(lightstr, str);

    if(selectedAttribute == POSITION && (selectedAtt[3] == 0.0 || selectedAtt[3] == -0.0))
    	strcat(str, "  AT INFINITY!");

    displayText(5.0f, 60.0f, lightstr);
	
	bool light0 = glIsEnabled(GL_LIGHT0);
	bool light1 = glIsEnabled(GL_LIGHT1);
	bool light2 = glIsEnabled(GL_LIGHT2);
    sprintf(str, "Light source 0, at (%.2f, %.2f, %.2f), is %s\nLight source 1, at (%.2f, %.2f, %.2f), is %s\nLight source 2, at (%.2f, %.2f, %.2f), is %s", 
    	lights[LIGHT0][POSITION][0],
    	lights[LIGHT0][POSITION][1],
    	lights[LIGHT0][POSITION][2],
    	light0 ? "enabled" : "disabled",
    	lights[LIGHT1][POSITION][0],
    	lights[LIGHT1][POSITION][1],
    	lights[LIGHT1][POSITION][2],
    	light1 ? "enabled" : "disabled",
    	lights[LIGHT2][POSITION][0],
    	lights[LIGHT2][POSITION][1],
    	lights[LIGHT2][POSITION][2],
    	light2 ? "enabled" : "disabled");

    displayText(glutGet(GLUT_WINDOW_WIDTH) -400.0f, 40.0f, str);
}

void DisplayControls(){
	displayText(5, 500, "WASD and Arrow Keys to move around\nF1/F2 cycle through light sources\nF3/F4 cycle through lights attributes\nZ X C V to increment attribute value\nQ to enable/disable light source\nSHIFT+F to change between FLAT and GOURAUD\nSHIFT + (Z X C V) to decrement attribute value\nIf a light source is not at infinity (position[3] == 0),\nit will be drawn at screen as a black sphere.");
}

// GlutIdleFunc callback. Processes keys and redraw scene
void update(void){
	
	static int count;
	float sine = g_sinf[count];
	float cossine = g_cosf[count];
	if(++count > 210) count = 0;
	
	processKeys();
	processSpecialKeys();

	glutPostRedisplay();
	
	if(needUpdateLight){
		updateLightning();
	}

	sun->position->y += 0.01f;

	// Translate objects
	float stranslation = 0.025f*sine;
	float cstranslation = 0.025f*cossine;
	objects[0].transform->position->x += stranslation;
	objects[0].transform->position->y += cstranslation;

	objects[1].transform->position->y -= stranslation;

	objects[2].transform->position->x -= cstranslation;
	objects[2].transform->position->y -= stranslation;

	// Rotate objects
	objects[0].transform->rotation->z += 0.5f;
	objects[1].transform->rotation->x += 0.5f;
	objects[2].transform->rotation->y += 0.5f;

	for (int i = 0; i < 3; i++){
		lightSources[i].transform->position->x = lights[i][POSITION][0];
		lightSources[i].transform->position->y = lights[i][POSITION][1];
		lightSources[i].transform->position->z = lights[i][POSITION][2];
	}
}

void updateLightning(void){

	needUpdateLight = false;

	if(glIsEnabled(GL_LIGHT0)){

		glLightfv(GL_LIGHT0, GL_AMBIENT, lights[LIGHT0][AMBIENT]);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lights[LIGHT0][DIFFUSE]);
		glLightfv(GL_LIGHT0, GL_SPECULAR, lights[LIGHT0][SPECULAR]);
		glLightfv(GL_LIGHT0, GL_POSITION, lights[LIGHT0][POSITION]);
	}

	if(glIsEnabled(GL_LIGHT1)){
		glLightfv(GL_LIGHT1, GL_AMBIENT, lights[LIGHT1][AMBIENT]);
		glLightfv(GL_LIGHT1, GL_DIFFUSE, lights[LIGHT1][DIFFUSE]);
		glLightfv(GL_LIGHT1, GL_SPECULAR, lights[LIGHT1][SPECULAR]);
		glLightfv(GL_LIGHT1, GL_POSITION, lights[LIGHT1][POSITION]);
	}
	
	if(glIsEnabled(GL_LIGHT2)){
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
    // Draw sun
    drawSun(sun);

    // Draws scene objects
    for(int i = 0; i < 3; i++){

    	glPushMatrix();

    	char buf[255];
    	switch(objects[i].type){
    	case TEAPOT:
    		drawTeapot(objects[i].transform, objects[i].color);
    		break;

    	case TORUS:
    		drawTorus(objects[i].transform, objects[i].color);
    		break;

    	case CUBE:
    		drawCube(objects[i].transform, objects[i].color);
    		break;

    	case SPHERE:
    		drawCube(objects[i].transform, objects[i].color);
    		break;

		default:
			break;
		}
		glPopMatrix();
    }

    // Draw light bulbs
    for(int i = 0; i < 3; i++){
    	// If not at infinity, draw light bulb
		if(lights[i][POSITION][3] != 0.0f){
    		glPushMatrix();
			drawSphere(lightSources[i].transform, black);
			glPopMatrix();
		}
	}

	if(showDebug){
    	DisplayDebugInfo();
	}
    if(showControls){
    	DisplayControls();
    }

    displayText(600, 40, "F9 - Show/Hide controls\nF10 - Show/Hide debug\nTry running the command \"make run reileao=1\"");

	//swap buffers, outputting all drawings done
	glutSwapBuffers();
}

// glutReshapeFunc callback. Corrects the aspect ratio when the window size changes
void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0) h = 1;

	// float _w = w, _h = h;

	float ratio = (float)w / (float)h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 500.0f);

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

		// Increment selected attribute values
		case 'z':
			needUpdateLight = true;
			lights[selectedLight][selectedAttribute][0] += step[selectedAttribute];
			if(lights[selectedLight][selectedAttribute][0] > maxs[selectedAttribute]) 
				lights[selectedLight][selectedAttribute][0] = maxs[selectedAttribute];
			break;
		case 'x':
			needUpdateLight = true;
			lights[selectedLight][selectedAttribute][1] += step[selectedAttribute];
			if(lights[selectedLight][selectedAttribute][1] > maxs[selectedAttribute]) 
				lights[selectedLight][selectedAttribute][1] = maxs[selectedAttribute];
			break;
		case 'c':
			needUpdateLight = true;
			lights[selectedLight][selectedAttribute][2] += step[selectedAttribute];
			if(lights[selectedLight][selectedAttribute][2] > maxs[selectedAttribute]) 
				lights[selectedLight][selectedAttribute][2] = maxs[selectedAttribute];
			break;
		case 'v': 
			needUpdateLight = true;
			lights[selectedLight][selectedAttribute][3] += step[selectedAttribute];
			if(lights[selectedLight][selectedAttribute][3] > maxs[selectedAttribute]) 
				lights[selectedLight][selectedAttribute][3] = maxs[selectedAttribute];
			break;

		// Dencrement selected attribute values
		case 'Z':
			needUpdateLight = true;
			lights[selectedLight][selectedAttribute][0] -= step[selectedAttribute];
			if(lights[selectedLight][selectedAttribute][0] < -maxs[selectedAttribute]) 
				lights[selectedLight][selectedAttribute][0] = -maxs[selectedAttribute];
			break;
		case 'X':
			needUpdateLight = true;
			lights[selectedLight][selectedAttribute][1] -= step[selectedAttribute];
			if(lights[selectedLight][selectedAttribute][1] < -maxs[selectedAttribute]) 
				lights[selectedLight][selectedAttribute][1] = -maxs[selectedAttribute];
			break;
		case 'C':
			needUpdateLight = true;
			lights[selectedLight][selectedAttribute][2] -= step[selectedAttribute];
			if(lights[selectedLight][selectedAttribute][2] < -maxs[selectedAttribute]) 
				lights[selectedLight][selectedAttribute][2] = -maxs[selectedAttribute];
			break;
		case 'V': 
			needUpdateLight = true;
			lights[selectedLight][selectedAttribute][3] -= step[selectedAttribute];
			if(lights[selectedLight][selectedAttribute][3] < -maxs[selectedAttribute]) 
				lights[selectedLight][selectedAttribute][3] = -maxs[selectedAttribute];
			break;

		// Change tonalization mode
		case 'F': 
			needUpdateLight = true;
			if(shading_mode == SMOOTH){
				glShadeModel(GL_FLAT);
				shading_mode = FLAT;
			} else if(shading_mode == FLAT){
				glShadeModel(GL_SMOOTH);
				shading_mode = SMOOTH;
			}
			break;

		// Enable/disable lightning
		case 'q': 
			needUpdateLight = true;
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

	// Go to previous light source
	if(key == GLUT_KEY_F1){
		selectedLight--;
		
		if(selectedLight < 0)
			selectedLight = MAX_LIGHTS-1;
	}

	// Go to next light source
	else if(key == GLUT_KEY_F2){
		selectedLight++;
		
		if(selectedLight > MAX_LIGHTS-1)
			selectedLight = 0;
	}

	// Go to previous attribute
	if(key == GLUT_KEY_F3){
		selectedAttribute--;
		
		if(selectedAttribute < 0)
			selectedAttribute = N_ATT-1;
	}

	// Go to next attribute
	else if(key == GLUT_KEY_F4){
		selectedAttribute++;
		
		if(selectedAttribute > N_ATT-1)
			selectedAttribute = 0;
	}

	if(key == GLUT_KEY_F9)
		showControls = !showControls;
	if(key == GLUT_KEY_F10)
		showDebug =  !showDebug;

	else skeys[key] = true; 
}
