/* Camera header file

	Giovanna Oliveira Guimarães		-	9293693
	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095

*/

#ifndef _CALLBACKS_HPP_
#define _CALLBACKS_HPP_

extern int g_WindowHandle;

void myInit();
void myCleanup();
bool setSpeed(float speed);
void drawBatata();
void drawSnowMan();
void drawPotatoIceCream();
void Update(void);
void renderScene(void);
void changeSize(int w, int h);
void keyboardUp(unsigned char key, int x, int y);
void keyboardDown(unsigned char key, int x, int y);
void specialUp(int key, int x, int y);
void specialDown(int key, int x, int y);
void initKeys();

#endif