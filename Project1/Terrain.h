#ifndef _TERRAIN_H_
#define _TERRAIN_H_
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "Shader.h"
using namespace std;
class Terrain
{
public:
	Terrain();
	~Terrain();
	void init();
	void display();
private:
	Shader terrainShader;
	GLuint terrainTexture;
	GLuint terrainVAO;
	GLuint terrainVBO;
	GLuint terrainEBO;

	
};


#endif
