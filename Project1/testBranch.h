#pragma once
#ifndef TEST_BRANCH
#define TEST_BRANCH
#include "Shader.h"
#include <iostream>
#include <string>
#include <stb_image.h>
#include <vector>
using namespace std;
class testBranch
{
public:
	testBranch();
	~testBranch();
	void drawBranch();
	void drawLeaf();
	
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
};
#endif // !TEST_BRANCH
