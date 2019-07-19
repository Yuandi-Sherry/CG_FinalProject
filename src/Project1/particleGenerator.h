#pragma once
#ifndef PARTICLE_GENERATOR_H
#define PARTICLE_GENERATOR_H
#include <vector>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shader.h"
#include "Camera.h"


// Represents a single particle and its state
struct Particle {
	glm::vec3 Position;
	glm::vec3 Velocity;
	glm::vec4 Color;

	Particle() : Position(0.0f), Velocity(0.0f), Color(1.0f){ }
};

class ParticleGenerator
{
public:
	// Constructor
	ParticleGenerator();
	void display(GLfloat dt, GLuint newParticles);
	// Initializes particle
	void init(GLuint amount, GLfloat areaLenght, GLfloat fallHeight);
private:
	GLfloat translation[3] = { 0.0f, 1.0f, 0.0f };
	GLfloat scale[3] = { 2.0f, 0.3f, 2.0f };
	GLfloat areaLength,fallHeight;
	// State
	std::vector<Particle> particles;
	GLuint amount;
	// Render state
	Shader shader;
	GLuint VAO;
	GLfloat rainWidth, rainHeight;

	// Returns the first Particle index
	GLuint firstUnusedParticle();
	Particle createParticle();
	void Update(GLfloat dt, GLuint newParticles);
	void Draw();
};

#endif