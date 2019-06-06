#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <string>
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include "testBranch.h"
#define N 888
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow * window);
bool readFile(const string & fileName, string & content);
void checkCompile(const int & shader, const int & checkType);
void compileShader(unsigned int & shader, const char * filename, const int & shaderType);

void initGUI(GLFWwindow* window);
void displayGUI(GLFWwindow* window);
GLFWwindow* initialize();
int windowWidth = 1200;
int windowHeight = 1200;
float lastX = windowWidth / 2.0;
float lastY = windowHeight / 2.0;
static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}
// ×ÅÉ«Æ÷ÎÄ¼þ
const char* vertexShaderFile = "shader.vs";
const char* fragmentShaderFile = "shader.fs";
const char* glsl_version = "#version 130";
// ÇåÆÁÑÕÉ«
ImVec4 clear_color = ImVec4(0, 0, 0, 1.00f);
testBranch test;

void processInput(GLFWwindow * window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


int main() {
	GLFWwindow* window = initialize();
	test.init();
	// äÖÈ¾Ñ­»·
	// Ã¿´ÎÑ­»·¿ªÊ¼Ç°¼ì²éGLFWÊÇ·ñ±»ÍË³ö
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	while (!glfwWindowShouldClose(window)) {
		// ¼ì²é´¥·¢ÊÂ¼þ¡¢¸üÐÂ´°¿Ú£¬»Øµ÷
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		processInput(window);
		//displayGUI(window);
		glfwMakeContextCurrent(window);
		test.display();
		// ½»»»»º³å¡¢»æÖÆ¡¢ÏÔÊ¾
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// ÊÍ·Å/É¾³ý×ÊÔ´
	glfwTerminate();

	return 0;
}

GLFWwindow* initialize() {
	// Setup window
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		throw "fail to init glfw";
	// ³õÊ¼»¯GLFW
	glfwInit();
	// ÉèÖÃGLFW - OpenGL 3.3 core mode
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// ´´½¨´°¿Ú
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "CG_HOMEWORK2", NULL, NULL);
	if (window == NULL) {
		glfwTerminate();
		throw "fail to init window";
	}
	// ½«´´½¨µÄ´°¿ÚµÄÉÏÏÂÎÄÉèÎªµ±Ç°Ïß³ÌµÄÖ÷ÉÏÏÂÎÄ
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSwapInterval(1); // Enable vsync
	// ³õÊ¼»¯GLAD£¬¼ÓÔØÏµÍ³Ïà¹ØOpenGLº¯ÊýÖ¸Õë
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw "fail to load glad";
	}
	// init GUI'
	initGUI(window);
	glEnable(GL_DEPTH_TEST);
	return window;
}
/*
 * Êó±êµ÷ÕûºóµÄÐÂµÄ´óÐ¡ÎªºóÁ½¸ö²ÎÊý
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
/*
 * ´¦ÀíÊäÈë
 */
void processInput(GLFWwindow * window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	test.processInput(window);
}
/*
 * ÎÄ¼þ¶ÁÈ¡
 */
bool readFile(const string & fileName, string & content) {
	ifstream inFile(fileName);
	if (!inFile) {
		cout << "Fail to read " << fileName.c_str() << endl;
		return false;
	}
	else {
		string line;
		while (getline(inFile, line)) {
			content.append(line);
			content.append("\n");
		}
	}
	return true;
}

void checkCompile(const int & shader, const int & checkType) {
	int success;
	char info[512];
	if (checkType == 1) {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			cout << "COMPILE ERROR: " << endl;
			glGetShaderInfoLog(shader, 512, NULL, info);
			cout << info << endl;
		}
	}
	else if (checkType == 2) {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			cout << "COMPILE ERROR: " << endl;
			glGetProgramInfoLog(shader, 512, NULL, info);
			cout << info << endl;
		}
	}
}
/*
 * ±àÒë×ÅÉ«Æ÷
 @shader ×ÅÉ«Æ÷
 @filename ×ÅÉ«Æ÷ÎÄ¼þÃû
 @type ×ÅÉ«Æ÷Àà±ð 1->vertex, 2->fragment
 */
void compileShader(unsigned int & shader, const char * filename, const int & shaderType) {
	shader = glCreateShader(shaderType);
	string shaderSource;
	if (readFile(filename, shaderSource)) {
		const GLchar* p[1];
		p[0] = shaderSource.c_str();
		GLint Lengths[1];
		Lengths[0] = strlen(shaderSource.c_str());
		glShaderSource(shader, 1, p, Lengths);
		glCompileShader(shader);
		checkCompile(shader, 1);
	}
	else {
		cout << "Fail to read shader file" << endl;
	}
}

void initGUI(GLFWwindow* window) {
	// set up GUI context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
}

void displayGUI(GLFWwindow* window) {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("Options", NULL, ImGuiWindowFlags_MenuBar);
	if (ImGui::BeginMenuBar())
	{
		ImGui::EndMenuBar();
	}

	ImGui::End();
	// Rendering
	ImGui::Render();
	int display_w, display_h;
	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &display_w, &display_h);
	glViewport(-1, 1, display_w, display_h);
	glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	//test.mouseCallback(window, xpos, ypos);
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	test.scrollCallback(window, xoffset, yoffset);
}
