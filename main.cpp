#include <GL/glut.h>
#include "camera_struct.cpp"
#include <iostream>
#include <math.h>

GLfloat angleCube = 1.0f, speedUnit = 0.2f, delta = 0.2f;
GLfloat clipX = 1.0f, clipY = 1.0f;
GLfloat nearZ = 2.0f, farZ = 100.0f;
GLfloat fovy = 45.0f;
GLfloat degreeX = 0.0f, degreeY = 0.0f, degreeZ = 0.0f;

GLfloat gridRange = 10.0f;

// CONST FOR PLANE

GLfloat WING_WIDTH = 4.0f;
GLfloat WING_LENGTH = 1.5f;
GLfloat WING_THICKNESS = 0.1f;
GLfloat WING_HEIGHT = 1.0f;
GLfloat WING_AXIS_X = 0.0f, WING_AXIS_Y = 0.0f, WING_AXIS_Z = 0.0f;

GLfloat HR_WIDTH_STBLZ = 1.5f;
GLfloat HR_LENGTH_STBLZ = 1.0f;
GLfloat HR_GAP = 0.0f;
GLfloat HR_AXIS_X = 0.0f;
GLfloat HR_AXIS_Y = 0.0f;
GLfloat HR_AXIS_Z = -2.0f;

GLfloat VR_FRONT_EDGE = 0.2f;
GLfloat VR_REAR_EDGE = 1.3f;
GLfloat VR_AXIS_X = 0.0f;
GLfloat VR_AXIS_Y = 0.0f;
GLfloat VR_AXIS_Z = -2.0f;
GLfloat VR_HEIGHT = 1.2f;
GLfloat VR_LENGTH = 1.5f;


GLfloat PROPELLER_AXIS_RADIUS = 0.2f;
GLfloat PROPELLER_AXIS_X = 0.0f, PROPELLER_AXIS_Y = 0.0f, PROPELLER_AXIS_Z = 1.0f;
GLfloat PROPELLER_BLADE_RADIUS = 1.0f;
GLfloat deltaAngle, tempX, tempY, angle;
GLuint FAN = 8;

Camera camera = Camera();

void initGL(){
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void keyboardHandler(unsigned char key, int x, int y){
	if (key == 27){ exit(0);}
	else if (key == 'r'){ camera.reset(); } // Reset Camera
	else if (key == 'R'){ degreeX = 0.0f; degreeY = 0.0f; degreeZ = 0.0f; } // Reset Object
	else if (key == 'a' || key == 'A'){ camera.rotateY(-2.0f); }
	else if (key == 'd' || key == 'D'){ camera.rotateY(2.0f); }
	else if (key == 'q' || key == 'Q'){ camera.roll(); }
	else if (key == 'i' || key == 'I'){ camera.zoomIn(); } // ZOOM IN
	else if (key == 'o' || key == 'O'){ camera.zoomOut(); }
	else if (key == 'x'){ degreeX += 1.0f; }
	else if (key == 'X'){ degreeX -= 1.0f; }
	else if (key == 'y'){ degreeY += 1.0f; }
	else if (key == 'Y'){ degreeY -= 1.0f; }
	else if (key == 'z'){ degreeZ -= 1.0f; }
	else if (key == 'Z'){ degreeZ += 1.0f; }
	else if (key == 'm'){ delta += 0.2f; }
	else if (key == 'M'){ delta -= 0.2f; }
}

void reshape(GLsizei width, GLsizei height){
	if (height == 0){
		height = 1;
	}
	GLfloat aspectRatio = (GLfloat) width/ (GLfloat) height;

	glViewport(0, 0, width, height);
}

void idle(){
	glutPostRedisplay();
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(
		-clipX, clipX,
		-clipY, clipY,
		nearZ, farZ
	);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		camera.eye.x, camera.eye.y, camera.eye.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
	);

	GLfloat i = -gridRange;
	glColor3f(1.0f, 1.0f, 1.0f);
	while (i <= gridRange){
		glBegin(GL_LINES);
			glVertex3f(i, 0.0f, gridRange);
			glVertex3f(i, 0.0f, -gridRange);
		glEnd();
		glBegin(GL_LINES);
			glVertex3f(gridRange, 0.0f, i);
			glVertex3f(-gridRange, 0.0f, i);
		glEnd();
		i += 2;
	}
	glRotatef(degreeX, 1.0f, 0.0f, 0.0f);
	glRotatef(degreeY, 0.0f, 1.0f, 0.0f);
	glRotatef(degreeZ, 0.0f, 0.0f, 1.0f);
// Body
{
   glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 1.0f);     // Green
      glVertex3f(0.0f,0.0f,0.0f); //0
      glColor3f(1.0f, 1.0f, 0.0f);
      glVertex3f( 1.0f, 0.0f,  -1.0f); //1
      glVertex3f( 0.5f, 1.0f,  -1.0f); // 2
      glVertex3f( -0.5f, 1.0f,  -1.0f); //3
      glVertex3f( -1.0f, 0.0f, -1.0f); // 4
      glVertex3f(-0.5f, -1.0f, -1.0f); // 5
      glVertex3f(0.5f, -1.0f,  -1.0f); //6
      glVertex3f(0.75f, -0.5f,  -1.0f);
      glVertex3f(1.0f, 0.0f,  -1.0f);
   glEnd();

 glBegin(GL_QUAD_STRIP);
   glColor3f(1.0f, 0.0f, 1.0f);
  glVertex3f( 0.3f, 0.5f,  -1.0f); //0
    glVertex3f( 1.0f, 0.0f,  -1.0f); //1
     glVertex3f( 0.3f, 1.5f,  -1.0f); //2
      glVertex3f( 0.5f, 1.0f,  -1.0f); // 3
     glVertex3f( -0.3f, 1.5f,  -1.0f); //4
     glVertex3f( -0.5f, 1.0f,  -1.0f); //5
      glVertex3f( -0.3f, 0.5f, -1.0f); //6
     glVertex3f( -1.0f, 0.0f, -1.0f); // 7
      glVertex3f(-0.3f, -0.5f, -1.0f); //8
    glVertex3f(-0.5f, -1.0f, -1.0f); // 9
     glVertex3f(0.3f, -0.5,  -1.0f); //10
      glVertex3f(0.5f, -1.0f,  -1.0f); //11
      glVertex3f(0.55f, -0.5f,  -1.0f); //12
   glEnd();
}

	// WING
	{
		glBegin(GL_POLYGON);
			glVertex3f(WING_WIDTH, WING_AXIS_Y + WING_HEIGHT, 0.0f);
			glVertex3f(WING_WIDTH, (WING_AXIS_Y + WING_HEIGHT), -(WING_LENGTH  * 0.6));
			glVertex3f(WING_WIDTH * 0.8, (WING_AXIS_Y + WING_HEIGHT), -WING_LENGTH);
			glVertex3f(-WING_WIDTH * 0.8, (WING_AXIS_Y + WING_HEIGHT), -WING_LENGTH);
			glVertex3f(-WING_WIDTH, (WING_AXIS_Y + WING_HEIGHT), -(WING_LENGTH  * 0.6));
			glVertex3f(-WING_WIDTH, (WING_AXIS_Y + WING_HEIGHT), 0.0f);
		glEnd();

		glBegin(GL_POLYGON);
			glVertex3f(WING_WIDTH, (WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), 0.0f);
			glVertex3f(WING_WIDTH, (WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), -(WING_LENGTH  * 0.6));
			glVertex3f(WING_WIDTH * 0.8, (WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), -WING_LENGTH);
			glVertex3f(-WING_WIDTH * 0.8, (WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), -WING_LENGTH);
			glVertex3f(-WING_WIDTH, (WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), -(WING_LENGTH  * 0.6));
			glVertex3f(-WING_WIDTH, (WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), 0.0f);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f(-WING_WIDTH, (WING_AXIS_Y + WING_HEIGHT), 0.0f);
			glVertex3f(-WING_WIDTH, (WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), 0.0f);
			glVertex3f(WING_WIDTH, (WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), 0.0f);
			glVertex3f(WING_WIDTH, (WING_AXIS_Y + WING_HEIGHT), 0.0f);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f(WING_WIDTH, (WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), 0.0f);
			glVertex3f(WING_WIDTH, (WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), -(WING_LENGTH  * 0.6));
			glVertex3f(WING_WIDTH, (WING_AXIS_Y + WING_HEIGHT), -(WING_LENGTH  * 0.6));
			glVertex3f(WING_WIDTH, (WING_AXIS_Y + WING_HEIGHT), 0.0f);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f(WING_WIDTH, (WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), -(WING_LENGTH  * 0.6));
			glVertex3f(WING_WIDTH * 0.8, (WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), -WING_LENGTH);
			glVertex3f(WING_WIDTH * 0.8, (WING_AXIS_Y + WING_HEIGHT), -WING_LENGTH);
			glVertex3f(WING_WIDTH, (WING_AXIS_Y + WING_HEIGHT), -(WING_LENGTH  * 0.6));
		glEnd();
		
		glBegin(GL_QUADS);
			glVertex3f(WING_WIDTH * 0.8, (WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), -WING_LENGTH);
			glVertex3f(-WING_WIDTH * 0.8, (WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), -WING_LENGTH);
			glVertex3f(-WING_WIDTH * 0.8, (WING_AXIS_Y + WING_HEIGHT), -WING_LENGTH);
			glVertex3f(WING_WIDTH * 0.8, (WING_AXIS_Y + WING_HEIGHT), -WING_LENGTH);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f(-WING_WIDTH, (WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), -(WING_LENGTH  * 0.6));
			glVertex3f(-WING_WIDTH, (WING_AXIS_Y + WING_HEIGHT), -(WING_LENGTH  * 0.6));
			glVertex3f(-WING_WIDTH * 0.8, (WING_AXIS_Y + WING_HEIGHT), -WING_LENGTH);
			glVertex3f(-WING_WIDTH * 0.8, (WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), -WING_LENGTH);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f(-WING_WIDTH, (WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), -(WING_LENGTH  * 0.6));
			glVertex3f(-WING_WIDTH, (WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), 0.0f);
			glVertex3f(-WING_WIDTH, (WING_AXIS_Y + WING_HEIGHT), 0.0f);
			glVertex3f(-WING_WIDTH, (WING_AXIS_Y + WING_HEIGHT), -(WING_LENGTH  * 0.6));
		glEnd();

		// LOWER WING

		glBegin(GL_POLYGON);
			glVertex3f(WING_WIDTH, -(WING_AXIS_Y + WING_HEIGHT), 0.0f);
			glVertex3f(WING_WIDTH, -(WING_AXIS_Y + WING_HEIGHT), -(WING_LENGTH  * 0.6));
			glVertex3f(WING_WIDTH * 0.8, -(WING_AXIS_Y + WING_HEIGHT), -WING_LENGTH);
			glVertex3f(-WING_WIDTH * 0.8, -(WING_AXIS_Y + WING_HEIGHT), -WING_LENGTH);
			glVertex3f(-WING_WIDTH, -(WING_AXIS_Y + WING_HEIGHT), -(WING_LENGTH  * 0.6));
			glVertex3f(-WING_WIDTH, -(WING_AXIS_Y + WING_HEIGHT), 0.0f);
		glEnd();

		glBegin(GL_POLYGON);
			glVertex3f(WING_WIDTH, -(WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), 0.0f);
			glVertex3f(WING_WIDTH, -(WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), -(WING_LENGTH  * 0.6));
			glVertex3f(WING_WIDTH * 0.8, -(WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), -WING_LENGTH);
			glVertex3f(-WING_WIDTH * 0.8, -(WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), -WING_LENGTH);
			glVertex3f(-WING_WIDTH, -(WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), -(WING_LENGTH  * 0.6));
			glVertex3f(-WING_WIDTH, -(WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), 0.0f);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f(-WING_WIDTH, -(WING_AXIS_Y + WING_HEIGHT), 0.0f);
			glVertex3f(-WING_WIDTH,-(WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), 0.0f);
			glVertex3f(WING_WIDTH, -(WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), 0.0f);
			glVertex3f(WING_WIDTH, -(WING_AXIS_Y + WING_HEIGHT), 0.0f);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f(WING_WIDTH, -(WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), 0.0f);
			glVertex3f(WING_WIDTH, -(WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), -(WING_LENGTH  * 0.6));
			glVertex3f(WING_WIDTH, -(WING_AXIS_Y + WING_HEIGHT), -(WING_LENGTH  * 0.6));
			glVertex3f(WING_WIDTH, -(WING_AXIS_Y + WING_HEIGHT), 0.0f);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f(WING_WIDTH, -(WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), -(WING_LENGTH  * 0.6));
			glVertex3f(WING_WIDTH * 0.8, -(WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), -WING_LENGTH);
			glVertex3f(WING_WIDTH * 0.8, -(WING_AXIS_Y + WING_HEIGHT), -WING_LENGTH);
			glVertex3f(WING_WIDTH, -(WING_AXIS_Y + WING_HEIGHT), -(WING_LENGTH  * 0.6));
		glEnd();
		
		glBegin(GL_QUADS);
			glVertex3f(WING_WIDTH * 0.8, -(WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), -WING_LENGTH);
			glVertex3f(-WING_WIDTH * 0.8, -(WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), -WING_LENGTH);
			glVertex3f(-WING_WIDTH * 0.8, -(WING_AXIS_Y + WING_HEIGHT), -WING_LENGTH);
			glVertex3f(WING_WIDTH * 0.8, -(WING_AXIS_Y + WING_HEIGHT), -WING_LENGTH);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f(-WING_WIDTH, -(WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), -(WING_LENGTH  * 0.6));
			glVertex3f(-WING_WIDTH, -(WING_AXIS_Y + WING_HEIGHT), -(WING_LENGTH  * 0.6));
			glVertex3f(-WING_WIDTH * 0.8, -(WING_AXIS_Y + WING_HEIGHT), -WING_LENGTH);
			glVertex3f(-WING_WIDTH * 0.8, -(WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), -WING_LENGTH);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f(-WING_WIDTH, -(WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), -(WING_LENGTH  * 0.6));
			glVertex3f(-WING_WIDTH, -(WING_AXIS_Y + WING_HEIGHT + WING_THICKNESS), 0.0f);
			glVertex3f(-WING_WIDTH, -(WING_AXIS_Y + WING_HEIGHT), 0.0f);
			glVertex3f(-WING_WIDTH, -(WING_AXIS_Y + WING_HEIGHT), -(WING_LENGTH  * 0.6));
		glEnd();

		// KANAN

		glBegin(GL_QUADS);
			glVertex3f(WING_WIDTH/2, (WING_AXIS_Y + WING_HEIGHT), -0.15f);
			glVertex3f(WING_WIDTH/2 + 0.1, (WING_AXIS_Y + WING_HEIGHT), -0.15f);
			glVertex3f(WING_WIDTH/2 + 0.1, -(WING_AXIS_Y + WING_HEIGHT), -0.15f);
			glVertex3f(WING_WIDTH/2, -(WING_AXIS_Y + WING_HEIGHT), -0.15f);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f(WING_WIDTH/2 + 0.1, (WING_AXIS_Y + WING_HEIGHT), -0.15f);
			glVertex3f(WING_WIDTH/2 + 0.1, (WING_AXIS_Y + WING_HEIGHT), -0.25f);
			glVertex3f(WING_WIDTH/2 + 0.1, -(WING_AXIS_Y + WING_HEIGHT), -0.25f);
			glVertex3f(WING_WIDTH/2 + 0.1, -(WING_AXIS_Y + WING_HEIGHT), -0.15f);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f(WING_WIDTH/2 + 0.1, (WING_AXIS_Y + WING_HEIGHT), -0.25f);
			glVertex3f(WING_WIDTH/2, (WING_AXIS_Y + WING_HEIGHT), -0.25f);
			glVertex3f(WING_WIDTH/2, -(WING_AXIS_Y + WING_HEIGHT), -0.25f);
			glVertex3f(WING_WIDTH/2 + 0.1, -(WING_AXIS_Y + WING_HEIGHT), -0.25f);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f(WING_WIDTH/2, (WING_AXIS_Y + WING_HEIGHT), -0.25f);
			glVertex3f(WING_WIDTH/2, (WING_AXIS_Y + WING_HEIGHT), -0.15f);
			glVertex3f(WING_WIDTH/2, -(WING_AXIS_Y + WING_HEIGHT), -0.15f);
			glVertex3f(WING_WIDTH/2, -(WING_AXIS_Y + WING_HEIGHT), -0.25f);
		glEnd();

		// BELAKANG
		glBegin(GL_QUADS);
			glVertex3f(WING_WIDTH/2, (WING_AXIS_Y + WING_HEIGHT), -1.15f);
			glVertex3f(WING_WIDTH/2 + 0.1, (WING_AXIS_Y + WING_HEIGHT), -1.15f);
			glVertex3f(WING_WIDTH/2 + 0.1, -(WING_AXIS_Y + WING_HEIGHT), -1.15f);
			glVertex3f(WING_WIDTH/2, -(WING_AXIS_Y + WING_HEIGHT), -1.15f);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f(WING_WIDTH/2 + 0.1, (WING_AXIS_Y + WING_HEIGHT), -1.15f);
			glVertex3f(WING_WIDTH/2 + 0.1, (WING_AXIS_Y + WING_HEIGHT), -1.25f);
			glVertex3f(WING_WIDTH/2 + 0.1, -(WING_AXIS_Y + WING_HEIGHT), -1.25f);
			glVertex3f(WING_WIDTH/2 + 0.1, -(WING_AXIS_Y + WING_HEIGHT), -1.15f);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f(WING_WIDTH/2 + 0.1, (WING_AXIS_Y + WING_HEIGHT), -1.25f);
			glVertex3f(WING_WIDTH/2, (WING_AXIS_Y + WING_HEIGHT), -1.25f);
			glVertex3f(WING_WIDTH/2, -(WING_AXIS_Y + WING_HEIGHT), -1.25f);
			glVertex3f(WING_WIDTH/2 + 0.1, -(WING_AXIS_Y + WING_HEIGHT), -1.25f);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f(WING_WIDTH/2, (WING_AXIS_Y + WING_HEIGHT), -1.25f);
			glVertex3f(WING_WIDTH/2, (WING_AXIS_Y + WING_HEIGHT), -1.15f);
			glVertex3f(WING_WIDTH/2, -(WING_AXIS_Y + WING_HEIGHT), -1.15f);
			glVertex3f(WING_WIDTH/2, -(WING_AXIS_Y + WING_HEIGHT), -1.25f);
		glEnd();
		
		glBegin(GL_LINE_STRIP);
			glVertex3f(WING_WIDTH/2 + 0.05, (WING_AXIS_Y + WING_HEIGHT), -0.15f);
			glVertex3f(WING_WIDTH/2 + 0.05, -(WING_AXIS_Y + WING_HEIGHT), -1.25f);
			glVertex3f(WING_WIDTH/2 + 0.05, -(WING_AXIS_Y + WING_HEIGHT), -0.15f);
			glVertex3f(WING_WIDTH/2 + 0.05, (WING_AXIS_Y + WING_HEIGHT), -1.25f);
		glEnd();

		// KIRI 
		glColor3f(1.0f, 1.0f, 0.0f);
		glBegin(GL_QUADS);
			glVertex3f(-WING_WIDTH/2 - 0.1, (WING_AXIS_Y + WING_HEIGHT), -0.15f);
			glVertex3f(-WING_WIDTH/2, (WING_AXIS_Y + WING_HEIGHT), -0.15f);
			glVertex3f(-WING_WIDTH/2, -(WING_AXIS_Y + WING_HEIGHT), -0.15f);
			glVertex3f(-WING_WIDTH/2 - 0.1, -(WING_AXIS_Y + WING_HEIGHT), -0.15f);
		glEnd();

		glColor3f(1.0f, 0.0f, 1.0f);
		glBegin(GL_QUADS);
			glVertex3f(-WING_WIDTH/2 - 0.1, (WING_AXIS_Y + WING_HEIGHT), -0.15f);
			glVertex3f(-WING_WIDTH/2 - 0.1, -(WING_AXIS_Y + WING_HEIGHT), -0.15f);
			glVertex3f(-WING_WIDTH/2 - 0.1, -(WING_AXIS_Y + WING_HEIGHT), -0.25f);
			glVertex3f(-WING_WIDTH/2 - 0.1, (WING_AXIS_Y + WING_HEIGHT), -0.25f);
		glEnd();

		glColor3f(0.0f, 1.0f, 1.0f);
		glBegin(GL_QUADS);
			glVertex3f(-WING_WIDTH/2, -(WING_AXIS_Y + WING_HEIGHT), -0.25f);
			glVertex3f(-WING_WIDTH/2, (WING_AXIS_Y + WING_HEIGHT), -0.25f);
			glVertex3f(-WING_WIDTH/2 - 0.1, (WING_AXIS_Y + WING_HEIGHT), -0.25f);
			glVertex3f(-WING_WIDTH/2 - 0.1, -(WING_AXIS_Y + WING_HEIGHT), -0.25f);
		glEnd();

		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_QUADS);
			glVertex3f(-WING_WIDTH/2, (WING_AXIS_Y + WING_HEIGHT), -0.15f);
			glVertex3f(-WING_WIDTH/2, (WING_AXIS_Y + WING_HEIGHT), -0.25f);
			glVertex3f(-WING_WIDTH/2, -(WING_AXIS_Y + WING_HEIGHT), -0.25f);
			glVertex3f(-WING_WIDTH/2, -(WING_AXIS_Y + WING_HEIGHT), -0.15f);
		glEnd();

		// BELAKANG
		glColor3f(1.0f, 1.0f, 0.0f);
		glBegin(GL_QUADS);
			glVertex3f(-WING_WIDTH/2 - 0.1, (WING_AXIS_Y + WING_HEIGHT), -1.15f);
			glVertex3f(-WING_WIDTH/2, (WING_AXIS_Y + WING_HEIGHT), -1.15f);
			glVertex3f(-WING_WIDTH/2, -(WING_AXIS_Y + WING_HEIGHT), -1.15f);
			glVertex3f(-WING_WIDTH/2 - 0.1, -(WING_AXIS_Y + WING_HEIGHT), -1.15f);
		glEnd();

		glColor3f(1.0f, 0.0f, 1.0f);
		glBegin(GL_QUADS);
			glVertex3f(-WING_WIDTH/2 - 0.1, (WING_AXIS_Y + WING_HEIGHT), -1.15f);
			glVertex3f(-WING_WIDTH/2 - 0.1, -(WING_AXIS_Y + WING_HEIGHT), -1.15f);
			glVertex3f(-WING_WIDTH/2 - 0.1, -(WING_AXIS_Y + WING_HEIGHT), -1.25f);
			glVertex3f(-WING_WIDTH/2 - 0.1, (WING_AXIS_Y + WING_HEIGHT), -1.25f);
		glEnd();

		glColor3f(0.0f, 1.0f, 1.0f);
		glBegin(GL_QUADS);
			glVertex3f(-WING_WIDTH/2, -(WING_AXIS_Y + WING_HEIGHT), -1.25f);
			glVertex3f(-WING_WIDTH/2, (WING_AXIS_Y + WING_HEIGHT), -1.25f);
			glVertex3f(-WING_WIDTH/2 - 0.1, (WING_AXIS_Y + WING_HEIGHT), -1.25f);
			glVertex3f(-WING_WIDTH/2 - 0.1, -(WING_AXIS_Y + WING_HEIGHT), -1.25f);
		glEnd();

		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_QUADS);
			glVertex3f(-WING_WIDTH/2, (WING_AXIS_Y + WING_HEIGHT), -1.15f);
			glVertex3f(-WING_WIDTH/2, (WING_AXIS_Y + WING_HEIGHT), -1.25f);
			glVertex3f(-WING_WIDTH/2, -(WING_AXIS_Y + WING_HEIGHT), -1.25f);
			glVertex3f(-WING_WIDTH/2, -(WING_AXIS_Y + WING_HEIGHT), -1.15f);
		glEnd();

		glBegin(GL_LINE_STRIP);
			glVertex3f(-WING_WIDTH/2 - 0.05, (WING_AXIS_Y + WING_HEIGHT), -0.15f);
			glVertex3f(-WING_WIDTH/2 - 0.05, -(WING_AXIS_Y + WING_HEIGHT), -1.25f);
			glVertex3f(-WING_WIDTH/2 - 0.05, -(WING_AXIS_Y + WING_HEIGHT), -0.15f);
			glVertex3f(-WING_WIDTH/2 - 0.05, (WING_AXIS_Y + WING_HEIGHT), -1.25f);
		glEnd();
	}

	// Stabilizer Horizontal
	{
		glColor3f(1.0f, 0.2f, 0.1f);
		glBegin(GL_POLYGON);
			glVertex3f((HR_AXIS_X) + HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z);
			glVertex3f((HR_AXIS_X) + HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 0.25f);
			glVertex3f((HR_AXIS_X) + HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 1.1f);
			glVertex3f((HR_AXIS_X + 0.6f) + HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 1.5f);
			glVertex3f((HR_AXIS_X + 1.2f) + HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 1.5f);
			glVertex3f((HR_AXIS_X + 1.5f) + HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 1.2f);
			glVertex3f((HR_AXIS_X + 1.5f) + HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 0.6f);
			glVertex3f((HR_AXIS_X + 1.1f) + HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 0.25f);
		glEnd();

		glBegin(GL_POLYGON);
			glVertex3f((HR_AXIS_X) + HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z);
			glVertex3f((HR_AXIS_X) + HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 0.25f);
			glVertex3f((HR_AXIS_X) + HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 1.1f);
			glVertex3f((HR_AXIS_X + 0.6f) + HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 1.5f);
			glVertex3f((HR_AXIS_X + 1.2f) + HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 1.5f);
			glVertex3f((HR_AXIS_X + 1.5f) + HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 1.2f);
			glVertex3f((HR_AXIS_X + 1.5f) + HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 0.6f);
			glVertex3f((HR_AXIS_X + 1.1f) + HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 0.25f);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f((HR_AXIS_X) + HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z);
			glVertex3f((HR_AXIS_X + 1.1f) + HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 0.25f);
			glVertex3f((HR_AXIS_X + 1.1f) + HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 0.25f);
			glVertex3f((HR_AXIS_X) + HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f((HR_AXIS_X + 1.1f) + HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 0.25f);
			glVertex3f((HR_AXIS_X + 1.5f) + HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 0.6f);
			glVertex3f((HR_AXIS_X + 1.5f) + HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 0.6f);
			glVertex3f((HR_AXIS_X + 1.1f) + HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 0.25f);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f((HR_AXIS_X + 1.5f) + HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 0.6f);
			glVertex3f((HR_AXIS_X + 1.5f) + HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 1.2f);
			glVertex3f((HR_AXIS_X + 1.5f) + HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 1.2f);
			glVertex3f((HR_AXIS_X + 1.5f) + HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 0.6f);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f((HR_AXIS_X + 1.5f) + HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 1.2f);
			glVertex3f((HR_AXIS_X + 1.2f) + HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 1.5f);
			glVertex3f((HR_AXIS_X + 1.2f) + HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 1.5f);
			glVertex3f((HR_AXIS_X + 1.5f) + HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 1.2f);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f((HR_AXIS_X + 1.2f) + HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 1.5f);
			glVertex3f((HR_AXIS_X + 0.6f) + HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 1.5f);
			glVertex3f((HR_AXIS_X + 0.6f) + HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 1.5f);
			glVertex3f((HR_AXIS_X + 1.2f) + HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 1.5f);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f((HR_AXIS_X + 0.6f) + HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 1.5f);
			glVertex3f((HR_AXIS_X) + HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 1.1f);
			glVertex3f((HR_AXIS_X) + HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 1.1f);
			glVertex3f((HR_AXIS_X + 0.6f) + HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 1.5f);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f((HR_AXIS_X) + HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z);
			glVertex3f((HR_AXIS_X) + HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z);
			glVertex3f((HR_AXIS_X) + HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 1.1f);
			glVertex3f((HR_AXIS_X) + HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 1.1f);
		glEnd();

		// KIRI
		glColor3f(0.0f, 0.4f, 1.0f);
		glBegin(GL_POLYGON);
			glVertex3f((HR_AXIS_X - 1.1f) - HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 0.25f);
			glVertex3f((HR_AXIS_X - 1.5f) - HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 0.6f);
			glVertex3f((HR_AXIS_X - 1.5f) - HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 1.2f);
			glVertex3f((HR_AXIS_X - 1.2f) - HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 1.5f);
			glVertex3f((HR_AXIS_X - 0.6f) - HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 1.5f);
			glVertex3f((HR_AXIS_X) - HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 1.1f);
			glVertex3f((HR_AXIS_X) - HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 0.25f);
			glVertex3f((HR_AXIS_X) - HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z);
		glEnd();

		glBegin(GL_POLYGON);
			glVertex3f((HR_AXIS_X - 1.1f) - HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 0.25f);
			glVertex3f((HR_AXIS_X - 1.5f) - HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 0.6f);
			glVertex3f((HR_AXIS_X - 1.5f) - HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 1.2f);
			glVertex3f((HR_AXIS_X - 1.2f) - HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 1.5f);
			glVertex3f((HR_AXIS_X - 0.6f) - HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 1.5f);
			glVertex3f((HR_AXIS_X) - HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 1.1f);
			glVertex3f((HR_AXIS_X) - HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 0.25f);
			glVertex3f((HR_AXIS_X) - HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f((HR_AXIS_X) - HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z);
			glVertex3f((HR_AXIS_X - 1.1f) - HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 0.25f);
			glVertex3f((HR_AXIS_X - 1.1f) - HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 0.25f);
			glVertex3f((HR_AXIS_X) - HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f((HR_AXIS_X - 1.1f) - HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 0.25f);
			glVertex3f((HR_AXIS_X - 1.5f) - HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 0.6f);
			glVertex3f((HR_AXIS_X - 1.5f) - HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 0.6f);
			glVertex3f((HR_AXIS_X - 1.1f) - HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 0.25f);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f((HR_AXIS_X - 1.5f) - HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 0.6f);
			glVertex3f((HR_AXIS_X - 1.5f) - HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 1.2f);
			glVertex3f((HR_AXIS_X - 1.5f) - HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 1.2f);
			glVertex3f((HR_AXIS_X - 1.5f) - HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 0.6f);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f((HR_AXIS_X - 1.5f) - HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 1.2f);
			glVertex3f((HR_AXIS_X - 1.2f) - HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 1.5f);
			glVertex3f((HR_AXIS_X - 1.2f) - HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 1.5f);
			glVertex3f((HR_AXIS_X - 1.5f) - HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 1.2f);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f((HR_AXIS_X - 1.2f) - HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 1.5f);
			glVertex3f((HR_AXIS_X - 0.6f) - HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 1.5f);
			glVertex3f((HR_AXIS_X - 0.6f) - HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 1.5f);
			glVertex3f((HR_AXIS_X - 1.2f) - HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 1.5f);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f((HR_AXIS_X - 0.6f) - HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 1.5f);
			glVertex3f((HR_AXIS_X) - HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 1.1f);
			glVertex3f((HR_AXIS_X) - HR_GAP/2 , HR_AXIS_Y + 0.05f, HR_AXIS_Z - 1.1f);
			glVertex3f((HR_AXIS_X - 0.6f) - HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 1.5f);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f((HR_AXIS_X) - HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z - 1.1f);
			glVertex3f((HR_AXIS_X) - HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z - 1.1f);
			glVertex3f((HR_AXIS_X) - HR_GAP/2, HR_AXIS_Y - 0.05f, HR_AXIS_Z);
			glVertex3f((HR_AXIS_X) - HR_GAP/2, HR_AXIS_Y + 0.05f, HR_AXIS_Z);
		glEnd();
	}

	// Stabilizer Vertical
	{
		glBegin(GL_POLYGON);
			glVertex3f(VR_AXIS_X + 0.05f, VR_AXIS_Y, VR_AXIS_Z);
			glVertex3f(VR_AXIS_X + 0.05f, VR_AXIS_Y + 0.4f, VR_AXIS_Z + VR_FRONT_EDGE);
			glVertex3f(VR_AXIS_X + 0.05f, VR_AXIS_Y + 0.7f, VR_AXIS_Z + VR_FRONT_EDGE);
			glVertex3f(VR_AXIS_X + 0.05f, VR_AXIS_Y + VR_HEIGHT - 0.05f, VR_AXIS_Z - 0.2f);
			glVertex3f(VR_AXIS_X + 0.05f, VR_AXIS_Y + VR_HEIGHT + 0.2f, VR_AXIS_Z - VR_LENGTH);
			glVertex3f(VR_AXIS_X + 0.05f, VR_AXIS_Y + VR_HEIGHT - 0.05f, VR_AXIS_Z - VR_LENGTH - 0.35f);
			glVertex3f(VR_AXIS_X + 0.05f, VR_AXIS_Y + 0.55f, VR_AXIS_Z - VR_LENGTH - 0.4f);
			glVertex3f(VR_AXIS_X + 0.05f, VR_AXIS_Y + 0.3f, VR_AXIS_Z - VR_LENGTH - 0.2f);
			glVertex3f(VR_AXIS_X + 0.05f, VR_AXIS_Y, VR_AXIS_Z - 1.2f);
		glEnd();

		glBegin(GL_POLYGON);
			glVertex3f(VR_AXIS_X - 0.05f, VR_AXIS_Y, VR_AXIS_Z - 1.2f);
			glVertex3f(VR_AXIS_X - 0.05f, VR_AXIS_Y + 0.3f, VR_AXIS_Z - VR_LENGTH - 0.2f);
			glVertex3f(VR_AXIS_X - 0.05f, VR_AXIS_Y + 0.55f, VR_AXIS_Z - VR_LENGTH - 0.4f);
			glVertex3f(VR_AXIS_X - 0.05f, VR_AXIS_Y + VR_HEIGHT - 0.05f, VR_AXIS_Z - VR_LENGTH - 0.35f);
			glVertex3f(VR_AXIS_X - 0.05f, VR_AXIS_Y + VR_HEIGHT + 0.2f, VR_AXIS_Z - VR_LENGTH);
			glVertex3f(VR_AXIS_X - 0.05f, VR_AXIS_Y + VR_HEIGHT - 0.05f, VR_AXIS_Z - 0.2f);
			glVertex3f(VR_AXIS_X - 0.05f, VR_AXIS_Y + 0.7f, VR_AXIS_Z + VR_FRONT_EDGE);
			glVertex3f(VR_AXIS_X - 0.05f, VR_AXIS_Y + 0.4f, VR_AXIS_Z + VR_FRONT_EDGE);
			glVertex3f(VR_AXIS_X - 0.05f, VR_AXIS_Y, VR_AXIS_Z);
		glEnd();

		glColor3f(1.0f, 0.9f, 0.2f);
		glBegin(GL_QUADS);
			glVertex3f(VR_AXIS_X + 0.05f, VR_AXIS_Y, VR_AXIS_Z);
			glVertex3f(VR_AXIS_X - 0.05f, VR_AXIS_Y, VR_AXIS_Z);
			glVertex3f(VR_AXIS_X - 0.05f, VR_AXIS_Y + 0.4f, VR_AXIS_Z + VR_FRONT_EDGE);
			glVertex3f(VR_AXIS_X + 0.05f, VR_AXIS_Y + 0.4f, VR_AXIS_Z + VR_FRONT_EDGE);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f(VR_AXIS_X + 0.05f, VR_AXIS_Y + 0.4f, VR_AXIS_Z + VR_FRONT_EDGE);
			glVertex3f(VR_AXIS_X - 0.05f, VR_AXIS_Y + 0.4f, VR_AXIS_Z + VR_FRONT_EDGE);
			glVertex3f(VR_AXIS_X - 0.05f, VR_AXIS_Y + 0.7f, VR_AXIS_Z + VR_FRONT_EDGE);
			glVertex3f(VR_AXIS_X + 0.05f, VR_AXIS_Y + 0.7f, VR_AXIS_Z + VR_FRONT_EDGE);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f(VR_AXIS_X + 0.05f, VR_AXIS_Y + 0.7f, VR_AXIS_Z + VR_FRONT_EDGE);
			glVertex3f(VR_AXIS_X - 0.05f, VR_AXIS_Y + 0.7f, VR_AXIS_Z + VR_FRONT_EDGE);
			glVertex3f(VR_AXIS_X - 0.05f, VR_AXIS_Y + VR_HEIGHT - 0.05f, VR_AXIS_Z - 0.2f);
			glVertex3f(VR_AXIS_X + 0.05f, VR_AXIS_Y + VR_HEIGHT - 0.05f, VR_AXIS_Z - 0.2f);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f(VR_AXIS_X + 0.05f, VR_AXIS_Y + VR_HEIGHT - 0.05f, VR_AXIS_Z - 0.2f);
			glVertex3f(VR_AXIS_X - 0.05f, VR_AXIS_Y + VR_HEIGHT - 0.05f, VR_AXIS_Z - 0.2f);
			glVertex3f(VR_AXIS_X - 0.05f, VR_AXIS_Y + VR_HEIGHT + 0.2f, VR_AXIS_Z - VR_LENGTH);
			glVertex3f(VR_AXIS_X + 0.05f, VR_AXIS_Y + VR_HEIGHT + 0.2f, VR_AXIS_Z - VR_LENGTH);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f(VR_AXIS_X + 0.05f, VR_AXIS_Y + VR_HEIGHT + 0.2f, VR_AXIS_Z - VR_LENGTH);
			glVertex3f(VR_AXIS_X - 0.05f, VR_AXIS_Y + VR_HEIGHT + 0.2f, VR_AXIS_Z - VR_LENGTH);
			glVertex3f(VR_AXIS_X - 0.05f, VR_AXIS_Y + VR_HEIGHT - 0.05f, VR_AXIS_Z - VR_LENGTH - 0.35f);
			glVertex3f(VR_AXIS_X + 0.05f, VR_AXIS_Y + VR_HEIGHT - 0.05f, VR_AXIS_Z - VR_LENGTH - 0.35f);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f(VR_AXIS_X + 0.05f, VR_AXIS_Y + VR_HEIGHT - 0.05f, VR_AXIS_Z - VR_LENGTH - 0.35f);
			glVertex3f(VR_AXIS_X - 0.05f, VR_AXIS_Y + VR_HEIGHT - 0.05f, VR_AXIS_Z - VR_LENGTH - 0.35f);
			glVertex3f(VR_AXIS_X - 0.05f, VR_AXIS_Y + 0.55f, VR_AXIS_Z - VR_LENGTH - 0.4f);
			glVertex3f(VR_AXIS_X + 0.05f, VR_AXIS_Y + 0.55f, VR_AXIS_Z - VR_LENGTH - 0.4f);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f(VR_AXIS_X + 0.05f, VR_AXIS_Y + 0.55f, VR_AXIS_Z - VR_LENGTH - 0.4f);
			glVertex3f(VR_AXIS_X - 0.05f, VR_AXIS_Y + 0.55f, VR_AXIS_Z - VR_LENGTH - 0.4f);
			glVertex3f(VR_AXIS_X - 0.05f, VR_AXIS_Y + 0.3f, VR_AXIS_Z - VR_LENGTH - 0.2f);
			glVertex3f(VR_AXIS_X + 0.05f, VR_AXIS_Y + 0.3f, VR_AXIS_Z - VR_LENGTH - 0.2f);
		glEnd();

		glBegin(GL_QUADS);
			glVertex3f(VR_AXIS_X + 0.05f, VR_AXIS_Y + 0.3f, VR_AXIS_Z - VR_LENGTH - 0.2f);
			glVertex3f(VR_AXIS_X - 0.05f, VR_AXIS_Y + 0.3f, VR_AXIS_Z - VR_LENGTH - 0.2f);
			glVertex3f(VR_AXIS_X - 0.05f, VR_AXIS_Y, VR_AXIS_Z - 1.2f);
			glVertex3f(VR_AXIS_X + 0.05f, VR_AXIS_Y, VR_AXIS_Z - 1.2f);
		glEnd();
	}

	glColor3f(1.0f, 1.0f, 0.1f);
	// Propellers
	{
		glTranslatef(PROPELLER_AXIS_X, PROPELLER_AXIS_Y, PROPELLER_AXIS_Z);
		// Propeller Base
		{
			glBegin(GL_QUADS);
				glVertex3f(PROPELLER_AXIS_RADIUS, PROPELLER_AXIS_RADIUS, 0.4f);
				glVertex3f(-PROPELLER_AXIS_RADIUS, PROPELLER_AXIS_RADIUS, 0.4f);
				glVertex3f(-PROPELLER_AXIS_RADIUS, PROPELLER_AXIS_RADIUS,0.0f);
				glVertex3f(PROPELLER_AXIS_RADIUS, PROPELLER_AXIS_RADIUS, 0.0f);
			glEnd();

			glBegin(GL_QUADS);
				glVertex3f(PROPELLER_AXIS_RADIUS, PROPELLER_AXIS_RADIUS, 0.4f);
				glVertex3f(PROPELLER_AXIS_RADIUS, PROPELLER_AXIS_RADIUS, 0.0f);
				glVertex3f(PROPELLER_AXIS_RADIUS, -PROPELLER_AXIS_RADIUS, 0.0f);
				glVertex3f(PROPELLER_AXIS_RADIUS, -PROPELLER_AXIS_RADIUS, 0.4f);
			glEnd();

			glBegin(GL_QUADS);
				glVertex3f(PROPELLER_AXIS_RADIUS, -PROPELLER_AXIS_RADIUS, 0.4f);
				glVertex3f(PROPELLER_AXIS_RADIUS, -PROPELLER_AXIS_RADIUS, 0.0f);
				glVertex3f(-PROPELLER_AXIS_RADIUS, -PROPELLER_AXIS_RADIUS, 0.0f);
				glVertex3f(-PROPELLER_AXIS_RADIUS, -PROPELLER_AXIS_RADIUS, 0.4f);
			glEnd();

			glBegin(GL_QUADS);
				glVertex3f(-PROPELLER_AXIS_RADIUS, -PROPELLER_AXIS_RADIUS, 0.0f);
				glVertex3f(-PROPELLER_AXIS_RADIUS, PROPELLER_AXIS_RADIUS, 0.0f);
				glVertex3f(-PROPELLER_AXIS_RADIUS, PROPELLER_AXIS_RADIUS, 0.4f);
				glVertex3f(-PROPELLER_AXIS_RADIUS, -PROPELLER_AXIS_RADIUS, 0.4f);
			glEnd();
		}
		// Propeller Cap
		{
			glBegin(GL_TRIANGLE_FAN);
				glVertex3f(0.0f, 0.0f, 0.4f + 0.2f);
				glVertex3f(-PROPELLER_AXIS_RADIUS, PROPELLER_AXIS_RADIUS, 0.4f);
				glVertex3f(PROPELLER_AXIS_RADIUS, PROPELLER_AXIS_RADIUS, 0.4f);
				glVertex3f(PROPELLER_AXIS_RADIUS, -PROPELLER_AXIS_RADIUS, 0.4f);
				glVertex3f(-PROPELLER_AXIS_RADIUS, -PROPELLER_AXIS_RADIUS, 0.4f);
				glVertex3f(-PROPELLER_AXIS_RADIUS, PROPELLER_AXIS_RADIUS, 0.4f);
			glEnd();
		}
		// Propeller Fan
		{
			FAN = 12;
			angle = 0.0f;
			deltaAngle = 360.0f / FAN;
			glRotatef(angleCube, 0.0f, 0.0f, 1.0f);
			while (angle < 360.0){
				tempX = PROPELLER_BLADE_RADIUS * cos(Camera::rad(angle));
				tempY = PROPELLER_BLADE_RADIUS * sin(Camera::rad(angle));

				glBegin(GL_QUADS);
					glVertex3f(0.0f, 0.0f, 0.0f);
					glVertex3f(0.0f, 0.0f, 0.4f);
					glVertex3f(tempX, tempY, 0.4f);
					tempX = PROPELLER_BLADE_RADIUS * cos(Camera::rad(angle + 15.0f));
					tempY = PROPELLER_BLADE_RADIUS * sin(Camera::rad(angle + 15.0f));
					glVertex3f(tempX, tempY, 0.0f);
				glEnd();
				angle += deltaAngle;
			}
			angleCube = fmod(angleCube - delta, -360.0f);
		}
	}
	glutSwapBuffers();
}

int main(int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("First Time?");
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboardHandler);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	initGL();
	glutMainLoop();


	return 0;
}