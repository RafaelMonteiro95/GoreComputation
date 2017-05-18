/* Camera header file

	Giovanna Oliveira Guimarães		-	9293693
	Lucas Alexandre Soares 			-	9293265
	Rafael Jureg Monteiro 			-	9293095

*/

#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

int g_handle = -1;

bool setSpeed(float speed);
void drawSnowMan();
void drawBatata();
void drawPotato();
void renderScene(void);
void changeSize(int w, int h);
void processSpecialKeys(int key, int xx, int yy);
void processNormalKeys(unsigned char key, int g_camx, int y);

#endif