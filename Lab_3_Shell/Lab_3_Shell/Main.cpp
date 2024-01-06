WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
// Define the entry point for the console application


#include <stdio.h>
#include <tchar.h>
#include <stdlib.h>

#include "glut.h"
#include "Display_1.h"
#include "Display_2.h"
#include "Display_3.h"
#include "Display_4.h"
#include "Display_5.h"
#include "Display_6.h"
#include "Display_7.h"
#include "Display_8.h"
#include "Display_9.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>


GLsizei winWidth = 1200, winHeight = 1200;   // Initial display-window size.
GLsizei xmin = 0, xmax = 1200, ymin = 0, ymax = 1200; // Set display limits.

// viewing = 2: 2D viewing
// viewing = 3: 3D orthogonal parallel projection
// viewing = 4: 3D perspective projection
int viewing = 4;

Display_1 display_1;
Display_2 display_2;
Display_3 display_3;
Display_4 display_4;
Display_5 display_5;
Display_6 display_6;
Display_7 display_7;
Display_8 display_8;
Display_9 display_9;

GLenum errorCheck()
{
	GLenum code;
	const GLubyte *string;
	code = glGetError();
	if (code != GL_NO_ERROR)
	{
		string = gluErrorString(code);
		fprintf(stderr, "OpenGL error: %s\n", string);
	}
	return code;
}

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);   // Set display-window color to white.

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//   gluOrtho2D (xmin, xmax, ymin, ymax);  
}

void displayFcn(void)
{
	glClear(GL_COLOR_BUFFER_BIT);          //  Clear display window.
	glClear(GL_DEPTH_BUFFER_BIT);			// Clear the depth (z) buffer
	glColor3f(1.0, 0.0, 0.0);              //  Set fill color to red.
}

// Window-reshape function for 3D display
void winReshapeFcn(GLint newWidth, GLint newHeight)
{
	/*  Reset viewport and projection parameters  */
	glViewport(0, 0, newWidth, newHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	switch (viewing)
	{
	case 2: // 2D display
		//       gluOrtho2D (0.0, GLdouble (newWidth), 0.0, GLdouble (newHeight));
		//		 glOrtho(0, GLdouble (newWidth), 0, GLdouble (newHeight), -50000.0, 50000.0);
		glOrtho(-GLdouble(newWidth / 2.0), GLdouble(newWidth / 2.0), -GLdouble(newHeight / 2.0), GLdouble(newHeight / 2.0), -50000.0, 50000.0);
		break;
	case 3: // 3D orthogonal parallel projection
		glOrtho(-GLdouble(newWidth / 2.0), GLdouble(newWidth / 2.0), -GLdouble(newHeight / 2.0), GLdouble(newHeight / 2.0), -50000.0, 50000.0);
		break;
	case 4: // 3D perspective projection
		//		 glFrustum(-GLdouble (newWidth/400.0), GLdouble (newWidth/400.0), -GLdouble (newHeight/400.0), GLdouble (newHeight/400.0), 1.0, 5000.0);
		glFrustum(-GLdouble(newWidth / 2.0), GLdouble(newWidth / 2.0), -GLdouble(newHeight / 2.0), GLdouble(newHeight / 2.0), 400.0, 5000.0);
		break;
	default:
		break;
	}

	/*  Reset display-window size parameters.  */
	winWidth = newWidth;
	winHeight = newHeight;
}

/*  Use keys 1 - 9 to select a display.  */
void DisplaySelection(GLubyte key, GLint xMouse, GLint yMouse)
{
	switch (key)
	{
	case '1':
		display_1.Draw(&viewing);
		break;
	case '2':
		display_2.Draw(&viewing);
		break;
	case '3':
		display_3.Draw(&viewing);
		break;
	case '4':
		display_4.Draw(&viewing);
		break;
	case '5':
		display_5.Draw(&viewing);
		break;
	case '6':
		display_6.Draw(&viewing);
		break;
	case '7':
		display_7.Draw(&viewing);
		break;
	case '8':
		display_8.Draw(&viewing);
		break;
	case '9':
		display_9.Draw(&viewing);
		break;
	default:
		break;
	}
}

void drawWorldFrame(void)
{
	//  Set drawing color (R, G, B) to black.
	glColor3ub(0, 0, 0);
	// Draw coordinate frame
	glBegin(GL_LINES);
	glVertex3i(0, 0, 0); // x axis
	glVertex3i(100, 0, 0);
	glVertex3i(110, 10, 0); // 'x' symbol
	glVertex3i(120, -10, 0);
	glVertex3i(120, 10, 0);
	glVertex3i(110, -10, 0);

	glVertex3i(0, 0, 0); // y axis
	glVertex3i(0, 100, 0);
	glVertex3i(0, 110, 0); // 'y' symbol
	glVertex3i(0, 124, 0);
	glVertex3i(0, 124, 0);
	glVertex3i(-5, 130, 0);
	glVertex3i(0, 124, 0);
	glVertex3i(5, 130, 0);

	if (viewing != 2)
	{
		glVertex3i(0, 0, 0); // z axis
		glVertex3i(0, 0, 100);
		glVertex3i(0, 10, 130); // 'z' symbol
		glVertex3i(0, 10, 110);
		glVertex3i(0, 10, 110);
		glVertex3i(0, -10, 130);
		glVertex3i(0, -10, 130);
		glVertex3i(0, -10, 110);
	}
	glEnd();
}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Display Results");

	init();
	glutDisplayFunc(displayFcn);
	glutKeyboardFunc(DisplaySelection);
	glutReshapeFunc(winReshapeFcn);
	//   glutKeyboardFunc (DisplaySelection);

	errorCheck(); // Check error

	glutMainLoop();
}
