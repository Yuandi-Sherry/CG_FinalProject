#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#ifndef _WAVE_H_
#define _WAVE_H_

#define WAVE_AMPLITUDE 0.01f
#define WAVE_LENGTH 0.01f
#define WAVE_SPEED 0.01f
struct Wave {
	GLfloat A = WAVE_AMPLITUDE;
	glm::vec2 D;
	glm::vec2 C;
	GLfloat w = 2.f * glm::pi<GLfloat>() / WAVE_LENGTH;
	GLfloat phi = WAVE_SPEED * w;
};

#endif