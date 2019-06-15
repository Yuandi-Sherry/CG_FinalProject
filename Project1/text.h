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
	void display(const char* str);

};


#endif // !_TEXT_
