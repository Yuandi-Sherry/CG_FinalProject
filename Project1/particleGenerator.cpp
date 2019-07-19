#include "particleGenerator.h"
extern Camera camera;
ParticleGenerator::ParticleGenerator()
{
}
void ParticleGenerator::display(GLfloat dt, GLuint newParticles){
	Update(dt, newParticles);
	Draw();
}
void ParticleGenerator::Update(GLfloat dt, GLuint newParticles)
{
	// Add new particles 
	for (GLuint i = 0; i < newParticles; ++i)
	{
		int unusedParticle = this->firstUnusedParticle();
		particles[unusedParticle]=createParticle();
		//cout << unusedParticle  << " " << particles[unusedParticle].Position.y << endl;
	}
	// Update all particles
	for (GLuint i = 0; i < this->amount; ++i)
	{
		Particle &p = this->particles[i];
		p.Position -= dt * p.Velocity;
	}
}

// Render all particles
void ParticleGenerator::Draw()
{
	// Use additive blending to give it a 'glow' effect
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	this->shader.use();
	GLuint VBO;
	glm::mat4 model = glm::mat4(1.0f);
	//model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
	shader.setMat4("model",glm::translate(glm::mat4(1.0f), glm::vec3()));

	//shader.setMat4("model",
		//glm::translate(glm::mat4(1.0f), glm::vec3(translation[0], translation[1], translation[2]))*
		//glm::scale(glm::mat4(1.0f), glm::vec3(scale[0], scale[1], scale[2])));
	shader.setMat4("view", camera.GetViewMatrix());
	// waterShader.setMat4("view", camera.GetViewMatrix() * glm::scale(glm::mat4(1.0f), glm::vec3(0.8, 0.8, 0.8)));
	shader.setMat4("projection", camera.GetProjectionMatrix());
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	//glBindVertexArray(0);
	int low = 0;
	for (Particle particle : this->particles)
	{
		if (particle.Position.y > 0)
		{
			GLfloat vertices[] = {
				particle.Position.x, particle.Position.y + rainHeight , particle.Position.z, 1.0f, 1.0f, 1.0f,
				particle.Position.x, particle.Position.y, particle.Position.z, 1.0f, 1.0f, 1.0f,
			};
			glLineWidth(rainWidth);
			//cout << particle.Position.x << " " << particle.Position.y << " " << particle.Position.z << endl;
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			glDrawArrays(GL_LINES, 0, 2);
			//glBindVertexArray(this->VAO);
		}
	}
	cout << low << endl;
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &VBO);
}

void ParticleGenerator::init(GLuint amount, GLfloat areaLenght, GLfloat fallHeight)
{
	this->amount = amount;
	this->areaLength = areaLenght;
	this->fallHeight = fallHeight;
	rainHeight = 1.0f;
	rainWidth = 1;
	// Create this->amount default particle instances
	for (GLuint i = 0; i < this->amount; ++i)
		this->particles.push_back(Particle());

	this->shader.init("Render.vs", "Render.fs");
}

// Stores the index of the last particle used (for quick access to next dead particle)
GLuint lastUsedParticle = 0;
GLuint ParticleGenerator::firstUnusedParticle()
{
	// First search from last used particle, this will usually return almost instantly
	for (GLuint i = lastUsedParticle; i < this->amount; ++i) {
		if (this->particles[i].Position.y < rainHeight) {
			lastUsedParticle = i;
			return i;
		}
	}
	// Otherwise, do a linear search
	for (GLuint i = 0; i < lastUsedParticle; ++i) {
		if (this->particles[i].Position.y < rainHeight) {
			lastUsedParticle = i;
			return i;
		}
	}
	// All particles are taken, override the first one (note that if it repeatedly hits this case, more particles should be reserved)
	lastUsedParticle = 0;
	return 0;
}

Particle ParticleGenerator::createParticle()
{
	Particle particle;
	particle.Position.x = (2.0f*float(rand()) / float(RAND_MAX) - 1.0f)*areaLength;
	particle.Position.z = (2.0f*float(rand()) / float(RAND_MAX) - 1.0f)*areaLength;
	particle.Position.y = fallHeight;
	particle.Color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	particle.Velocity = glm::vec3(0.0f, 40.0f, 0.0f);
	return particle;
}