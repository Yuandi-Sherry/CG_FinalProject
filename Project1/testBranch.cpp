#include "testBranch.h"
#include "utils.h"

testBranch::testBranch() {
	branchShader.init("textureShader.vs", "textureShader.fs");
	colorShader.init("colorShader.vs", "colorShader.fs");
	initVars();
}
testBranch::~testBranch() {
	glDeleteVertexArrays(1, &leafVAO);
	glDeleteBuffers(1, &leafVBO);
	glDeleteBuffers(1, &leafEBO);
}

void testBranch::drawBranch() {

}

void testBranch::drawLeaf() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, woodTexture);
	branchShader.use();
	glBindVertexArray(leafVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void testBranch::initVars() {
	woodTexture = utils::loadTexture((GLchar* )"./Maple1.bmp");
	
	float temp[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	
	// init leaf vao, vbo
	glGenVertexArrays(1, &leafVAO);
	glGenBuffers(1, &leafVBO);
	glGenBuffers(1, &leafEBO);

	glBindVertexArray(leafVAO);

	glBindBuffer(GL_ARRAY_BUFFER, leafVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(temp), &temp, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, leafEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	//glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	branchShader.use();
	glUniform1i(glGetUniformLocation(branchShader.ID, "woodTexture"), 0);
	// branchShader.setInt("texture2", 1);
}