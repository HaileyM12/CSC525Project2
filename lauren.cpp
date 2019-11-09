/*==================================================================================================
PROGRAMMER:			    Derrick Box (\Box241) 50% 
                        Lauren Tallerico (\Tallerico322) 50% 
                        Equal amounts of effort were given for this program.
                        However, the menu-bar and its attachments are all thanks to Derrick!
COURSE:				    CSC 525
MODIFIED BY:		    N/A
LAST MODIFIED DATE:	    11/7/2018
DESCRIPTION:			Project 2:  a text editor that allows font/color changes and can save text to a file
NOTE:					N/A
FILES:					proj02, (projProject.sln)
IDE/COMPILER:			MicroSoft Visual Studio 2017
INSTRUCTION FOR COMPILATION AND EXECUTION:
1.		Double click on projProject.sln	to OPEN the project
2.		Press Ctrl+F7					to COMPILE
3.		Press Ctrl+F5					to EXECUTE
==================================================================================================*/
#include <iostream>
#include <string>
#include <GL\glut.h>
//#include <glut.h>				// include GLUT library
#include <math.h> 
#include <vector>
#include <fstream>

int x = 0, y = 0;
int  posX = -(glutGet(GLUT_SCREEN_WIDTH) / 2) + 15, posY = (glutGet(GLUT_SCREEN_HEIGHT) / 2) - 50;
int color = 0, fontInt = 0, fontWidth = 8, fontHeight = 13;
int shadedWindow, helpWindow, mainWindow, menuFile[] = { -1,0 }, menuColor[] = { -1,0 }, menuFont[] = { -1,0 };
int menuState = 0;
void * font = GLUT_BITMAP_8_BY_13;
std::vector<std::string> text = { "", "00" };

void drawColorSquare(int x, int y, int color);
void closeMenus();
void renderText();
void textColor(int tempColor);
void textFont(int tempFont);
void drawFileCallback();
void drawColorCallback();
void drawFontCallback();
void getInput(unsigned char key, int cursorX, int cursorY);
void saveFile();

//Help Menu Items----------------------------------------------------------------------------------------------
void writeHelp() {  // Gives information and instructions on how to use this program
	glutSetWindow(helpWindow);
	std::string title = "Help Menu";
	std::string name = "MORD TEXT EDITOR";
	std::string def = "A program that allows you to choose different fonts and colors as you type.";
	std::string useTitle = "TO USE MORD EDITOR:";
	std::string use = "Click off this window to start typing.";
	std::string use1 = "Default location is top left. Otherwise, indicate start location by mouseclick.";
	std::string use2 = "Click the menu bars shown on the top left to edit your text.";
	std::string use3 = "Options allow color change and font change.";
	std::string save = "TO SAVE TEXT:";
	std::string save1 = "click on 'File' and then 'Save'.";
	std::string save2 = "text will be saved as 'typed.txt' in 'C:\TEMP'.";
	std::string exit = "TO CLOSE PROGRAM:";
	std::string exit1 = "press 'esc' OR  click on 'File' and then 'Exit'";

	glColor3f(0, 0, 0);
	glRasterPos2i(-50, 185);
	for (unsigned int i = 0; i < title.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, title[i]);
	}
	glColor3f(0, 0, 1);
	glRasterPos2i(-85, 140);
	for (unsigned int i = 0; i < name.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, name[i]);
	}
	glRasterPos2i(-350, 120);
	for (unsigned int i = 0; i < def.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, def[i]);
	}
	glRasterPos2i(-95, 70);
	for (unsigned int i = 0; i < useTitle.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, useTitle[i]);
	}
	glRasterPos2i(-180, 50);
	for (unsigned int i = 0; i < use.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, use[i]);
	}
	glRasterPos2i(-350, 30);
	for (unsigned int i = 0; i < use1.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, use1[i]);
	}
	glRasterPos2i(-275, 10);
	for (unsigned int i = 0; i < use2.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, use2[i]);
	}
	glRasterPos2i(-200, -10);
	for (unsigned int i = 0; i < use3.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, use3[i]);
	}
	glRasterPos2i(-65, -60);
	for (unsigned int i = 0; i < save.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, save[i]);
	}
	glRasterPos2i(-150, -80);
	for (unsigned int i = 0; i < save1.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, save1[i]);
	}
	glRasterPos2i(-220, -100);
	for (unsigned int i = 0; i < save2.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, save2[i]);
	}
	glRasterPos2i(-85, -150);
	for (unsigned int i = 0; i < exit.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, exit[i]);
	}
	glRasterPos2i(-220, -170);
	for (unsigned int i = 0; i < exit1.length(); i++) {
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, exit1[i]);
	}
	glFlush();
}
//--  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  ----
void closeHelp(int id) { // closes shadedWindow which includes helpWindow
	glutDestroyWindow(shadedWindow);
	glutSetWindow(mainWindow);
}
//--  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  ----
void helpCallback() {    // callback for helpWindow // enables right click menu to close window
	glClear(GL_COLOR_BUFFER_BIT);
    
    // enables right click menu to close window
	int fontMenu = glutCreateMenu(closeHelp);
	glutAddMenuEntry("Close Help", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    // renders text for information and instructions
	writeHelp();
}
//--  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  ----
void openHelp() {   // opens sub-window helpWindow 
	int x = ((glutGet(GLUT_SCREEN_WIDTH) - 800) / 2);
	int y = (glutGet(GLUT_SCREEN_HEIGHT) - 400) / 2;
    // this window is attached to shadedWindow
	helpWindow = glutCreateSubWindow(shadedWindow, x, y, 800, 400);
	glClearColor(1, 1, 1, 0);
	gluOrtho2D(-400, 400, -200, 200);
	glutDisplayFunc(helpCallback);
}
//--  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  ----
void shadedWindowCallBack() {   // callback for shadedWindow
	glClear(GL_COLOR_BUFFER_BIT);
	openHelp(); // opens helpWindow
}
//--  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  ----
void shadedMouseClickFunction(int button, int state, int x, int y) { 
    // closes shadedWindow, including helpWindow if clicked outside of helpWindow
	if (state == GLUT_DOWN) {
		glutDestroyWindow(shadedWindow);
		glutSetWindow(mainWindow);
	}
}
//--  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  ----
void openShaded() { // opens shadedWindow, including helpWindow
	int x = glutGet(GLUT_SCREEN_WIDTH);
	int y = glutGet(GLUT_SCREEN_HEIGHT);
	shadedWindow = glutCreateSubWindow(mainWindow, -x / 2, -y / 2, x, y);
	glClearColor(.75, .75, .75, .015);
	gluOrtho2D(-1 * x / 2, y / 2,
		-1 * glutGet(GLUT_SCREEN_HEIGHT) / 2, glutGet(GLUT_SCREEN_HEIGHT) / 2);
	glutDisplayFunc(shadedWindowCallBack);
	glutMouseFunc(shadedMouseClickFunction);
}
//Menu Bar Items----------------------------------------------------------------------------------------------
void drawMenuItem(int x, int y, std::string word, int fontChoice) { // font switch statement for menu
	glColor3ub(0, 0, 0);
	glRasterPos2f(x, y);
	if (fontChoice != 0) {
		void * tempfont;
		switch (fontChoice) {
		case 1:
			tempfont = GLUT_BITMAP_8_BY_13;
			break;
		case 2:
			tempfont = GLUT_BITMAP_9_BY_15;
			break;
		case 3:
			tempfont = GLUT_BITMAP_HELVETICA_10;
			break;
		case 4:
			tempfont = GLUT_BITMAP_HELVETICA_18;
			break;
		case 5:
			tempfont = GLUT_BITMAP_TIMES_ROMAN_10;
			break;
		case 6:
			tempfont = GLUT_BITMAP_TIMES_ROMAN_24;
			break;
		default:
			tempfont = GLUT_BITMAP_8_BY_13;
			break;

		}
		for (int i = 0; i < word.size(); i++)
			glutBitmapCharacter(tempfont, word[i]);
	}
	else {
		for (int i = 0; i < word.size(); i++)
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, word[i]);
	}
}

//--  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  ----
void drawMenuSquare(int x, int x2) {    // draws menu by polygon
	int sWidth = glutGet(GLUT_SCREEN_WIDTH) / 2;
	int sHeight = glutGet(GLUT_SCREEN_HEIGHT) / 2;

	glBegin(GL_POLYGON);
	glColor3ub(133, 134, 135);
	glVertex2f((sWidth * -1) + x, sHeight);
	glVertex2f((sWidth * -1) + x + x2, sHeight);
	glVertex2f((sWidth * -1) + x + x2, sHeight - 30);
	glVertex2f((sWidth * -1) + x, sHeight - 30);
	glEnd();

    // sub menus are shaded based on mouseHover
	glColor3ub(196, 197, 198);
	if (x == 0)
		if (menuState == 1 || menuState == 3 || menuState == 5 || menuState == 7)
			glColor3ub(133, 134, 135);
	if (x == 75)
		if (menuState == 2 || menuState == 3 || menuState == 6 || menuState == 7)
			glColor3ub(133, 134, 135);
	if (x == 175)
		if (menuState >= 4)
			glColor3ub(133, 134, 135);


	glBegin(GL_POLYGON);
	glVertex2f((sWidth * -1) + x + 2, sHeight - 2);
	glVertex2f((sWidth * -1) + x + x2 - 2, sHeight - 2);
	glVertex2f((sWidth * -1) + x + x2 - 2, sHeight - 27);
	glVertex2f((sWidth * -1) + x + 2, sHeight - 27);
	glEnd();
}

//--  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  ----
void drawMenuBar() {    // draws menu bar with options "File", "Color", and "Font"

	int sWidth = glutGet(GLUT_SCREEN_WIDTH) / 2;
	int sHeight = glutGet(GLUT_SCREEN_HEIGHT) / 2;

	glBegin(GL_POLYGON);
	glColor3ub(196, 197, 198);
	glVertex2f((sWidth * -1), sHeight);
	glVertex2f(sWidth, sHeight);
	glVertex2f(sWidth, sHeight - 30);
	glVertex2f((sWidth * -1), sHeight - 30);
	glEnd();

	drawMenuSquare(0, 75);
	drawMenuItem((sWidth * -1) + 15, sHeight - 18, "File", 0);
	drawMenuSquare(75, 100);
	drawMenuItem((sWidth * -1) + 110, sHeight - 18, "Color", 0);
	drawColorSquare((sWidth * -1) + 105, sHeight - 18, 7);
	drawMenuSquare(175, 100);
	drawMenuItem((sWidth * -1) + 215, sHeight - 18, "Font", 0);
	drawColorSquare((sWidth * -1) + 210, sHeight - 22, -1); // shows current color in little square
	glRasterPos2f((sWidth * -1) + 190, sHeight - 23);
	textFont(-1);
	glutBitmapCharacter(font, 'F'); // Shows current font in little square

	glFlush();
}

//Menu Bar Sub Items------------------------------------------------------------------------------------------
void drawSubMenuSelection(int y, int menu) { // creates boxes for File, Color, and Font menus
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3ub(133, 134, 135);
	switch (menu) {
	case 1:
		drawFileCallback();
		glBegin(GL_LINE_LOOP);
		glVertex2f(-36, 70 - y);
		glVertex2f(36, 70 - y);
		glVertex2f(36, 70 - y - 30);
		glVertex2f(-36, 70 - y - 30);
		glEnd();
		glFlush();
		break;
	case 2:
		drawColorCallback();
		glColor3ub(133, 134, 135);
		glBegin(GL_LINE_LOOP);
		glVertex2f(-50, 120 - y);
		glVertex2f(50, 120 - y);
		glVertex2f(50, 120 - y - 30);
		glVertex2f(-50, 120 - y - 30);
		glEnd();
		glFlush();
		break;
	case 3:
		drawFontCallback();
		glBegin(GL_LINE_LOOP);
		glVertex2f(-39, 120 - y + 2);
		glVertex2f(49, 120 - y + 2);
		glVertex2f(49, 120 - y - 30);
		glVertex2f(-39, 120 - y - 30);
		glEnd();
		glFlush();
		break;
	default:
		break;
	}
}

//--  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  ----
void fileMouseClickFunction(int button, int state, int x, int y) { // file menu instructions
	// if "clear" is selected, reset everything
    if (state == GLUT_DOWN && y < 35) {
		text = { "","00" }; // reset vector
		posX = -(glutGet(GLUT_SCREEN_WIDTH) / 2) + 15; // reset start position X
		posY = (glutGet(GLUT_SCREEN_HEIGHT) / 2) - 50; // reset start position Y
		color = 0;    // reset color to default
		fontInt = 0;  // reset font to default
		closeMenus();
	}  // if "save" is selected, save typed.txt
	if (state == GLUT_DOWN && y > 35 && y < 70) {
		saveFile();
		closeMenus();
	}  // if "help" is selected, open shadedWindow (includes helpWindow)
	if (state == GLUT_DOWN && y > 70 && y < 105) {
		openShaded();
		closeMenus();
	}  // if "exit" is selected, exit!
	if (state == GLUT_DOWN && y > 105 && y < 135) {
		exit(0);
	}
}

//--  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  ----
void fileMousePassiveFunction(int x, int y) { // enables the shading based on hover
	if (y < 35 && y > 0) {
		drawSubMenuSelection(0, 1);
	}
	if (y > 35 && y < 70) {
		drawSubMenuSelection(35, 1);
	}
	if (y > 70 && y < 105) {
		drawSubMenuSelection(70, 1);
	}
	if (y > 105 && y < 135) {
		drawSubMenuSelection(105, 1);
	}
}

//--  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  ----
void colorMouseClickFunction(int button, int state, int x, int y) { // changes text color upon mouse-click
	if (state == GLUT_DOWN && y < 30) {
		color = 0;
		closeMenus();
	}
	if (state == GLUT_DOWN && y > 30 && y < 60) {
		color = 1;
		closeMenus();
	}
	if (state == GLUT_DOWN && y > 60 && y < 90) {
		color = 2;
		closeMenus();
	}
	if (state == GLUT_DOWN && y > 90 && y < 120) {
		color = 3;
		//renderText();
		closeMenus();
	}
	if (state == GLUT_DOWN && y > 120 && y < 150) {
		color = 4;
		closeMenus();
	}
	if (state == GLUT_DOWN && y > 150 && y < 180) {
		color = 5;
		//renderText();
		closeMenus();
	}
	if (state == GLUT_DOWN && y > 180 && y < 210) {
		color = 6;
		//renderText();
		closeMenus();
	}
}

//--  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  ----
void colorMousePassiveFunction(int x, int y) {  // shades color-subMenu via mouseHover (after click on menu-bar)
	if (y < 30 && y > 0) {
		drawSubMenuSelection(0, 2);
	}
	if (y > 30 && y < 60) {
		drawSubMenuSelection(30, 2);
	}
	if (y > 60 && y < 90) {
		drawSubMenuSelection(60, 2);
	}
	if (y > 90 && y < 120) {
		drawSubMenuSelection(90, 2);
	}
	if (y > 120 && y < 150) {
		drawSubMenuSelection(120, 2);
	}
	if (y > 150 && y < 180) {
		drawSubMenuSelection(150, 2);
	}
	if (y > 180 && y < 210) {
		drawSubMenuSelection(180, 2);
	}
}

//--  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  ----
void fontMouseClickFunction(int button, int state, int x, int y) { // changes text font via mouse-click
	if (state == GLUT_DOWN && y < 30) {
		//font = GLUT_BITMAP_8_BY_13;
		fontInt = 0;
		fontWidth = 8;
		closeMenus();
	}
	if (state == GLUT_DOWN && y > 30 && y < 60) {
		//font = GLUT_BITMAP_9_BY_15;
		fontInt = 1;
		fontWidth = 9;
		closeMenus();
	}
	if (state == GLUT_DOWN && y > 60 && y < 90) {
		//font = GLUT_BITMAP_HELVETICA_10;
		fontInt = 2;
		fontWidth = 10;
		closeMenus();
	}
	if (state == GLUT_DOWN && y > 90 && y < 120) {
		//font = GLUT_BITMAP_HELVETICA_18;
		fontInt = 3;
		fontWidth = 10;
		closeMenus();
	}
	if (state == GLUT_DOWN && y > 120 && y < 150) {
		//font = GLUT_BITMAP_TIMES_ROMAN_10;
		fontInt = 4;
		fontWidth = 10;
		closeMenus();
	}
	if (state == GLUT_DOWN && y > 150 && y < 180) {
		//font = GLUT_BITMAP_TIMES_ROMAN_24;
		fontInt = 5;
		fontWidth = 14;
		closeMenus();
	}
}

//--  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  ----
void fontMousePassiveFunction(int x, int y) {  // shades font-subMenu via mouseHover (after click on menu-bar)
	if (y < 30 && y > 0) {
		drawSubMenuSelection(0, 3);
	}
	if (y > 30 && y < 60) {
		drawSubMenuSelection(40, 3);
	}
	if (y > 60 && y < 90) {
		drawSubMenuSelection(80, 3);
	}
	if (y > 90 && y < 120) {
		drawSubMenuSelection(120, 3);
	}
	if (y > 120 && y < 140) {
		drawSubMenuSelection(160, 3);
	}
	if (y > 140 && y < 170) {
		drawSubMenuSelection(200, 3);
	}
}

//--  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  ----
void drawColorSquare(int x, int y, int color) { // updates the little square in menu-bar to show current color
	switch (color) {
	case 0:
		glColor3ub(0, 0, 0);
		break;
	case 1:
		glColor3ub(255, 0, 0);
		break;
	case 2:
		glColor3ub(0, 255, 0);
		break;
	case 3:
		glColor3ub(0, 0, 255);
		break;
	case 4:
		glColor3ub(255, 255, 0);
		break;
	case 5:
		glColor3ub(0, 255, 255);
		break;
	case 6:
		glColor3ub(255, 0, 255);
		break;
	case 7:
		textColor(-1);
		break;
	default:
		glColor3ub(0, 0, 0);
		break;
	}
	if (color == -1) {
		glBegin(GL_LINE_LOOP);
		glVertex2f(x - 23, y + 17);
		glVertex2f(x - 2, y + 17);
		glVertex2f(x - 2, y - 3);
		glVertex2f(x - 23, y - 3);
		glEnd();
	}
	else {
		glBegin(GL_POLYGON);
		glVertex2f(x - 12, y + 10);
		glVertex2f(x - 2, y + 10);
		glVertex2f(x - 2, y);
		glVertex2f(x - 12, y);
		glEnd();
	}
}

//--  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  ----
void closeMenus() { // hides the menu-bar items
	if (menuFile[0] != -1 && menuFile[1] == 1) {
		glutSetWindow(menuFile[0]);
		glutHideWindow();
		menuFile[1] = 0;
	}
	if (menuColor[0] != -1 && menuColor[1] == 1) {
		glutSetWindow(menuColor[0]);
		glutHideWindow();
		menuColor[1] = 0;
	}
	if (menuFont[0] != -1 && menuFont[1] == 1) {
		glutSetWindow(menuFont[0]);
		glutHideWindow();
		menuFont[1] = 0;
	}
	menuState = 0;
	glutSetWindow(mainWindow); // sets up mainWindow as current window
}

//Menu Bar Sub Item Setup-------------------------------------------------------------------------------------
void menuInit(int i) {  // opens menu sub-menus
	glClearColor(.77, .77, .77, 0);
	switch (i) {
	case 1:  // file menu
		gluOrtho2D(-36, 36, -75, 75);
		break;
	case 2:  // color menu
		gluOrtho2D(-50, 50, -125, 125);
		break;
	case 3:  // font menu
		gluOrtho2D(-40, 50, -125, 125);
		break;
	default:
		break;
	}
}

//--  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  ----
void drawFileCallback() {  // attaches menu items to "File"
	glClear(GL_COLOR_BUFFER_BIT);
	drawMenuItem(-20, 50, "Clear", 0);
	drawMenuItem(-20, 15, "Save", 0);
	drawMenuItem(-20, -20, "Help", 0);
	drawMenuItem(-20, -55, "Exit", 0);
	glutMouseFunc(fileMouseClickFunction);
	glutPassiveMotionFunc(fileMousePassiveFunction);
	glutKeyboardFunc(getInput);
}

//--  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  ----
void drawColorCallback() {  // attaches menu items to "Color"
	glClear(GL_COLOR_BUFFER_BIT);
	drawMenuItem(-20, 100, "Black", 0);
	drawColorSquare(-20, 100, 0);

	drawMenuItem(-20, 70, "Red", 0);
	drawColorSquare(-20, 70, 1);

	drawMenuItem(-20, 40, "Green", 0);
	drawColorSquare(-20, 40, 2);

	drawMenuItem(-20, 10, "Blue", 0);
	drawColorSquare(-20, 10, 3);

	drawMenuItem(-20, -20, "Yellow", 0);
	drawColorSquare(-20, -20, 4);

	drawMenuItem(-20, -50, "Aqua", 0);
	drawColorSquare(-20, -50, 5);

	drawMenuItem(-20, -80, "Purple", 0);
	drawColorSquare(-20, -80, 6);
	glutMouseFunc(colorMouseClickFunction);
	glutPassiveMotionFunc(colorMousePassiveFunction);
	glutKeyboardFunc(getInput);

}

//--  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  ----
void drawFontCallback() {  // attaches menu items to "Font"
	glClear(GL_COLOR_BUFFER_BIT);
	drawMenuItem(-35, 100, "8 BY 13", 1);
	drawMenuItem(-35, 60, "9 BY 15", 2);
	drawMenuItem(-35, 20, "HELVETICA 10", 3);
	drawMenuItem(-35, -20, "HELVETICA 18", 4);
	drawMenuItem(-35, -60, "TIMES ROMAN 10", 5);
	drawMenuItem(-35, -100, "TIMES ROMAN 24", 6);
	glutMouseFunc(fontMouseClickFunction);
	glutPassiveMotionFunc(fontMousePassiveFunction);
	glutKeyboardFunc(getInput);
}

//Mouse Functions---------------------------------------------------------------------------------------------
void mouseClickFunction(int button, int state, int x, int y) {
	if (y < 30) { // if mouse is on menu bar...
        // if "File" is selected, open File menu
		if (x < 75 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			if (menuFile[0] == -1) {
				menuFile[0] = glutCreateSubWindow(mainWindow, 0, 29, 75, 150);
				glutDisplayFunc(drawFileCallback);
				menuInit(1);
				menuFile[1] = 1;
			}
			else {
				if (menuFile[1] == 0) {
					glutSetWindow(menuFile[0]);
					glutShowWindow();
					menuFile[1] = 1;
				}
				else
				{
					closeMenus();
					glutSetWindow(mainWindow);
				}
			}
		} // if "Color" is selected, open Color menu
		if (x > 75 && x < 175 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			if (menuColor[0] == -1) {
				menuColor[0] = glutCreateSubWindow(mainWindow, 75, 29, 100, 250);
				glutDisplayFunc(drawColorCallback);
				menuInit(2);
				menuColor[1] = 1;
			}
			else {
				if (menuColor[1] == 0) {
					glutSetWindow(menuColor[0]);
					glutShowWindow();
					menuColor[1] = 1;
				}
				else
				{
					closeMenus();
					glutSetWindow(mainWindow);
				}
			}
		} // if "Font" is selected, open Font menu
		if (x > 175 && x < 275 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			if (menuFont[0] == -1) {
				menuFont[0] = glutCreateSubWindow(mainWindow, 175, 29, 225, 200);
				glutDisplayFunc(drawFontCallback);
				menuInit(3);
				menuFont[1] = 1;
			}
			else {
				if (menuFont[1] == 0) {
					glutSetWindow(menuFont[0]);
					glutShowWindow();
					menuFont[1] = 1;
				}
				else
				{
					closeMenus();
					glutSetWindow(mainWindow);
				}
			}
		}
	}
	else { // otherwise update text start position for X and Y
		if (state == GLUT_DOWN) {
			posX = x - (glutGet(GLUT_SCREEN_WIDTH) / 2) + 5;
			posY = (glutGet(GLUT_SCREEN_HEIGHT) / 2) - y - 15;
		}
	} // if menus are open, and user clicks away from menus, close the menus
	if ((menuFile[1] != 0 || menuColor[1] != 0 || menuFont[1] != 0) && glutGetWindow() == mainWindow && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		closeMenus();
		glutSetWindow(mainWindow);
	}
	glClear(GL_COLOR_BUFFER_BIT);
	renderText();
	drawMenuBar();
	glFlush();
}

//--  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  ----
void mousePassiveFunction(int x, int y) { // location of mouseHover over menu bar determines which menu is open
	if (y < 30) {
		glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
		if (x < 75) {
			menuState = 1;
			drawMenuBar();
		}
		if (x > 75 && x < 175) {
			menuState = 2;
			drawMenuBar();
		}
		if (x > 175 && x < 275) {
			menuState = 4;
			drawMenuBar();
		}
	}
	else {
		glutSetWindow(mainWindow);
		menuState = 0;
		glutSetCursor(GLUT_CURSOR_TEXT);
	}
}

//Mouse Menu Items--------------------------------------------------------------------------------------------
void MenuCallback(int id) { // menu options
	switch (id) {
	case(1):
		openShaded(); // opens helpWindow
		break;
	case(2):
		exit(0);      // exits program
		break;
	default:
		break;
	}
}

//--  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  ----
void colorMenuCallback(int id) { // color switch for color menu
	switch (id) {
	case(0):
		color = 0;
		break;
	case(1):
		color = 1;
		break;
	case(2):
		color = 2;
		break;
	case(3):
		color = 3;
		break;
	case(4):
		color = 4;
		break;
	case(5):
		color = 5;
		break;
	case(6):
		color = 6;
		break;
	default:
		color = 0;
		break;
	}
	glClear(GL_COLOR_BUFFER_BIT);
	renderText();
	drawMenuBar();
	glFlush();
}

//--  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  ----
void fontMenuCallback(int id) { // font switch for font menu
	switch (id) {
	case(1):
		font = GLUT_BITMAP_8_BY_13;
		fontInt = 0;
		break;
	case(2):
		font = GLUT_BITMAP_9_BY_15;
		fontInt = 1;
		break;
	case(3):
		font = GLUT_BITMAP_HELVETICA_10;
		fontInt = 2;
		break;
	case(4):
		font = GLUT_BITMAP_HELVETICA_18;
		fontInt = 3;
		break;
	case(5):
		font = GLUT_BITMAP_TIMES_ROMAN_10;
		fontInt = 4;
		break;
	case(6):
		font = GLUT_BITMAP_TIMES_ROMAN_24;
		fontInt = 5;
		break;
	default:
		break;
	}
	glClear(GL_COLOR_BUFFER_BIT);
	renderText();
	drawMenuBar();
	glFlush();
}

//Text Input and Display--------------------------------------------------------------------------------------
void textColor(int tempColor) { // color switch for textVector
	if (tempColor == -1) {
		tempColor = color;
	}
	switch (tempColor) {
	case 1:
		glColor3f(1, 0, 0);
		break;
	case 2:
		glColor3f(0, 1, 0);
		break;
	case 3:
		glColor3f(0, 0, 1);
		break;
	case 4:
		glColor3f(1, 1, 0);
		break;
	case 5:
		glColor3f(0, 1, 1);
		break;
	case 6:
		glColor3f(1, 0, 1);
		break;
	default:
		glColor3f(0, 0, 0);
		break;
	}
}

//--  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  ----
void textFont(int tempFont) { // font switch for textVector
	if (tempFont == -1) {
		tempFont = fontInt;
	}
	switch (tempFont) {
	case(0):
		font = GLUT_BITMAP_8_BY_13;
		break;
	case(1):
		font = GLUT_BITMAP_9_BY_15;
		break;
	case(2):
		font = GLUT_BITMAP_HELVETICA_10;
		break;
	case(3):
		font = GLUT_BITMAP_HELVETICA_18;
		break;
	case(4):
		font = GLUT_BITMAP_TIMES_ROMAN_10;
		break;
	case(5):
		font = GLUT_BITMAP_TIMES_ROMAN_24;
		break;
	default:
		break;
	}
}
//--  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  ----
void renderText() { // renders text :D
	glClear(GL_COLOR_BUFFER_BIT);
	drawMenuBar();
	glutSetWindow(mainWindow);

	int xStart = posX;
	int yStart = posY;
	glRasterPos2i(xStart, yStart);
	for (int i = 0; i < text.size(); i += 2) {
        // set up array to get current raster position
		int lastCharPosArray[4];
		glGetIntegerv(GL_CURRENT_RASTER_POSITION, lastCharPosArray);
        // set color for current text rendering
		textColor((int)text.at(i + 1)[1] - 48);
		std::cout << text.at(i + 1)[1] << std::endl;
		glRasterPos2i(lastCharPosArray[0] - glutGet(GLUT_SCREEN_WIDTH) / 2, yStart);
        // for loop to print out text
		for (int j = 0; j < text.at(i).size(); j++) {
			int lastCharPosX = (glutGet(GLUT_SCREEN_WIDTH)) - fontWidth - 15;
			int lastCharPosArray[4];
			glGetIntegerv(GL_CURRENT_RASTER_POSITION, lastCharPosArray);
            // if current raster position has reached the end of the row...
			if (lastCharPosArray[0] >= lastCharPosX) {
				yStart -= 20; // start text rendering on next row...
				xStart = -(glutGet(GLUT_SCREEN_WIDTH) / 2) + 15; // and first column
				glRasterPos2i(xStart, yStart); // update new starting position
			} // if 'enter' is pressed, start new line
			if (text.at(i)[j] == '\n') {
				yStart -= 20;
				xStart = -(glutGet(GLUT_SCREEN_WIDTH) / 2) + 15;
				glRasterPos2i(xStart, yStart);
			}
			else { // otherwise, render text
				textFont((int)text.at(i + 1)[0] - 48);
				glutBitmapCharacter(font, text.at(i)[j]);
			}
		}
	}
	glFlush();
}

//--  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  ----
void getInput(unsigned char key, int cursorX, int cursorY) { // gets user keyboard input
	glutSetWindow(mainWindow);
    // note:  textVector = {"string", ##} --> ## represent font and color
	if (key == 27) exit(0);  // if 'esc' is pressed, exit program
	if (key == 8 && text.at(text.size() - 2).size() >= 0) {  // if 'backspace' is pressed, and textVector is not empty...
		std::string tempString;
        // delete "string" and font-color from vector if backspace has reached the beginning of current string
		if (text.at(text.size() - 2).size() < 1 && text.size() > 2) {
			text.pop_back();
			text.pop_back();
		} // if string still has letters to delete, backspace (aka delete this letter of string)
		for (int j = 0; j < text.at(text.size() - 2).size() - 1 && text.at(text.size() - 2).size() > 1; j++) {
			tempString += text.at(text.size() - 2)[j];
		}
		text.at(text.size() - 2) = tempString;
	}
	else { // if keyboard input is anything but backspace and escape...
        // if color or font is different from previous letter/string, create new object in vector w/ current "string", font-color
		if (color != (int)(text.at(text.size() - 1)[1]) - 48 || fontInt != (int)(text.at(text.size() - 1)[0]) - 48) {
			std::cout << text.at(text.size() - 1)[1] << std::endl;
			std::string tempString = "";
			tempString += key;
			text.push_back(tempString);
			text.push_back(std::to_string(fontInt) + std::to_string(color));
		}
		else { // if 'enter' is pressed, add "\n" to vector
			if (key == 13) text.at(text.size() - 2) += "\n";
			else {
				if (key != 8)
                    // if the color and font are the same as previous string, keep adding to current object in vector
					text.at(text.size() - 2) += key;
			}
		}
	}
	renderText();
}

//--  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  ----
void saveFile() { // saves file to 'typed.txt'
	std::ofstream myfile("c:/temp/typed.txt");
	if (myfile.is_open())
	{   // for each string in textVector (skips over font-color values)
		for (int i = 0; i < text.size(); i += 2) {
            // print to file
			myfile << text.at(i);
		}
		myfile.close();
	}
	else std::cout << "Unable to open file";
}

//Initalization-----------------------------------------------------------------------------------------------
void myInit()
{
	glClearColor(1, 1, 1, 0);	// specify a background clor: white 
	gluOrtho2D(-1 * glutGet(GLUT_SCREEN_WIDTH) / 2, glutGet(GLUT_SCREEN_WIDTH) / 2, -1 * glutGet(GLUT_SCREEN_HEIGHT) / 2, glutGet(GLUT_SCREEN_HEIGHT) / 2);

}

//--  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  ----
void myDisplayCallback()
{
	glClear(GL_COLOR_BUFFER_BIT);	// draw the background

	drawMenuBar();
	renderText();
	menuState = 0;
	glutSetWindow(mainWindow);

	glFlush(); // flush out the buffer contents
}

//--  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  ----
int main(int argc, char ** argv)
{
	glutInitWindowSize(glutGet(GLUT_SCREEN_WIDTH), glutGet(GLUT_SCREEN_HEIGHT));				// specify a window size
	glutInitWindowPosition(0, 0);	// specify a window position
	mainWindow = glutCreateWindow("Mord Text Editor");	// create a titled window

	myInit();	// setting up

	int colorMenu = glutCreateMenu(colorMenuCallback);
	glutAddMenuEntry("Black", 0);
	glutAddMenuEntry("Red", 1);
	glutAddMenuEntry("Green", 2);
	glutAddMenuEntry("Blue", 3);
	glutAddMenuEntry("Yellow", 4);
	glutAddMenuEntry("Aqua", 5);
	glutAddMenuEntry("Purple", 6);

	int fontMenu = glutCreateMenu(fontMenuCallback);
	glutAddMenuEntry("8 BY 13", 1);
	glutAddMenuEntry("9 BY 15", 2);
	glutAddMenuEntry("HELVETICA 10", 3);
	glutAddMenuEntry("HELVETICA 18", 4);
	glutAddMenuEntry("TIMES ROMAN 10", 5);
	glutAddMenuEntry("TIMES ROMAN 24", 6);

	int Menu = glutCreateMenu(MenuCallback); //MenuId
	glutAddSubMenu("Font", fontMenu);
	glutAddSubMenu("Color", colorMenu);
	glutAddMenuEntry("Help", 1);
	glutAddMenuEntry("Exit", 2);


	glutAttachMenu(GLUT_RIGHT_BUTTON);


	glutKeyboardFunc(getInput);
	glutMouseFunc(mouseClickFunction);
	glutPassiveMotionFunc(mousePassiveFunction);
	glutDisplayFunc(myDisplayCallback);		// register a callback

	openShaded();                           // opens helpWindow

	glutMainLoop();							// get into an infinite loop

	return 0;
}