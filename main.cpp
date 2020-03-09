#include <GL/glut.h>
#include "camera.cpp"
#include <iostream>

GLfloat angleCube = 0.0f;
GLfloat speedUnit = 0.2f;
GLfloat clipX = 1.0f, clipY = 1.0f;
GLfloat nearZ = 2.0f;
GLfloat farZ = 100.0f;
GLfloat fovy = 45.0f;

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
	std::cout << "depth : " << camera.eye.z << std::endl;
	if (key == 27){ exit(0);}
	else if (key == 82 || key == 114){
		camera.reset();
	}
	else if (key == 65 || key == 97){
		camera.moveLeft();
	}
	else if (key == 68 || key == 100){
		camera.moveRight();
	}
	else if (key == 87 || key == 119){
		camera.moveUp();
	}
	else if (key == 83 || key == 115){
		camera.moveDown();
	}
	else if (key == 73 || key == 105){
		// Zoom In
		camera.zoomIn();
	}
	else if (key == 79 || key == 111){
		// Zoom Out
		camera.zoomOut();
	}
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
void createPlane(){
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
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
	//glRotatef(angleCube, 0.0f, 0.0f, 1.0f);
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
	angleCube += 2.0f;
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