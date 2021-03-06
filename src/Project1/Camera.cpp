#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <iostream>
using namespace std;

extern int windowWidth;
extern int windowHeight;

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position, Position + Front, Up);
}


glm::mat4 Camera::GetProjectionMatrix()
{
	return  glm::perspective(glm::radians(Zoom), (float)windowWidth / (float)windowHeight, 0.1f, farPanel);
}

glm::vec3 Camera::GetPosition() {
	return Position;
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = MovementSpeed * deltaTime;
	if (direction == FORWARD)
		Position += Front * velocity;
	if (direction == BACKWARD)
		Position -= Front * velocity;
	if (direction == LEFT)
		Position -= Right * velocity;
	if (direction == RIGHT)
		Position += Right * velocity;
	if (direction == UP)
		Pitch += velocity;
	if (direction == DOWN)
		Pitch -= velocity;
	if (direction == KEY_LEFT)
		Yaw += velocity;
	if (direction == KEY_RIGHT)
		Yaw -= velocity;


	if (Pitch > 89.0f)
		Pitch = 89.0f;
	if (Pitch < -89.0f)
		Pitch = -89.0f;
	updateCameraVectors();
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;
	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	// Update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
	if (Zoom >= 1.0f && Zoom <= 45.0f)
		Zoom -= yoffset;
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
	// Calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);
	// Also re-calculate the Right and Up vector
	Right = glm::normalize(glm::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Up = glm::normalize(glm::cross(Right, Front));
}

void Camera::displayGUI() {
	ImGui::InputFloat("camera - positionX", &Position.x, -50, 50);
	ImGui::InputFloat("camera - positionY", &Position.y, -50, 50);
	ImGui::InputFloat("camera - positionZ", &Position.z, -50, 50);
	ImGui::RadioButton("local view", &mode, 1);
	ImGui::RadioButton("global view", &mode, 0);
	if (mode != lastMode) {
		cout << "mode != lastMode" << endl;
		lastMode = mode;
		
		// 切换为全局
		if (mode == 0) {
			// 将当前的状态保存
			localPosition = Position;
			Position = globalPosition;
			localYaw = Yaw;
			localPitch = Pitch;
			Yaw = globalYaw;
			Pitch = globalPitch;
		}
		// 切换为局部
		else {
			cout << "切换为局部" << endl;
			cout << "Position1: " << Position.x << Position.y << Position.z << endl;
			// 将当前的状态保存
			if (first) {
				Position = localPosition;
				first = false;
				
			}
			else {
				globalPosition = Position;
				Position = localPosition;

				globalYaw = Yaw;
				globalPitch = Pitch;
				Yaw = localYaw;
				Pitch = localPitch;
			}
			
			cout << "Position2: " << Position.x << Position.y << Position.z << endl;
		}
		updateCameraVectors();
	}
	ImGui::InputFloat("far panel", &farPanel, 100, 1000);
}