
/*==================================================================================================
 PROGRAMMERS:			Hailey Martinelli, Quy Pham, Nathan Pasley, Evan Politte
 TRACE FOLDEER:			Hailey555, quy123, Pollitt96, pasley3
 ASSIGNMENT:			Proj2
 COURSE:				CSC 525
 MODIFIED BY:			N/A
 LAST MODIFIED DATE:	11/10/2019
 DESCRIPTION:			Creating a text editor
 NOTE:					Pollitt96 - Backspace key works, until it reaches last character, does not erase.
						Hailey555 - created menus, saved text to typed.txt file
						quy123 -
						? -
 FILES:					proj2.cpp, (labProject.sln, ...)
 IDE/COMPILER:			MicroSoft Visual Studio 2019
 INSTRUCTION FOR COMPILATION AND EXECUTION:
	1.		Double click on labProject folder
	2.		Double click on	labProject.sln  to OPEN the project
	3.		Press Ctrl+F7					to COMPILE
	4.		Press Ctrl+F5					to EXECUTE
==================================================================================================*/
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <GL/glut.h>				// include GLUT library
using namespace std;
//***********************************************************************************
int color = 0, fontInteger = 0;
vector<string> userMessage = { "", "00" };
void* font = GLUT_BITMAP_TIMES_ROMAN_24;
int xpos = -180;
int ypos = 180;


void changeTextColor(int tempColor) {
	switch (tempColor) {
	case 1: glColor3i(0, 0, 1);
		cout << "its red";
		break;
	case 2: glColor3i(1, 0, 0);
		break;
	case 3: glColor3i(0, 1, 0);
		break;
	case 0: glColor3i(0, 0, 0);
		break;
	}
}

void changeFont(int tempFont) {
	switch (tempFont) {
	case 1: font = GLUT_BITMAP_HELVETICA_18;
		cout << "yay" << endl;
		break;
	case 2: font = GLUT_BITMAP_TIMES_ROMAN_10;
		break;
	case 3: font = GLUT_BITMAP_HELVETICA_10;
		break;
	case 0: font = GLUT_BITMAP_TIMES_ROMAN_24;
		break;
	}
}

void writeText()
{
	glClear(GL_COLOR_BUFFER_BIT);

	int startX = xpos;
	int startY = ypos;
	glRasterPos2i(startX, startY);

	for (int i = 0; i < userMessage.size(); i += 2) {
		int lastCharPosArr[4];
		glGetIntegerv(GL_CURRENT_RASTER_POSITION, lastCharPosArr);

		changeTextColor((int)userMessage.at(i + 1)[1] - 48);
		//cout << "hello" << userMessage.at(i + 1)[1] << endl;
		glRasterPos2i(lastCharPosArr[0] - 200, startY);

		for (int j = 0; j < userMessage.at(i).size(); j++) {
			int lastPosX = 180;
			int lastCharPosArr[4];
			glGetIntegerv(GL_CURRENT_RASTER_POSITION, lastCharPosArr);

			if (lastCharPosArr[0] - 200 >= lastPosX) {
				startY -= 25;
				startX = -180;
				glRasterPos2i(startX, startY);
			}

			if (userMessage[i][j] == '\n') {
				startY -= 20;
				startX = xpos;
				glRasterPos2i(startX, startY);
			}
			else {
				changeFont((int)userMessage.at(i + 1)[0] - 48);
				glutBitmapCharacter(font, userMessage.at(i)[j]);
			}
		}
	}

	glFlush();
}


//***********************************************************************************
void myInit()
{
	glClearColor(1, 1, 1, 0);			// specify a background clor: white 
	gluOrtho2D(-200, 200, -200, 200);  // specify a viewing area
}

//***********************************************************************************
void myDisplayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT);	// draw the background

	writeText();


	glFlush(); // flush out the buffer contents
}

void myKeyCallback(unsigned char key, int cursorX, int cursorY)
{
	if (key == 8 && userMessage.at(userMessage.size() - 2).size() >= 0) {
		string temp;

		if (userMessage.at(userMessage.size() - 2).size() < 1 && userMessage.size() > 2) {
			userMessage.pop_back();
			userMessage.pop_back();
		}
		for (int i = 0; i < userMessage.at(userMessage.size() - 2).size() - 1 && userMessage.at(userMessage.size() - 2).size() > 1; i++) {
			temp += userMessage.at(userMessage.size() - 2)[i];
		}
		userMessage.at(userMessage.size() - 2) = temp;
	}
	else {
		if (color != (int)(userMessage.at(userMessage.size() - 1)[1]) - 48 || fontInteger != (int)(userMessage.at(userMessage.size() - 1)[0]) - 48) {
			//cout << "hi" << userMessage.at(userMessage.size() - 1)[1] << endl;
			string temp = "";
			temp += key;
			userMessage.push_back(temp);
			userMessage.push_back(to_string(fontInteger) + to_string(color));
		}
		else {
			if (key == 13) {
				userMessage.at(userMessage.size() - 2) += "\n";
			}
			else {
				if (key != 8) {
					userMessage.at(userMessage.size() - 2) += key;
				}
			}
		}
	}

	writeText();
}

void myMouseCallback(int button, int state, int cursorX, int cursorY)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		xpos = cursorX - 200;
		ypos = 200 - cursorY;
	}
	writeText();
}

void colorMenuCallback(int entryId)
{
	switch (entryId) {
	case 1: color = 1;
		cout << "new color" << endl;
		break;
	case 2: color = 2;
		break;
	case 3: color = 3;
		break;
	}
}

/*void saveFile()
{
	ofstream fout;
	string fileLocation = "C:\\Temp\\", fileName = "typed.txt";
	fout.open(fileLocation + fileName);
	for (int i = 0; i < userMessage.length(); i++) {
		fout << userMessage[i];
	}
	fout.close();
}*/

void fontMenuCallback(int entryId)
{
	switch (entryId) {
	case 1:  font = GLUT_BITMAP_HELVETICA_18;
		cout << "new font" << endl;
		fontInteger = 1;
		break;
	case 2: font = GLUT_BITMAP_TIMES_ROMAN_10;
		fontInteger = 2;
		break;
	case 3: font = GLUT_BITMAP_HELVETICA_10;
		fontInteger = 3;
		break;
	}
}

void parentMenuCallback(int entryId)
{
	switch (entryId) {
	case 3: exit(0);
		//case 4: saveFile();
		//	break;
	}
}

//***********************************************************************************
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitWindowSize(400, 400);				// specify a window size
	glutInitWindowPosition(100, 0);			// specify a window position
	glutCreateWindow("Text Editor");	// create a titled window

	myInit();									// setting up

	int colorMenu = glutCreateMenu(colorMenuCallback);
	glutAddMenuEntry("Blue", 1);
	glutAddMenuEntry("Red", 2);
	glutAddMenuEntry("Green", 3);

	int fontMenu = glutCreateMenu(fontMenuCallback);
	glutAddMenuEntry("Helvetica 18", 1);
	glutAddMenuEntry("Times 10", 2);
	glutAddMenuEntry("Helvatica 10", 3);

	glutCreateMenu(parentMenuCallback);
	glutAddSubMenu("Color", colorMenu);
	glutAddSubMenu("Font", fontMenu);
	glutAddMenuEntry("Exit", 3);
	glutAddMenuEntry("Save Text", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);


	glutDisplayFunc(myDisplayCallback);		// register a callback
	glutKeyboardFunc(myKeyCallback);
	//glutMouseFunc(myMouseCallback);

	glutMainLoop();							// get into an infinite loop

	return 0;
}

