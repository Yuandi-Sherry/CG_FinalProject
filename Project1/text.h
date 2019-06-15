#include <stdlib.h>
#include <glad/glad.h>
#include <GL/glut.h>

#include <string>

#include "OpenGLText.h"

using namespace std;
#ifndef _TEXT_
#define _TEXT_

class Text
{
public:
	Text();
	~Text();
	void init(int windowWidth, int windowHeight);
	void display(const char* str);

	OpenGLText oglText;
};


#endif // !_TEXT_
