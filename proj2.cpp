/*==================================================================================================
 PROGRAMMERS:			Hailey Martinelli, Quy Pham, Nathan Pasley, Evan Politt
 TRACE FOLDEER:			Hailey555, quy123, Pollitt96, ?
 ASSIGNMENT:			Proj2
 COURSE:				CSC 525
 MODIFIED BY:			N/A
 LAST MODIFIED DATE:	11/11/2019
 DESCRIPTION:			Creating a text editor
 NOTE:					PUT WHAT EACH PERSON DID HERE
						Pollitt96 - Backspace key works
									Working info screen, with visibility working
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
#include <glut.h>				// include GLUT library
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
bool help = true;
int win1, win2;
void* font2 = GLUT_BITMAP_HELVETICA_18;


void drawBitmapText(float x, float y, void* font, const char* string)
{
	const char* c;
	glRasterPos2f(x, y);

	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(font, *c);
	}
}

void drawPoints()
{
	glPointSize(7);		// change point size to 10
	glRasterPos2i(xMouse, yMouse); //starting position of message
	glColor3i(1, 1, 1);

	for (int i = 0; i < userMessage.length(); i++) {
		glutBitmapCharacter(font, userMessage[i]);
		if (userMessage.length() >= 30)
		{
			glRasterPos2i(xMouse, yMouse + 10);
		}
	}

}

void helpText()
{
	glColor3f(0, 0, 0);
	drawBitmapText(-190, 170, (void*)font2, "Left click to set text starting position. If you don't click, text begins in upper left corner");
	drawBitmapText(-190, 130, (void*)font2, "Type to have it show up on window. Text can contain 30 characters before going to next row.");
	drawBitmapText(-190, 90, (void*)font2, "There can be up to 30 rows before you can no longer type.");
	drawBitmapText(-190, 50, (void*)font2, "Left click typed text and drag mouse to move text along the window");
	drawBitmapText(-190, 10, (void*)font2, "Right click brings up a menu with submenus allowing you to change font and font color");
	drawBitmapText(-190, -30, (void*)font2, "Press BACKSPACE to go back a character, or previous line if at beginning of a line");
	drawBitmapText(-190, -70, (void*)font2, "Press ENTER to go down to the beginning of the next row");
	drawBitmapText(-190, -110, (void*)font2, "To hide help menu, select help menu window and press ESC");

}

//***********************************************************************************
void myInit()
{
	glClearColor(1, 1, 1, 0);			// specify a background clor: white 
	gluOrtho2D(-200, 200, -200, 200);  // specify a viewing area
}

void myInit2()
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

void myDisplayCallback2()
{
	glClear(GL_COLOR_BUFFER_BIT);	// draw the background
	helpText();

	glFlush(); // flush out the buffer contents
}

void myKeyCallback(unsigned char key, int cursorX, int cursorY) 
{
	
	if (key == 8)                 //BACKSPACE key
	{
		if (userMessage.length() >= 1)
		{
			userMessage.pop_back();
			xMouse = cursorX - 200;
			yMouse = 200 - cursorY;
			myDisplayCallback();
		}
		else if (userMessage.length() == 0)
		{
			userMessage.clear();
			xMouse = cursorX - 200;
			yMouse = 200 - cursorY;
			myDisplayCallback();
		}
	}
	else
	{
		userMessage += key;
		xMouse = cursorX - 200;
		yMouse = 200 - cursorY;
		myDisplayCallback();
	}

	switch (key)
	{
	case 32:                     //ENTER key
		
		break;
	}
}

void myKeyCallback2(unsigned char key, int cursorX, int cursorY) {
	switch (key)                //ESC key
	{
	case 27:
		help = false;
		glutHideWindow();
		myDisplayCallback2();
		break;
	}
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
	case 3: help = true;
		glutSetWindow(win2);
		glutShowWindow();
		myDisplayCallback2();
		break;
	case 4: exit(0);
	case 5: saveFile();
		break;
	}
}

void visible(int state)
{
	if (help == false)
	{
		state == GLUT_NOT_VISIBLE;
		myDisplayCallback2();
	}
	else
	{
		help == true;
		state == GLUT_VISIBLE;
		myDisplayCallback2();
	}
}

//***********************************************************************************
int main(int argc, char ** argv)
{
	 glutInitWindowSize(400, 400);				// specify a window size
	 glutInitWindowPosition(100, 100);			// specify a window position
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
	 glutAddMenuEntry("Help", 3);
	 glutAddMenuEntry("Exit", 4);
	 glutAddMenuEntry("Save Text", 5);
	 glutAttachMenu(GLUT_RIGHT_BUTTON);


	 glutDisplayFunc(myDisplayCallback);		// register a callback
	 glutKeyboardFunc(myKeyCallback);
	 //glutMouseFunc(myMouseCallback);
	 glutMotionFunc(myMovementCallback);


	 //info window
	 glutInitWindowSize(800, 400);
	 glutInitWindowPosition(550, 100);
	 win2 = glutCreateWindow("Help Window");

	 myInit2();

	 glutDisplayFunc(myDisplayCallback2);
	 glutKeyboardFunc(myKeyCallback2);
	 glutVisibilityFunc(visible);

	 glutMainLoop();							// get into an infinite loop

	 return 0;
}
