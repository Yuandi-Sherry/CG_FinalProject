#ifndef _TERRAIN_2_
#define _TERRAIN_2_
#include <glad/glad.h>
#include "Shader.h"
class Terrain2
{
public:
	Terrain2();
	~Terrain2();
	void init();
	void display();

private:
	GLuint heightMapTexture;
	Shader terrainShader;
	GLuint terrainVAO;
	GLuint terrainVBO;
	GLuint terrinTexture;
	void loadTerrain(const string &filename, const string &texName);
};

#endif // !_TERRAIN_2_
