#pragma once
#ifndef TEST_BRANCH
#define TEST_BRANCH
#include "Shader.h"
#include <iostream>
#include <string>
//#include <stb_image.h>
#include <vector>
#include "Camera.h"
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "LSystem.h"
#include "tree.h"
using namespace std;
class TreeGeneration
{
public:
	TreeGeneration();
	~TreeGeneration();
	void init(glm::mat4 position = glm::mat4(1.0f));
	void display();
	void displayGUI();
	int lastLevel;
	int level;
private:
	void initVars();
	// position in global world
	glm::mat4 position = glm::mat4(1.0f);
	// leaf
	GLuint leafVAO = 0;
	GLuint leafVBO = 0;
	GLuint leafEBO = 0;
	GLuint leafTexture;
	Shader leafShader;
	void initLeaf();
	void drawLeaf(glm::vec4 start, glm::vec4 end, double radius);
	// branch
	GLuint branchVAO = 0;
	GLuint branchVBO = 0;
	GLuint branchEBO = 0;
	GLuint branchTexture;
	void initBranch();
	Shader branchShader;
	void drawBranch(glm::vec4 start, glm::vec4 end, double radius);
	// cylinder for branch
	vector<float> branchVertices;
	vector<int> branchIndices;
	void generateCylinder();
	void drawCylinder(glm::mat4 model = glm::mat4(1.0f));
	// Lsystem
	LSystem LS;
	// tree definiation
	Tree tree;
	
};
#endif // !TEST_BRANCH
