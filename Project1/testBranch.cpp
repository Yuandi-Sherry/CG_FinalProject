﻿#include "testBranch.h"
#include "utils.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "tgaLoader.h"
#include <cmath>

GLint SLICEX = 20;
extern double PI;
extern int windowWidth;
extern int windowHeight;
extern float lastX;
extern float lastY;
testBranch::testBranch() {
	
}
testBranch::~testBranch() {
	glDeleteVertexArrays(1, &leafVAO);
	glDeleteBuffers(1, &leafVBO);
	glDeleteBuffers(1, &leafEBO);
}

void testBranch::init() {
	leafShader.init("textureShader.vs", "textureShader.fs");
	branchShader.init("textureShader.vs", "textureShader.fs");
	initVars();
	camera.setCamera();
	// dealing with l system
	LS.init(tree);
	LS.initGrammar();
	LS.generateFractal();
	generateCylinder();
}

void testBranch::drawCylinder(glm::mat4 model) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, branchTexture);
	glUniform1i(glGetUniformLocation(branchShader.ID, "myTexture"), 0);
	branchShader.use();
	// set transformation
	glm::mat4 view(1.0f);
	glm::mat4 projection(1.0f);
	view = camera.getViewMatrix();
	projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 1000.0f);

	branchShader.setMat4("projection", projection);
	branchShader.setMat4("view", view);
	branchShader.setMat4("model", model);
	glBindVertexArray(branchVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, branchEBO);
	glDrawElements(GL_TRIANGLES, (GLsizei)(branchIndices.size()), GL_UNSIGNED_INT, 0);
	//glUniform1i(glGetUniformLocation(shaderProgram, "solarTexture"), 0);
}
void testBranch::drawBranch(glm::vec4 start, glm::vec4 end, double radius) {
	glm::vec3 delta = glm::vec3(end.x - start.x, end.y - start.y, end.z - start.z);
	GLfloat distance = sqrt(pow(delta.x, 2) + pow(delta.y, 2) + pow(delta.z, 2));
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(start.x, start.y, start.z));
	if (delta.x == 0 && delta.z == 0) {
		drawCylinder(translation* glm::scale(glm::mat4(1.0f), glm::vec3(radius, (GLfloat)distance, radius)));
	}
	else {
		glm::vec3 assVec = glm::vec3(0, distance, 0);
		glm::vec3 normal = glm::cross(assVec, delta);
		GLfloat angle = acos(glm::dot(assVec, delta) / distance / distance);
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, normal);
		glm::mat4 model = rotation* glm::scale(glm::mat4(1.0f), glm::vec3(radius, (GLfloat)distance, radius));
		drawCylinder(translation* model);
	}
}

void testBranch::drawLeaf(glm::vec4 start, glm::vec4 end, double radius) {
	glm::vec3 delta = glm::vec3(end.x - start.x, end.y - start.y, end.z - start.z);
	GLfloat distance = sqrt(pow(delta.x, 2) + pow(delta.y, 2) + pow(delta.z, 2));
	glm::mat4 translation = glm::translate(glm::mat4(1.0f), glm::vec3(start.x + radius/3, start.y+radius/3, start.z));
	glm::mat4 model(1.0f);
	if (delta.x == 0 && delta.z == 0) {
		model = translation * glm::scale(glm::mat4(1.0f), glm::vec3(radius, (GLfloat)radius,1));
	}
	else {
		glm::vec3 assVec = glm::vec3(0, distance, 0);
		glm::vec3 normal = glm::cross(assVec, delta);
		GLfloat angle = acos(glm::dot(assVec, delta) / distance / distance);
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, normal);
		model = translation *  rotation * glm::scale(glm::mat4(1.0f), glm::vec3(radius, radius, 1));
	}
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, leafTexture);
	glUniform1i(glGetUniformLocation(leafShader.ID, "myTexture"), 0);
	leafShader.use();
	// set transformation
	glm::mat4 view(1.0f);
	glm::mat4 projection(1.0f);
	view = camera.getViewMatrix();
	projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 1000.0f);

	leafShader.setMat4("projection", projection);
	leafShader.setMat4("view", view);
	leafShader.setMat4("model", model);
	//glBindVertexArray(branchVAO);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, branchEBO);
	//glDrawElements(GL_TRIANGLES, (GLsizei)(branchIndices.size()), GL_UNSIGNED_INT, 0);



	//leafShader.use();
	glBindVertexArray(leafVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void testBranch::initVars() {
	initLeaf();
	initBranch();

	// leafShader.setInt("texture2", 1);
}

void testBranch::initLeaf() {
	leafTexture = utils::loadTextureCutout((GLchar*)"./Maple1.png");

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

	leafShader.use();
	glUniform1i(glGetUniformLocation(leafShader.ID, "leafTexture"), 0);
}

GLuint createTexture(char const *filePath) {
	return loadtga(filePath);
}

void testBranch::initBranch() {
	// branchTexture = loadtga("./Sun.tga");
	branchTexture = utils::loadTexture((GLchar*)"./bark1.bmp");
	generateCylinder();
	branchShader.use();
	glUniform1i(glGetUniformLocation(branchShader.ID, "myTexture"), 0);

}

void testBranch::generateCylinder() {
	int upperIndex = 0, lowerIndex = 0;
	float stripe = 1.0f / SLICEX;
	double radius = 1;
	double offset = 0;
	int indexCounter = 1;
	int outerCounter = 0;
	float phi = stripe;
	for (float phi = 0; phi <= 1; phi += 1) {
		int innerCounter = 0;
		for (float theta = 0; theta <= PI*2; theta += stripe) {
			innerCounter++;
			float x = radius * cos(theta + offset);
			float y = phi;
			float z = radius * sin(theta + offset);
			branchVertices.push_back(x);
			branchVertices.push_back(y);
			branchVertices.push_back(z);
			// ?? 2 
			float u = theta / 2 / PI;
			float v = phi/1;
			branchVertices.push_back(u);
			branchVertices.push_back(v);
			branchVertices.push_back(0);

			if (theta != 0) {
				if (abs(phi - stripe) < 0.00001) { // ��һ��
					branchIndices.push_back(indexCounter - 1);
					branchIndices.push_back(indexCounter);
					branchIndices.push_back(0);
				}
				else { // ֮��ÿ��������������
					branchIndices.push_back(indexCounter - 1);
					branchIndices.push_back(indexCounter);
					branchIndices.push_back(indexCounter - outerCounter - 1);
					branchIndices.push_back(indexCounter);
					branchIndices.push_back(indexCounter - outerCounter - 1);
					branchIndices.push_back(indexCounter - outerCounter);
				}
			}

			indexCounter++;

		}
		if (abs(phi - stripe) < 0.0001) {
			//vector<int>({ indexCounter - innerCounter, indexCounter - 1, 0 })
			branchIndices.push_back(indexCounter - innerCounter);
			branchIndices.push_back(indexCounter - 1);
			branchIndices.push_back(0);
		}
		else {
			branchIndices.push_back(indexCounter - innerCounter);
			branchIndices.push_back(indexCounter - 1);
			branchIndices.push_back(indexCounter - outerCounter - 1);
			branchIndices.push_back(indexCounter - innerCounter);
			branchIndices.push_back(indexCounter - outerCounter - innerCounter);
			branchIndices.push_back(indexCounter - outerCounter - 1);
		}
		outerCounter = innerCounter;
		offset += stripe / 2;
		radius *= 0.9;
	}
	for (int i = indexCounter - 1; i > indexCounter - outerCounter; --i) {
		branchIndices.push_back(i);
		branchIndices.push_back(i - 1);
		branchIndices.push_back(indexCounter);

	}
	branchIndices.push_back(indexCounter - 1);
	branchIndices.push_back(indexCounter - outerCounter);
	branchIndices.push_back(indexCounter);

	// init leaf vao, vbo, ebo
	glGenVertexArrays(1, &branchVAO);
	glGenBuffers(1, &branchVBO);
	glGenBuffers(1, &branchEBO);

	glBindVertexArray(branchVAO);

	glBindBuffer(GL_ARRAY_BUFFER, branchVBO);
	glBufferData(GL_ARRAY_BUFFER, branchVertices.size() * sizeof(branchVertices[0]), branchVertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, branchEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, branchIndices.size() * sizeof(branchVertices[0]), branchIndices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat) * 3));
	glEnableVertexAttribArray(2);
}

void testBranch::processInput(GLFWwindow * window) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.processKeyboard(FORWARD, 0.1);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.processKeyboard(BACKWARD, 0.1);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.processKeyboard(LEFT, 0.1);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.processKeyboard(RIGHT, 0.1);
	}
}

void testBranch::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;
	camera.processMouseMovement(xoffset, yoffset);
}
void testBranch::scrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	camera.processMouseScroll(yoffset);
}

void testBranch::display() {
	// draw trunks
	for (int i = 0; i < LS.trunks.size(); i++) {
		drawBranch(LS.trunks[i].pos1, LS.trunks[i].pos2, LS.trunks[i].radius);
	}
	/*for (int i = 0; i < 1; i++) {
		cout << LS.leaves[i].pos1.x << " " << LS.leaves[i].pos1.y << " " << LS.leaves[i].pos1.z << endl;
		cout << LS.leaves[i].pos2.x << " " << LS.leaves[i].pos2.y << " " << LS.leaves[i].pos2.z << endl;
		cout << LS.leaves[i].radius << endl;
	}*/
	// draw leaves
	for (int i = 0; i < LS.leaves.size(); i++) {
		drawLeaf(LS.leaves[i].pos1, LS.leaves[i].pos2, tree.leaf.radius);
	}
}