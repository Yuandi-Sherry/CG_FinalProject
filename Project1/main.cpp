#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <fstream>
#include <string>
#include <iostream>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include "TreeGeneration.h"
#include "Skybox.h"
#include "WaterSimulation.h"
#include "Terrain.h"
#define N 888

using namespace std;
double PI = 3.14159265;

// function prototype
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow * window);

void initGUI(GLFWwindow* window);
void displayGUI(GLFWwindow* window);
GLFWwindow* initialize();
static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

// extern variables
int windowWidth = 1600;
int windowHeight = 900;
float lastX = windowWidth / 2.0;
float lastY = windowHeight / 2.0;

const char* glsl_version = "#version 130";

// keyboard and mouse manipulate
void processInput(GLFWwindow * window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

TreeGeneration treeGeneration;
Camera camera(glm::vec3(0.0f,20.0f, 20.0f));
Skybox skybox;
WaterSimulation water;
Terrain terrain;
int main() {
	GLFWwindow* window = initialize();
	// init tree
	treeGeneration.init(glm::translate(glm::mat4(1.0f),glm::vec3(0.0f, 0.0f, -50.0f)));
	skybox.init();
	water.init();
	terrain.init();
	GLdouble lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.5f, 0.6f, 0.7f, 1.0f);
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		processInput(window);
		
		//glfwMakeContextCurrent(window);
		// treeGeneration.display();
		// 
		GLdouble currentTime = glfwGetTime();
		GLdouble elapsed = currentTime - lastTime;
		lastTime = currentTime;
		
		
		water.display();
		skybox.display();
		treeGeneration.display();
		terrain.display();


		displayGUI(window);
		// GUI
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
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "FINAL_PROJECT", NULL, NULL);
	if (window == NULL) {
		glfwTerminate();
		throw "fail to init window";
	}
	// ½«´´½¨µÄ´°¿ÚµÄÉÏÏÂÎÄÉèÎªµ±Ç°Ïß³ÌµÄÖ÷ÉÏÏÂÎÄ
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSwapInterval(1); // Enable vsync


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		throw "fail to load glad";
	}
	// init GUI'
	initGUI(window);
	glEnable(GL_DEPTH_TEST);
	return window;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow * window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.ProcessKeyboard(FORWARD, 0.1);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.ProcessKeyboard(BACKWARD, 0.1);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.ProcessKeyboard(LEFT, 0.1);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.ProcessKeyboard(RIGHT, 0.1);
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
	// ----------------------------------------- modify there -----------------------------------------
	///water.displayGUI();
	camera.displayGUI();
	// skybox.displayGUI();
	// terrain.displayGUI();
	treeGeneration.displayGUI();
	// ----------------------------------------- modify there -----------------------------------------
	ImGui::End();
	// Rendering
	ImGui::Render();
	int display_w, display_h;
	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &display_w, &display_h);
	glViewport(-1, 1, display_w, display_h);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;
	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
	camera.ProcessMouseScroll(yoffset);
}

