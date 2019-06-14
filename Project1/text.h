//#include <windows.h>
//#include <stdio.h>
//#include <math.h>
//#include <GL/glut.h>
//#include <stdlib.h>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

#include <stb_image.h>

#include "Shader.h"
#include "Camera.h"
#include "Texture2D.h"
#include "TextMesh.h"

#include "Glyph3D.h"
#include "FreeTypeFont.h"
#include "Tessellator.h"

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
#ifndef _TEXT_
#define _TEXT_

class Text
{
public:
	Text();
	~Text();
	void init();
	void display(const char* str, Camera camera);
	//void selectFont(int size, int charset, const char* face);
	//void drawString(const char* str);
	
	const int MAX_CHAR = 128;

	Shader textShader;
	std::vector<GLuint> advances;
	std::vector<TextMesh> string3D;
};


#endif // !_TEXT_
