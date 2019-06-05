#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
using namespace std;
// 使用向量初始化
void Camera::setCamera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
{
	// 设置front向量、速度、敏感性、缩放
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	movementSpeed = SPEED;
	MouseSensitivity = SENSITIVITY;
	Zoom = ZOOM;

	this->position = position;
	worldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();

}

// 使用scalar value初始化
void Camera::setCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
{
	front = glm::vec3(0.0f, 0.0f, -1.0f);
	movementSpeed = SPEED;
	MouseSensitivity = SENSITIVITY;
	Zoom = ZOOM;

	position = glm::vec3(posX, posY, posZ);
	worldUp = glm::vec3(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();

}

void Camera::updateCameraVectors() {
	glm::vec3 front; 
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front = glm::normalize(front);
	right = glm::normalize(glm::cross(front, worldUp)); 
	up = glm::normalize(glm::cross(right, front));
}

glm::mat4 Camera::getViewMatrix() {
	return glm::lookAt(position, position + front, up);
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime) {
	float v = movementSpeed * deltaTime;
	switch (direction) {
	case FORWARD:
		position += front * v;
		break;
	case BACKWARD:
		position -= front * v;
		break;
	case LEFT:
		position += right * v;
		break;
	case RIGHT:
		position -= right * v;
		break;
	}
}

void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
	// cout << "move" << endl;
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	if (constrainPitch) {
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}
	updateCameraVectors();
}

void Camera::processMouseScroll(float yoffset) {
	// cout << "zoom" << endl;
	if (Zoom >= 1.0f && Zoom <= 45.0f)
		Zoom -= yoffset;
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;
}