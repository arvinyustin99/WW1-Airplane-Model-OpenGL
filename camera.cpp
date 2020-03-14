#include <iostream>
#include "camera.h"
#include <math.h>

float Camera::rad(float deg){
	return (deg * PI)/180.0f;
}

Camera::Camera(){
	currentAngleXZ = 0.0f;
	currentAngleYZ = 0.0f;
	origin = glm::vec3(0.0f, 0.0f, 0.0f);
	eye = glm::vec3(0.0f, 10.0f, 20.0f);
	target = glm::vec3(0.0f, 0.0f, 0.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
}
void Camera::reset(){
	eye = glm::vec3(0.0f, 10.0f, 20.0f);
	target = glm::vec3(0.0f, .0f, 0.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	currentAngleXZ = 0.0f;
	currentAngleYZ = 0.0f;
}

void Camera::moveLeft(){
	eye.x -= movementSpeed * cos(currentAngleXZ);
	eye.z -= movementSpeed * sin(currentAngleXZ);
}
void Camera::moveRight(){
	eye.x += movementSpeed * cos(currentAngleXZ);
	eye.z += movementSpeed * sin(currentAngleXZ);
}
void Camera::moveUp(){
	eye.y += movementSpeed;
	eye.z += movementSpeed;
}
void Camera::moveDown(){
	eye.y -= movementSpeed;
	eye.z -= movementSpeed;
}

float Camera::distance(float x1, float y1, float x2, float y2){
	float result = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
	return result;
}

void Camera::zoomIn(){
	// jarak camera dengan target, tetapi pada bidang XZ saja
	float distXZ = distance(eye.x, eye.z, target.x, target.z);
	
	// dengan rumus kesebangunan
	eye.z = (eye.z / distXZ) * (distXZ - movementSpeed);
	eye.x = (eye.x / distXZ) * (distXZ - movementSpeed);
	eye.y = (eye.y / distXZ) * (distXZ - movementSpeed);
}
void Camera::zoomOut(){
	float distXZ = distance(eye.x, eye.z, target.x, target.z);
	eye.z = (distXZ + movementSpeed) * (eye.z / distXZ);
	eye.x = (distXZ + movementSpeed) * (eye.x / distXZ);
	eye.y = (distXZ + movementSpeed) * (eye.y / distXZ);
	std::cout<<"eye.x " << eye.x << " eye.z " << eye.z << std::endl;
}

void Camera::roll(){
	up.x = up.x * cos(movementSpeed) - up.y * sin(movementSpeed);
	up.y = up.x * sin(movementSpeed) + up.y * cos(movementSpeed);
}

void Camera::rotateY(float unit){
	// Rotate the eye
	eye.x = eye.x * cos(rad(unit)) + eye.z* sin(rad(unit));
	eye.z = -1 * eye.x * sin(rad(unit)) + eye.z * cos(rad(unit));


	//Update Current Angle
	currentAngleXZ += unit;
	if (currentAngleXZ > 360.0f){
		currentAngleXZ -= 360.0f;
	}
	if (currentAngleXZ < 0){
		currentAngleXZ += 360.0f;
	}
	std::cout<<" angle: " << currentAngleXZ << std::endl;
}

void Camera::rotateX(float unit){
	// Rotate the eye
	eye.y = eye.y * cos(rad(unit)) - eye.z* sin(rad(unit));
	eye.z = eye.y * sin(rad(unit)) + eye.z * cos(rad(unit));

	// Update Current Angle
	currentAngleYZ += unit;
	if (currentAngleYZ > 360.0f){
		currentAngleYZ -= 360.0f;
	}
	if (currentAngleYZ < 0){
		currentAngleYZ += 360.0f;
	}
}