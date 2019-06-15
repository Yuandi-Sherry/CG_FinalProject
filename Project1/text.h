#ifndef _TEXT_
#define _TEXT_

// Std. Includes
#include <iostream>
#include <map>
#include <string>
////// GLEW
////#define GLEW_STATIC
////#include <GL/glew.h>
//// GLFW
//#include <GLFW/glfw3.h>
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H
// GL includes
#include "Shader.h"

using namespace std;



/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
	GLuint TextureID;   // ID handle of the glyph texture
	glm::ivec2 Size;    // Size of glyph
	glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
	GLuint Advance;    // Horizontal offset to advance to next glyph
};

class Text
{
public:
	Text();
	~Text();
	void init(int windowWidth, int windowHeight);
	void display(string str);

	void RenderText(Shader &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
	GLuint textVAO;
	GLuint textVBO;
	Shader textShader;

	map<GLchar, Character> Characters;
	
	int width;
	int height;
};


#endif // !_TEXT_
