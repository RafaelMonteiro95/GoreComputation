/* Drawing source file

	Giovanna Oliveira Guimarães		-	9293693
	Lucas Alexandre Soares 			-	9293265
	Rafael Augusto Monteiro 		-	9293095

*/


#include <math.h>
#include <GL/glut.h>

#include "draw.hpp"

#define HIGHLIGHTED 0.5f, 0.2f, 0.9f
#define NOT_HIGHLIGHTED 0.3f, 0.3f, 0.3f

//color array
GLfloat color[] = {0.0f, 0.0f, 0.0f, 1.0f};

void applyTransform(Transform* obj){
	glTranslatef(obj->position->x, obj->position->y + 0.7, obj->position->z);
	glScalef(obj->scale->x + 1, obj->scale->y + 1, obj->scale->z + 1);

	glRotatef(obj->rotation->x, 1.0f, 0.0f, 0.0f);
	glRotatef(obj->rotation->y, 0.0f, 1.0f, 0.0f);
	glRotatef(obj->rotation->z, 0.0f, 0.0f, 1.0f);
}

void drawSnowman(Transform* snowman) {

	glPushMatrix();

	applyTransform(snowman);

	// glColor3f(0.2f, 0.3f, 0.9f);
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
	// glColor3f(0.0f, 0.0f, 0.0f);
	glTranslatef(0.05f, 0.10f, 0.36f);
	glutSolidSphere(0.1f,20,20);
	glTranslatef(-0.1f, 0.0f, 0.0f);
	glutSolidSphere(0.1f,20,20);
	glPopMatrix();

	// Draw Nose
	// glColor3f(1.0f, 0.5f , 0.5f);
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
	// glColor3f(0.6f, 0.2f, 0.3f);
	glNormal3d(0, 1, 0);
	color[0] = 1.0f;
	color[1] = 1.2f;
	color[2] = 1.3f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);

	// glTranslatef(0.0f, 2.5f, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glutSolidCone(0.8, -2.5, 20, 5);

	// Draw icecream
	// glColor3f(1.0f, 0.6f, 1.0f);
	glutSolidSphere(0.75f, 20, 20);
}

void drawTorus(Transform* torus, bool selected){

	applyTransform(torus);

	glNormal3d(0, 1, 0);
	color[0] = 1.0f;
	color[1] = 1.2f;
	color[2] = 1.3f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);

	glRotatef(90,1,0,0);

	// selected? glColor3f(HIGHLIGHTED): glColor3f(NOT_HIGHLIGHTED);
	glutSolidTorus(0.4f, 0.7f, 20, 20);
}

void drawCube(Transform* cube, bool selected){

	applyTransform(cube);

	glNormal3d(0, 1, 0);
	color[0] = 1.0f;
	color[1] = 1.2f;
	color[2] = 1.3f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, color);


	// selected? glColor3f(HIGHLIGHTED): glColor3f(NOT_HIGHLIGHTED);
	glutSolidCube(1.5f);

}

void drawSky(){
	glColor3f(0.0f,0.0f,1.0f);
	glutSolidSphere(60.0f,5,5);
}

void drawGround(){

	glBegin(GL_QUADS);

		glColor3f(255.0f, 255.0f, 255.0f);
		glVertex3f(-30.0f, 0.0f, -30.0f);

		glColor3f(255.0f, 0.0f, 255.0f);
		glVertex3f(-30.0f, 0.0f,  30.0f);

		glColor3f(255.0f, 255.0f, 0.0f);
		glVertex3f( 30.0f, 0.0f,  30.0f);

		glColor3f(0.0f, 255.0f, 255.0f);
		glVertex3f( 30.0f, 0.0f, -30.0f);

	glEnd();

	drawSky();
}


void drawTeapot(Transform* teapot, bool selected) {

	glPushMatrix();

	// Apllies transformations
	applyTransform(teapot);

	// Draws obj
	selected? glColor3f(HIGHLIGHTED): glColor3f(NOT_HIGHLIGHTED);
	// selected? glColorMaterial(GL_FRONT): glColor3f(NOT_HIGHLIGHTED);
	glutSolidTeapot(0.7f);

	glPopMatrix();

}