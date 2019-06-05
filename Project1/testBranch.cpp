#include "testBranch.h"
#include "utils.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "tgaLoader.h"

GLint SLICEX = 20;
double PI = 3.14159265;
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
}
void testBranch::drawBranch() {

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, branchTexture);
	glUniform1i(glGetUniformLocation(branchShader.ID, "branchTexture"), 0);
	branchShader.use();
	// set transformation
	glm::mat4 model(1.0f);
	glm::mat4 view(1.0f);
	glm::mat4 projection(1.0f);
	view = camera.getViewMatrix();
	projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);

	branchShader.setMat4("projection", projection);
	branchShader.setMat4("view", view);
	branchShader.setMat4("model", model);
	glBindVertexArray(branchVAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, branchEBO);
	glDrawElements(GL_TRIANGLES, (GLsizei)(branchIndices.size()), GL_UNSIGNED_INT, 0);
	//glUniform1i(glGetUniformLocation(shaderProgram, "solarTexture"), 0);

}

void testBranch::drawLeaf() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, leafTexture);
	leafShader.use();
	glBindVertexArray(leafVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void testBranch::initVars() {
	initLeaf();
	initBranch();

	// leafShader.setInt("texture2", 1);
}

void testBranch::initLeaf() {
	leafTexture = utils::loadTexture((GLchar*)"./Maple1.bmp");

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
	
	// init leaf vao, vbo
	glGenVertexArrays(1, &branchVAO);
	glGenBuffers(1, &branchVBO);
	glGenBuffers(1, &branchEBO);

	glBindVertexArray(branchVAO);

	glBindBuffer(GL_ARRAY_BUFFER, branchVBO);
	glBufferData(GL_ARRAY_BUFFER, branchVertices.size() * sizeof(branchVertices[0]), branchVertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, branchEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, branchIndices.size() * sizeof(branchVertices[0]), branchIndices.data(), GL_STATIC_DRAW);

	//glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6* sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat) * 3));
	glEnableVertexAttribArray(2);

	branchShader.use();
	glUniform1i(glGetUniformLocation(branchShader.ID, "branchTexture"), 0);

}

void testBranch::generateCylinder() {
	int upperIndex = 0, lowerIndex = 0;
	float stripe = PI / SLICEX;
	// for (int theta = 0; theta < 2 * PI; theta += stripe) {

	// }
	float radius = 0.03;
	float height = 0.3;
	
	double offset = 0;
	branchVertices.push_back(0.0f);
	branchVertices.push_back(radius);
	branchVertices.push_back(0.0f);
	branchVertices.push_back(0.5f);
	branchVertices.push_back(1.0f);
	branchVertices.push_back(0.0f);
	int indexCounter = 1;
	int outerCounter = 0;
	float phi = stripe;
	for (float phi = 0; phi <= height; phi += height) {
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
			float v = phi/height;
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
	}
	for (int i = indexCounter - 1; i > indexCounter - outerCounter; --i) {
		branchIndices.push_back(i);
		branchIndices.push_back(i - 1);
		branchIndices.push_back(indexCounter);

	}
	branchIndices.push_back(indexCounter - 1);
	branchIndices.push_back(indexCounter - outerCounter);
	branchIndices.push_back(indexCounter);
}

void testBranch::processInput(GLFWwindow * window) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		cout << "w " << endl;
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