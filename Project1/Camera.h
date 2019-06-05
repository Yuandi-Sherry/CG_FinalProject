#pragma once
#ifndef CAMERA_H_
#define CAMERA_H_
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
enum CameraMovement {
	FORWARD, BACKWARD, LEFT, RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	float Yaw; 
	float Pitch;
	
	float movementSpeed;
	float MouseSensitivity;
	float Zoom;
	Camera() {

	}
	void setCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	void setCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
	~Camera() {

	}
	glm::mat4 getViewMatrix();
	void processKeyboard(CameraMovement direction, float deltaTime);
	void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
	void processMouseScroll(float yoffset);

private:
	void updateCameraVectors();
};

#endif // !CAMERA_H_
