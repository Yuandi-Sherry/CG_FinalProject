#pragma once
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include <glad\glad.h>
#include <glm\glm.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <functional>
#include <unordered_map>
#include <iostream>



struct Triplet
{
	GLint x, y, z;
	Triplet(GLint val) : x(val), y(val), z(val) { }
	bool operator==(const Triplet& b) const {
		return (x == b.x) && (y == b.y) && (z == b.z);
	}
};

struct VertexFormat
{
	GLfloat xpos, ypos, zpos;
	GLfloat xnorm, ynorm, znorm;
	GLfloat xuv, yuv;

	VertexFormat(GLfloat xpos = 0, GLfloat ypos = 0, GLfloat zpos = 0,
		GLfloat xnorm = 0, GLfloat ynorm = 0, GLfloat znorm = 0,
		GLfloat xuv = 0, GLfloat yuv = 0)
		: xpos(xpos), ypos(ypos), zpos(zpos),
		xnorm(xnorm), ynorm(ynorm), znorm(znorm),
		xuv(xuv), yuv(yuv) { }
};

class Mesh {
public:
	Mesh(const GLchar* inFile, GLboolean wireframe = GL_TRUE);
	Mesh(std::string& inFile) : Mesh(inFile.c_str()) {}
	Mesh(GLuint vao, GLuint vbo, GLuint ibo, GLuint count)
		: VAO(vao), VBO(vbo), IBO(ibo), count(count) {}
	~Mesh() {
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &IBO);
		glDeleteVertexArrays(1, &VAO);
	}

	void draw();

private:
	GLuint VAO, VBO, IBO, count;
};

// Specialization of hash for Triplet type
// With this, Triplet is hashable
template <> struct std::hash<Triplet>
{
	size_t operator()(const Triplet & t) const
	{
		const size_t p1 = 73856093;
		const size_t p2 = 19349663;
		const size_t p3 = 83492791;
		return ((size_t)t.x * p1) ^ ((size_t)t.y * p2) ^ ((size_t)t.z * p3);
	}
};