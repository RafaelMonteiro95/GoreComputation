/* Main source file

	Giovanna Oliveira Guimarães		-	9293693
	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095

*/

#include "camera.hpp"
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
	glutKeyboardFunc(keyboardUp);
	glutKeyboardUpFunc(keyboardDown);
	glutSpecialFunc(specialDown);
	glutSpecialUpFunc(specialUp);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 1;
}

