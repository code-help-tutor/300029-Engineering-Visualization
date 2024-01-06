WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#include "Display_3.h"
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

Display_3::Display_3(void)
{
}


Display_3::~Display_3(void)
{
}


void Display_3::Draw(int *viewing)
{
	//// Section 1 ///////////////////////////////////////////////
	//// Do not change/remove any function in Section 1. ////////
	glClear (GL_COLOR_BUFFER_BIT);  //  Clear display window.
	glClear (GL_DEPTH_BUFFER_BIT);	// Clear the depth (z) buffer
	glDisable (GL_DEPTH_TEST);		// Disable the depth test
	glDisable(GL_LIGHTING);			// Disable lighting
	glutSetWindowTitle("Display 3");
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//////////////////////////////////////////////////////////////

	//// Section 2 ///////////////////////////////////////////////
	//// You may select a display method: *viewing = 2, 3 or 4. //
	//// Do not change/remove anything else in Section 2. ////////
	*viewing = 3; // Decide the display method: 2 = 2D display; 3 = 3D orthogonal parallel projection; 4 = 3D perspective projection;
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
	GLfloat x0 = 400.0, y0 = 310.0, z0 = 200.0; // eye position
	GLfloat xref = 200.0, yref = 50.0, zref = 0.0; //look-at point
	GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0; // view-up vector
	gluLookAt(x0, y0, z0, xref, yref, zref, Vx, Vy, Vz); 
	
	// Draw the World coordinate frame based on the current projection setting
	drawWorldFrame();

// An example of drawing the partial surface 
// after a rotation of the polyline by 10 degrees.
	{
		// A polyline with 6 vertices.
		// Store all vertices of the polyline before and after rotation by 10 degrees.
		float vertices[2][6][3];	// 2 x 6 vertices are used to model the partial surface of the solid.
									// 2 = 2 sets of vertices before and after rotation of 10 degrees.
									// 6 = 6 vertices for the polyline.
									// 3 = 3 coordinates (x, y, z) for each vertice.
		
		// Original vertices of the polyline before rotation
		vertices[0][0][0] = 200; vertices[0][0][1] = 50; vertices[0][0][2] = 0;
		vertices[0][1][0] = 50; vertices[0][1][1] = 50; vertices[0][1][2] = 0;
		vertices[0][2][0] = 160; vertices[0][2][1] = 150; vertices[0][2][2] = 0;
		vertices[0][3][0] = 150; vertices[0][3][1] = 200; vertices[0][3][2] = 0;
		vertices[0][4][0] = 60; vertices[0][4][1] = 300; vertices[0][4][2] = 0;
		vertices[0][5][0] = 200; vertices[0][5][1] = 300; vertices[0][5][2] = 0;

		// Find the vertices of the polyline after rotation of 10 degrees
		double theta = 3.14159265 / 180 * 10; // Convert 10 degrees to radians
		double r11 = cos(theta), r12 = 0.0, r13 = sin(theta), tx = 0.0;
		double r21 = 0.0, r22 = 1.0, r23 = 0.0, ty = 0.0;
		double r31 = -sin(theta), r32 = 0.0, r33 = cos(theta), tz = 0.0;
		double xx1, yy1, zz1; // Transformed point

		// Apply the translation-rotation-translation sequence to get the transformed points.
		for (int count = 0; count < 6; count++)
		{
			double xx = vertices[0][count][0], yy = vertices[0][count][1], zz = vertices[0][count][2]; // Original point
			transform3D(1.0, 0.0, 0.0, -vertices[0][0][0],
						0.0, 1.0, 0.0, -vertices[0][0][1],
						0.0, 0.0, 1.0, -vertices[0][0][2],
						xx, yy, zz, &xx1, &yy1, &zz1);  // Translate the polyline so that (vertices[0][0][0], vertices[0][0][1], vertices[0][0][2]) moves to the origin.
			transform3D(r11, r12, r13, tx,
						r21, r22, r23, ty,
						r31, r32, r33, tz,
						xx1, yy1, zz1, &xx, &yy, &zz);  // Rotate the translated polyline about the y axis.
			transform3D(1.0, 0.0, 0.0, vertices[0][0][0],
						0.0, 1.0, 0.0, vertices[0][0][1],
						0.0, 0.0, 1.0, vertices[0][0][2],
						xx, yy, zz, &xx1, &yy1, &zz1);  // Translate the polyline so that (vertices[0][0][0], vertices[0][0][1], vertices[0][0][2]) moves back to its original place.
			vertices[1][count][0] = xx1;  vertices[1][count][1] = yy1;  vertices[1][count][2] = zz1;
		}

		// draw polygons just created
		for (int count = 0; count < 5; count++)
		{
			int nextCount = count + 1;
			GLfloat colour = (count + 1) * 10 / 19.0; // Different colours for different lines
			colour = colour - (int)colour;
			glColor3f(colour, 1 - colour, colour * (1 - colour) * 4.0);
			glBegin(GL_LINE_LOOP);
				glVertex3i(vertices[0][count][0], vertices[0][count][1], vertices[0][count][2]);
				glVertex3i(vertices[1][count][0], vertices[1][count][1], vertices[1][count][2]);
				glVertex3i(vertices[1][nextCount][0], vertices[1][nextCount][1], vertices[1][nextCount][2]);
				glVertex3i(vertices[0][nextCount][0], vertices[0][nextCount][1], vertices[0][nextCount][2]);
			glEnd();
		}
	}

	//// Section 4 ///////////////////////////////////////////////
	//// Do not delete the following function ////////////////////
	glFlush ( );  // Show the result now
	//////////////////////////////////////////////////////////////
}


/*	A generic function for 3D transformation. Original point = (x, y, z); Transformed point = (x1, y1, z1).
For example, for translation with amounts tx = 10, ty = 20 and tz = 30, the following code may be used.

double r11 = 1.0, r12 = 0.0, r13 = 0.0, tx = 10.0;
double r21 = 0.0, r22 = 1.0, r23 = 0.0, ty = 20.0;
double r31 = 0.0, r32 = 0.0, r33 = 1.0, tz = 30.0;
double x = 30.0, y = 40.0, z = 50.0; // Original point = (30.0, 40.0, 50.0) (as an example).
double x1, y1, z1; // The transformed point will be stored in (x1, y1, z1).
transform3D(r11, r12, r13, tx,
			r21, r22, r23, ty,
			r31, r32, r33, tz,
			x, y, z, &x1, &y1, &z1);  // Calculate the transformed point and store it in (x1, y1, z1).
*/

void Display_3::transform3D(double r11, double r12, double r13, double tx, 
							double r21, double r22, double r23, double ty, 
							double r31, double r32, double r33, double tz, 
							double x, double y, double z, double * x1, double * y1, double * z1)
{
	/*
	[ x1 ]   [ r11  r12  r13  tx ] [ x ]
	| y1 | = | r21  r22  r23  ty | | y |
	| z1 |   | r31  r32  r33  tz | | z |
	[ 1  ]   [ 0     0    0    1 ] [ 1 ]
	*/
	double xx = r11 * x + r12 * y + r13 * z + tx;
	double yy = r21 * x + r22 * y + r23 * z + ty;
	double zz = r31 * x + r32 * y + r33 * z + tz;
	*x1 = xx;
	*y1 = yy;
	*z1 = zz;
}
