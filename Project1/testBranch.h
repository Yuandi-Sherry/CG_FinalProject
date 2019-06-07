#pragma once
#ifndef TEST_BRANCH
#define TEST_BRANCH
#include "Shader.h"
#include <iostream>
#include <string>
#include <stb_image.h>
#include <vector>
#include "Camera.h"
#include <GLFW/glfw3.h>
#include "LSystem.h"
#include "tree.h"
using namespace std;
class testBranch
{
public:
	testBranch();
	~testBranch();
	void drawBranch();
	void drawLeaf();
	// process input
	void processInput(GLFWwindow * window);
	void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	void init();
	void display();

	void drawBranch(glm::vec4 start, glm::vec4 end, double radius);
private:
	void initVars();
	// leaf
	GLuint leafVAO = 0;
	GLuint leafVBO = 0;
	GLuint leafEBO = 0;
	GLuint leafTexture;
	Shader leafShader;
	void initLeaf();
	// branch
	GLuint branchVAO = 0;
	GLuint branchVBO = 0;
	GLuint branchEBO = 0;
	vector<float> branchVertices;
	vector<int> branchIndices;
	GLuint branchTexture;
	Shader branchShader;
	void initBranch();
	// cylinder
	void generateCylinder();
	void drawCylinder(glm::mat4 model = glm::mat4(1.0f));
	Camera camera;
	LSystem LS;
	Tree tree;
	
};
#endif // !TEST_BRANCH
