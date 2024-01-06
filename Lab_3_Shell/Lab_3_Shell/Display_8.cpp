WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#include "Display_8.h"
#include "glut.h"
#include <stdlib.h>
#include <math.h>
#include "dcPt.h"

// For accessing OpenCV ...
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

using namespace cv;
using namespace std;
///////////////////////

extern void winReshapeFcn(GLint newWidth, GLint newHeight);
extern GLsizei winWidth, winHeight; 
extern void drawWorldFrame(void);

Display_8::Display_8(void)
{
}


Display_8::~Display_8(void)
{
}


void Display_8::Draw(int *viewing)
{
	//// Section 1 ///////////////////////////////////////////////
	//// Do not change/remove any function in Section 1. ////////
	glClear(GL_COLOR_BUFFER_BIT);  //  Clear display window.
	glClear(GL_DEPTH_BUFFER_BIT);	// Clear the depth (z) buffer
	glDisable(GL_DEPTH_TEST);		// Disable the depth test
	glDisable(GL_LIGHTING);			// Disable lighting
	glutSetWindowTitle("Display 8");
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//////////////////////////////////////////////////////////////

//// Section 2 ///////////////////////////////////////////////
	//// You may select a display method: *viewing = 2, 3 or 4. //
	//// Do not change/remove anything else in Section 2. ////////
	*viewing = 2; // Decide the display method: 2 = 2D display; 3 = 3D orthogonal parallel projection; 4 = 3D perspective projection;
	winReshapeFcn(winWidth, winHeight); // Show the display/projection now.	
	//////////////////////////////////////////////////////////////

	//// Section 3 ///////////////////////////////////////////////
	/*******************************/
	// Place your drawing code below. 
	// Note:
	// For 3D display: call the following function after the projection parameters are set.
	// drawWorldFrame(); // Draw the World coordinate frame based on the current projection setting
	// For 2D display: call this function below.
	/*******************************/
	drawWorldFrame(); // Draw the World coordinate frame based on the current projection setting





	//// Section 4 ///////////////////////////////////////////////
	//// Do not delete the following function ////////////////////
	glFlush();  // Show the result now
	//////////////////////////////////////////////////////////////
}
