/*==================================================================================================
 PROGRAMMERS:			Hailey Martinelli, Quy Pham, Nathan Pasley, Evan Politte
 TRACE FOLDEER:			Hailey555, quy123, ?, ?
 ASSIGNMENT:			Proj2
 COURSE:				CSC 525
 MODIFIED BY:			N/A
 LAST MODIFIED DATE:	11/11/2019
 DESCRIPTION:			Creating a text editor
 NOTE:					PUT WHAT EACH PERSON DID HERE
 FILES:					proj2.cpp, (labProject.sln, ...)
 IDE/COMPILER:			MicroSoft Visual Studio 2019
 INSTRUCTION FOR COMPILATION AND EXECUTION:
	1.		Double click on labProject folder
    2.		Double click on	labProject.sln  to OPEN the project
	3.		Press Ctrl+F7					to COMPILE
	4.		Press Ctrl+F5					to EXECUTE
==================================================================================================*/
#include <string>
#include <iostream>
#include <fstream>
#include <GL/glut.h>				// include GLUT library
using namespace std;
//***********************************************************************************
//to make 30 rows and 30 columns, we can specify how big a letter is in pixels and then when 
//creating the window size multiply that pixels size by 30?
string userMessage;
string color;
void * font = GLUT_BITMAP_TIMES_ROMAN_24;
int xMouse = 0;
int yMouse = 0;
int btn;
bool clicked = false;


void drawPoints()
{
	glPointSize(7);		// change point size to 10
	glRasterPos2i(xMouse, yMouse); //starting position of message
	glColor3i(1, 1, 1);

	for (int i = 0; i < userMessage.length(); i++) {
		glutBitmapCharacter(font, userMessage[i]);
	}

 

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
	glRasterPos2i(xMouse, yMouse);
	

	glFlush(); // flush out the buffer contents
}

void myKeyCallback(unsigned char key, int cursorX, int cursorY) 
{
	userMessage += key;
	xMouse = cursorX - 200;
	yMouse = 200 - cursorY;
	myDisplayCallback();
}

void myMovementCallback(int cursorX, int cursorY) 
{
	xMouse = cursorX - 200;
	yMouse = 200 - cursorY;
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

void saveFile()
{
	ofstream fout;
	string fileLocation = "C:\\Temp\\", fileName = "typed.txt";
	fout.open(fileLocation + fileName);
	for (int i = 0; i < userMessage.length(); i++) {
		fout << userMessage[i];
	}
	fout.close();
}

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
	case 4: saveFile();
		break;
	}
}

//***********************************************************************************
int main(int argc, char ** argv)
{
	 glutInitWindowSize(400, 400);				// specify a window size
	 glutInitWindowPosition(100, 0);			// specify a window position
	 glutCreateWindow("Simple Point Drawing");	// create a titled window

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
	 glutMotionFunc(myMovementCallback);

	 glutMainLoop();							// get into an infinite loop

	 return 0;
}
