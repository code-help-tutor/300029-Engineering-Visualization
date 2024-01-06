WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#include "Display_5.h"
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

Display_5::Display_5(void)
{
}


Display_5::~Display_5(void)
{
}


void Display_5::Draw(int *viewing)
{
	//// Section 1 ///////////////////////////////////////////////
	//// Do not change/remove any function in Section 1. ////////
	glClear(GL_COLOR_BUFFER_BIT);  //  Clear display window.
	glClear(GL_DEPTH_BUFFER_BIT);	// Clear the depth (z) buffer
	glDisable(GL_DEPTH_TEST);		// Disable the depth test
	glDisable(GL_LIGHTING);			// Disable lighting
	glutSetWindowTitle("Display 5");
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//////////////////////////////////////////////////////////////

	//// Section 2 ///////////////////////////////////////////////
	//// You may select a display method: *viewing = 2, 3 or 4. //
	//// Do not change/remove anything else in Section 2. ////////
	*viewing = 3; // Decide the display method: 2 = 2D display; 3 = 3D orthogonal parrallel projection; 4 = 3D perspective projection;
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

	// Set the projection parameters for 3D display
	GLfloat x0 = 60.0, y0 = 100.0, z0 = 180.0; // eye position
	GLfloat xref = 0.0, yref = 0.0, zref = 0.0; //look-at point
	GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0; // view-up vector
	gluLookAt(x0, y0, z0, xref, yref, zref, Vx, Vy, Vz); // Set viewing/projection parameters

	//  Enable the depth (z) test to show the visible surface only
	glEnable(GL_DEPTH_TEST);

	// Draw the World coordinate frame based on the current projection setting
	drawWorldFrame();

	//  Set drawing color (R, G, B) to green.
	glColor3ub(0, 255, 0);

	// A cube
	//     5 _________ 6
	//      /:       /|
	//    1/_:______/2|
	//     |4:......|.|7
	//     | /      | /
	//    0|/_______|/3
	//
	//      y|
	//       |______ x
	//      /
	//    z/

	// Define the cube
	GLint vertices[][3] = { { 50, 50, 250 },{ 50, 250, 250 },
	{ 250, 250, 250 },{ 250, 50, 250 },{ 50, 50, 50 },
	{ 50, 250, 50 },{ 250, 250, 50 },{ 250, 50, 50 } };

	// Draw a wire-frame model of the cube
	{
		glBegin(GL_LINE_LOOP);
			glVertex3iv(vertices[0]);
			glVertex3iv(vertices[3]);
			glVertex3iv(vertices[2]);
			glVertex3iv(vertices[1]);
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex3iv(vertices[2]);
			glVertex3iv(vertices[3]);
			glVertex3iv(vertices[7]);
			glVertex3iv(vertices[6]);
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex3iv(vertices[3]);
			glVertex3iv(vertices[0]);
			glVertex3iv(vertices[4]);
			glVertex3iv(vertices[7]);
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex3iv(vertices[1]);
			glVertex3iv(vertices[2]);
			glVertex3iv(vertices[6]);
			glVertex3iv(vertices[5]);
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex3iv(vertices[4]);
			glVertex3iv(vertices[5]);
			glVertex3iv(vertices[6]);
			glVertex3iv(vertices[7]);
		glEnd();

		glBegin(GL_LINE_LOOP);
			glVertex3iv(vertices[5]);
			glVertex3iv(vertices[4]);
			glVertex3iv(vertices[0]);
			glVertex3iv(vertices[1]);
		glEnd();
	}

	// Example: Map a texture image to the right surface of the cube
	{
		////// Load an image for texture mapping //////
		long count;
		//// Part 1: Read an image from file using OpenCV ////
		Mat image1 = imread("../images/test.jpg", IMREAD_COLOR); // Read the file and convert the image to a BGR colour image
		if (!image1.data) // Check for invalid input
		{
			cout << "Could not open or find the image" << std::endl; return;
		}
		CV_Assert(image1.depth() == CV_8U);  // accept only char type matrices

		//// Part 2: Create a texture array using OpenGL and fill the array with pixel values ////
		Mat_<Vec3b> _I1 = image1;
		int textureH1 = image1.rows, textureW1 = image1.cols;
		GLubyte *texArray1 = new GLubyte[4 * textureH1 * textureW1];  // Memory allocation for the OpenGL array
		if (!texArray1) { cout << "Out of memory!"; return; }
		count = 0;
		for (int y = 0; y < textureH1; y++) // Fill the texture array with pixel values
			for (int x = 0; x < textureW1; x++)
			{
				texArray1[count] = _I1(textureH1 - 1 - y, x)[2]; // 'red' component
				texArray1[count + 1] = _I1(textureH1 - 1 - y, x)[1]; // 'green' component
				texArray1[count + 2] = _I1(textureH1 - 1 - y, x)[0]; // 'blue' component
				texArray1[count + 3] = 0; // alpha channel: opaque
				count += 4;
			}	

		////// Map the texture image to the righ surface //////
		
		// Preparation
		glPolygonMode(GL_FRONT, GL_FILL); // Set the polygon display mode to 'fill'
		glClearColor(1.0, 1.0, 1.0, 1.0); // Clear the background and set it to white

		// Set parameters for texture mapping. This must be done just before texture mapping!
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glColor3ub(255, 255, 255); //  Set drawing color (R, G, B) to white to ensure texture maps are visible.
		glEnable(GL_TEXTURE_2D); // Enable texture mapping
		
		// Texture mapping to the right surface
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureW1, textureH1, 0, GL_RGBA, GL_UNSIGNED_BYTE, texArray1); // Set parameters for surface texture mapping
		glBegin(GL_POLYGON);
			glTexCoord2f(0.0, 0.0); glVertex3iv(vertices[3]);
			glTexCoord2f(1.0, 0.0); glVertex3iv(vertices[7]);
			glTexCoord2f(1.0, 1.0); glVertex3iv(vertices[6]);
			glTexCoord2f(0.0, 1.0); glVertex3iv(vertices[2]);
		glEnd();

		delete[] texArray1;  // Delete the dynamic memory for texture array 1
		glDisable(GL_TEXTURE_2D); // Disable texture mapping
	}

	//// Section 4 ///////////////////////////////////////////////
	//// Do not delete the following function ////////////////////
	glFlush();  // Show the result now
	//////////////////////////////////////////////////////////////
}
