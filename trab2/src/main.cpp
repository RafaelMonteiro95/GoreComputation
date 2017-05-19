/* Main source file

	Giovanna Oliveira Guimarães		-	9293693
	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095

*/

#include <math.h>
#include <GL/glut.h>

#include "callbacks.hpp"

int main(int argc, char *argv[]) {

	// Initializa my things 
	myInit();

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(1400, 900);
	g_WindowHandle = glutCreateWindow("FreeGluteos3D v2.0");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(update);
	glutKeyboardFunc(keyboardDown);
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialFunc(specialDown);
	glutSpecialUpFunc(specialUp);

	// OpenGL lightning
	float angle[] = {1,1,0};
	float ambient[] = {0,0,0,1};
	float diffuse[] = {1,1,1,1};
	float specular[] = {1,1,1,1};

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, angle);
	glLightfv(GL_LIGHT0, GL_AMBIENT, angle);
	// glLightfv(GL_LIGHT0, GL_DIFFUSE, angle);
	// glLightfv(GL_LIGHT0, GL_SPECULAR, angle);
    
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}

