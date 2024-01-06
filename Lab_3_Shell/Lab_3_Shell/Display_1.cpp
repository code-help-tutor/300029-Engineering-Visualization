WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#include "Display_1.h"
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

Display_1::Display_1(void)
{
}

Display_1::~Display_1(void)
{
}

void Display_1::Draw(int *viewing)
{
	//// Section 1 ///////////////////////////////////////////////
	//// Do not change/remove any function in Section 1. ////////
	glClear (GL_COLOR_BUFFER_BIT);  //  Clear display window.
	glClear (GL_DEPTH_BUFFER_BIT);	// Clear the depth (z) buffer
	glDisable (GL_DEPTH_TEST);		// Disable the depth test
	glDisable(GL_LIGHTING);			// Disable lighting
	glutSetWindowTitle("Display 1");
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

	GLfloat x0 = 0.0, y0 = 0.0, z0 = -600.0; // eye position
	GLfloat xref = 0.0, yref = 0.0, zref = 0.0; //look-at point
	GLfloat Vx = 0.0, Vy = 1.0, Vz = 0.0; // view-up vector
	gluLookAt(x0, y0, z0, xref, yref, zref, Vx, Vy, Vz);

	// Draw the World coordinate frame based on the current projection setting
	drawWorldFrame();
	
	// Bezier surface defined by 4 x 4 control points P(u, v)
	GLfloat ctrlPts[4][4][3] = {
		{ { 120, 80, 200 }, { 80, 170, 100 }, { 120, 230, 100 }, { 150, 280, 100 } },
		{ { 130, 120, -100 }, { 170, 130, 100 }, { 130, 270, 100 }, { 170, 280, -100 } },
		{ { 270, 80, -100 }, { 230, 170, 100 }, { 270, 230, 100 }, { 230, 320, -100 } },
		{ { 280, 120, 200 }, { 320, 130, 100 }, { 280, 270, 100 }, { 320, 280, 100 } }
	};

	// Set up Bezier surface parameters and activate the surface-generation routine.
	// The offset of P(u, v) is 12 (i.e., 4 x 3) in the u direction and 3 in the v direction.
	glMap2f (GL_MAP2_VERTEX_3, 0.0, 1.0, 12, 4, 0.0, 1.0, 3, 4, &ctrlPts[0][0][0]); 
	glEnable (GL_MAP2_VERTEX_3);

	GLint k, j;
	GLfloat u, v, uv;
	for (k = 0; k <= 10; k++)
	{
		uv = GLfloat(k) / 10.0;
		glBegin (GL_LINE_STRIP);  // Generate Bezier surface lines (polylines).
			for (j = 0; j <= 50; j++)
			{
				u = GLfloat (j) / 50.0;
				glColor3f ((1.0 - u),  (u + uv) / 2.0, (1.0 - uv)); // Changing colour for lines
				glEvalCoord2f (u, uv);
			}
		glEnd ( );
		glBegin (GL_LINE_STRIP);
			for (j = 0; j <= 50; j++)
			{
				v = GLfloat (j) / 50.0;
				glColor3f ((uv + v) / 2.0, (1.0 - uv), (1.0 - v)); // Changing colour for lines
				glEvalCoord2f (uv, v);
			}
		glEnd ( ); 
	}
	glDisable(GL_MAP2_VERTEX_3); // Disable Bezier surface drawing

	//// Section 4 ///////////////////////////////////////////////
	//// Do not delete the following function ////////////////////
	glFlush ( );  // Show the result now
	//////////////////////////////////////////////////////////////
}

