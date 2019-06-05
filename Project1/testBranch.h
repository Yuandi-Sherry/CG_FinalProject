#pragma once
#ifndef TEST_BRANCH
#define TEST_BRANCH
#include "Shader.h"
#include <iostream>
#include <string>
#include <stb_image.h>
using namespace std;
class testBranch
{
public:
	testBranch();
	~testBranch();
	void drawBranch();
	void drawLeaf();

private:
	Shader branchShader;
	Shader colorShader;
	void initVars();
	GLuint leafVAO = 0;
	GLuint leafVBO = 0;
	GLuint leafEBO = 0;
	GLuint woodTexture;

};
#endif // !TEST_BRANCH
