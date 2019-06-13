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
<<<<<<< HEAD
// private:
=======
	void displayGUI();
private:
	glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(200.0f, 200.0f, 20.0f);
>>>>>>> sherry
	Shader terrainShader;
	Shader heightMapShader;
	// GLuint terrainTexture;
	GLuint terrainVAO;
	GLuint terrainVBO;
	GLuint terrainEBO;
	GLuint shadowTexture;
	GLuint heightMapTexture;
	void geneTriGrid();

	// heightMap
	void geneHeightMap();
	GLuint permTableTexture;
	GLuint gradVectTexture;
	GLuint heightMapVAO;
	GLuint heightMapVBO;
	void genePermutationTable();
	void geneGradientVectors();

	
};


#endif
