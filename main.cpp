#include <GL/glut.h>
#include "camera.cpp"
#include <iostream>
#include <omp.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

GLfloat angleCube = 0.0f;
GLfloat speedUnit = 0.2f;
GLfloat clipX = 20.0f, clipY = 20.0f;
GLfloat nearZ = 1.0f;
GLfloat farZ = -100.0f;

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
		camera.zoomIn();
	}
	else if (key == 79 || key == 111){
		camera.zoomOut();
	}
}

void reshape(GLsizei width, GLsizei height){
	if (height == 0){
		height = 1;
	}
	GLfloat aspectRatio = (GLfloat) width/ (GLfloat) height;

	glViewport(0, 0, width, height);

	// Setting CLIPPING AREA
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (width >= height){
		gluOrtho2D(
			-clipX * aspectRatio, clipX * aspectRatio,
			-clipY, clipY);
	}
	else{
		gluOrtho2D(
			-clipX, clipX,
			-clipY / aspectRatio, clipY / aspectRatio);
	}

	gluLookAt(
		camera.eye.x, camera.eye.y, camera.eye.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
	);
}

void idle(){
	glutPostRedisplay();
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	//glRotatef(angleCube, 0.0f, 1.0f, 0.0f);

	// Face
	glColor3f(0.5f, 0.5f, 0.3f);
	glBegin(GL_QUADS);
		glVertex3f(0.25f, 0.0f, 0.25f);
		glVertex3f(0.0f, 0.25f, 0.25f);
		glVertex3f(-0.25f, 0.0f, 0.25f);
		glVertex3f(0.0f, -0.25f, 0.25f);
	glEnd();

	// Back Side
	glColor3f(0.6f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
		glVertex3f(0.3f, 0.0f, -0.25f);
		glVertex3f(0.0f, 0.3f, -0.25f);
		glVertex3f(-0.3f, 0.0f, -0.25f);
		glVertex3f(0.0f, -0.3f, -0.25f);
	glEnd();

	// Upper Left
	glColor3f(0.0f, 0.0f, 0.6f);
	glBegin(GL_QUADS);
		glVertex3f(0.25f, 0.0f, 0.25f);
		glVertex3f(0.3f, 0.0f, -0.25f);
		glVertex3f(0.0f, 0.3f, -0.25f);
		glVertex3f(0.0f, 0.25f, 0.25f);
	glEnd();

	// Upper Right
	glColor3f(0.5f, 0.8f, 0.2f);
	glBegin(GL_QUADS);
		glVertex3f(0.0f, 0.25f, 0.25f);
		glVertex3f(0.0f, 0.3f, -0.25f);
		glVertex3f(-0.3f, 0.0f, -0.25f);
		glVertex3f(-0.25f, 0.0f, 0.25f);
	glEnd();

	// Lower Right
	glColor3f(0.5f, 0.5f, 0.8f);
	glBegin(GL_QUADS);
		glVertex3f(-0.25f, 0.0f, 0.25f);
		glVertex3f(-0.3f, 0.0f, -0.25f);
		glVertex3f(0.0f, -0.3f, -0.25f);
		glVertex3f(0.0f, -0.25f, 0.25f);
	glEnd();

	// Lower Left
	glColor3f(0.1f, 0.7f, 0.4f);
	glBegin(GL_QUADS);
		glVertex3f(0.0f, -0.25f, 0.25f);
		glVertex3f(0.0f, -0.3f, -0.25f);
		glVertex3f(0.3f, 0.0f, -0.25f);
		glVertex3f(0.25f, 0.0f, 0.25f);
	glEnd();

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluLookAt(
		camera.eye.x, camera.eye.y, camera.eye.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
	);

	glutSwapBuffers();
	angleCube += 2.0f;
}

int main(int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("First Time?");
	#pragma omp parallel
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboardHandler);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	initGL();
	glutMainLoop();

	return 0;
}