/*==================================================================================================
 PROGRAMMERS:			Hailey Martinelli, Quy Pham, Nathan Pasley, Evan Politte
 TRACE FOLDEER:			Hailey555, quy123, Pollitt96, ?
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
#include <glut.h>				// include GLUT library
using namespace std;
//***********************************************************************************
const int ROW = 30;
const int COL = 30;
int curRow = 0, curCol = 0;
vector<vector<int>> userMessage = vector<vector<int>>(ROW, vector<int>(COL));


//string userMessage;
string color;
void * font = GLUT_BITMAP_TIMES_ROMAN_24;
int xMouse = 0;
int yMouse = 0;
int btn;
bool clicked = false;
bool nextLine = false;
int startX = -180;
int startY = 180;


void drawPoints()
{
	glPointSize(7);		
	glColor3i(1, 1, 1);
	glRasterPos2i(startX, startY); 

	//for (int r = 0; r < ROW; r++) {
	//	for (int c = 0; c < COL; c++) {
	glutBitmapCharacter(font, userMessage[curRow][curCol]);
	cout << curRow << endl << curCol;
	//	}
	//}
	/*for (int i = 0; i < userMessage.length(); i++) {
		glutBitmapCharacter(font, userMessage[i]);
	}*/
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

	if (color == "blue") {
		glColor3f(0, 0, 1);
	}
	if (color == "red") {
		glColor3f(1, 0, 0);
	}
	if (color == "green") {
		glColor3f(0, 1, 0);
	}
	drawPoints();
	

	glFlush(); // flush out the buffer contents
}

void myKeyCallback(unsigned char key, int cursorX, int cursorY) 
{
	if (key == 8)
	{
		if (sizeof(userMessage) >= 1)
		{
			userMessage[curRow].pop_back();
		}
		else if (sizeof(userMessage) == 0)
		{
			userMessage.clear();
		}
	}
	else if (key == 13) {
		startY -= 20;
	}
	else {
		//userMessage += key;
		if (curCol == 29) {
			curRow++;
			curCol = 0;
		}
		userMessage[curRow][curCol] = key;
		curCol++;
	}

	myDisplayCallback();
}

void myMouseCallback(int button, int state, int cursorX, int cursorY)
{
	if (button == GLUT_LEFT_BUTTON) {
		if (sizeof(userMessage) == 0) {
			startX = cursorX - 200;
			startY = 200 - cursorY;
		}
	}
	myDisplayCallback();
}

void colorMenuCallback(int entryId) 
{
	switch (entryId) {
		case 1: color = "blue";
			myDisplayCallback();
			break;
		case 2: color = "red";
			myDisplayCallback();
			break;
		case 3: color = "green";
			myDisplayCallback();
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
			myDisplayCallback();
			break;
		case 2: font = GLUT_BITMAP_TIMES_ROMAN_10;
			myDisplayCallback();
			break;
		case 3: font = GLUT_BITMAP_HELVETICA_10;
			myDisplayCallback();
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
int main(int argc, char ** argv)
{
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
	 glutMouseFunc(myMouseCallback);

	 glutMainLoop();							// get into an infinite loop

	 return 0;
}
