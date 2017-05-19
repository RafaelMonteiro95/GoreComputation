/* Main source file

	Giovanna Oliveira Guimarães		-	9293693
	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095

*/

#include "callbacks.hpp"
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <math.h>

int main(int argc, char *argv[]) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	g_WindowHandle = glutCreateWindow("FreeGluteos3D v2.0");

	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(Update);
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

