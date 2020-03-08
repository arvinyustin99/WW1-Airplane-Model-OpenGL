#include <iostream>
#include "camera.h"

Camera::Camera(){
	eye = glm::vec3(0.0f, 0.0f, 0.0f);

	target = glm::vec3(0.0f, 0.0f, -5.0f);
	direction = glm::normalize(eye - target);

	up = glm::vec3(0.0f, 1.0f, 0.0f);
	xPosAxis = glm::normalize(glm::cross(up, direction));

	yPosAxis = glm::cross(direction, xPosAxis);
}
void Camera::reset(){
	eye = glm::vec3(0.0f, 0.0f, 0.0f);
	target = glm::vec3(0.0f, 0.0f, -5.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::moveLeft(){
	eye.x -= movementSpeed;
}

void Camera::moveRight(){
	eye.x += movementSpeed;
}

void Camera::moveUp(){
	eye.y += movementSpeed;
}

void Camera::moveDown(){
	eye.y -= movementSpeed;
}

void Camera::zoomIn(){
	eye.z -= movementSpeed;
}

void Camera::zoomOut(){
	eye.z += movementSpeed;
}