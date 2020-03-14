#include <GL/glut.h>
#include "camera.cpp"
#include <iostream>

GLfloat angleCube = 1.0f;
GLfloat speedUnit = 0.2f;
GLfloat clipX = 1.0f, clipY = 1.0f;
GLfloat nearZ = 2.0f;
GLfloat farZ = 100.0f;
GLfloat fovy = 45.0f;

GLfloat degreeX = 0.0f, degreeY = 0.0f, degreeZ = 0.0f;

GLfloat gridRange = 10.0f;

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
	else if (key == 'x'){ degreeX += angleCube; }
	else if (key == 'X'){ degreeX -= angleCube; }
	else if (key == 'y'){ degreeY += angleCube; }
	else if (key == 'Y'){ degreeY -= angleCube; }
	else if (key == 'z'){ degreeZ -= angleCube; }
	else if (key == 'Z'){ degreeZ += angleCube; }
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
		i += 1;
	}
	glRotatef(degreeX, 1.0f, 0.0f, 0.0f);
	glRotatef(degreeY, 0.0f, 1.0f, 0.0f);
	glRotatef(degreeZ, 0.0f, 0.0f, 1.0f);
	// Face
	glColor3f(0.5f, 0.5f, 0.3f);
	glBegin(GL_QUADS);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();

	// Back Side
	glColor3f(0.6f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();

	// Top
	glColor3f(0.0f, 0.0f, 0.6f);
	glBegin(GL_QUADS);
		glVertex3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, 1.0f, 1.0f);
	glEnd();

	// Left Side
	glColor3f(0.5f, 0.8f, 0.2f);
	glBegin(GL_QUADS);
		glVertex3f(-1.0f, 1.0f, 1.0f);
		glVertex3f(-1.0f, 1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();

	// Bottom
	glColor3f(0.5f, 0.5f, 0.8f);
	glBegin(GL_QUADS);
		glVertex3f(-1.0f, -1.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();

	// Right Side
	glColor3f(0.1f, 0.7f, 0.4f);
	glBegin(GL_QUADS);
		glVertex3f(1.0f, -1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, -1.0f);
		glVertex3f(1.0f, 1.0f, 1.0f);
	glEnd();

	
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