#include "WaterSimulation.h"
#include "Camera.h"
#include "Wave.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
extern Camera camera;
WaterSimulation::WaterSimulation()
{
}

WaterSimulation::~WaterSimulation()
{
}

void WaterSimulation::init() {
	firstRender = true;

	waterShader.init("water.vs", "water.fs");
	// set mesh
	waterMesh = new Mesh("grid.obj");
	color = glm::vec4(0.0f, 0.5f, 1.0f, 1.0f);

	waterShader.use();
	waterShader.setVec3("gridColor", color);
	waterShader.setVec3("lightColor", glm::vec4(1.f));
	waterShader.setFloat("E", glm::e<GLfloat>());
	waterShader.setFloat("damp", 0.1f);
	waterShader.setFloat("Q", 1.0f);

	// Set up waves
	// Directional
	w1.A *= 120; // 120
	w1.w *= 1.f / 150.f;
	w1.phi = 50.f * WAVE_SPEED * w1.w;
	w1.D = glm::normalize(glm::vec2(.5f, .5f));
	// Circular 1
	w2.A *= 110; // 110
	w2.w = 1.f / 1.5f;
	w2.phi = 500 * WAVE_SPEED * w2.w;
	w2.C = glm::vec2(40.f, 40.f);
	// Circular 2
	w3.A *= 130; // 130
	w3.w = 1.f / 2.5f;
	w3.phi = 600 * WAVE_SPEED * w3.w;
	w3.C = glm::vec2(-40.f, -40.f);
	sendWaves();

}

void WaterSimulation::display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	waterShader.use();
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::scale(model, glm::vec3(0.6f, 0.6f, 0.6f));
	// waterShader.setMat4("model",glm::translate(glm::mat4(1.0f), glm::vec3()));

	waterShader.setMat4("model",
		glm::translate(glm::mat4(1.0f), glm::vec3(translation[0], translation[1], translation[2]))*
		glm::scale(glm::mat4(1.0f), glm::vec3(scale[0], scale[1], scale[2])));
	waterShader.setMat4("view", camera.GetViewMatrix());
	// waterShader.setMat4("view", camera.GetViewMatrix() * glm::scale(glm::mat4(1.0f), glm::vec3(0.8, 0.8, 0.8)));
	waterShader.setMat4("projection", camera.GetProjectionMatrix());
	waterShader.setVec3("eyePos", camera.GetPosition());
	waterShader.setVec3("lightPos", glm::vec3(0.0f, 1.0f, 0.0f));
	waterShader.setFloat("blinn", 1);
	
	if (firstRender) {
		firstRender = false;
		firstRenderTime = glfwGetTime();
	}

	GLfloat dt = (GLfloat)glfwGetTime() - (GLfloat)firstRenderTime + 30;
	// cout << "dt " << dt << endl;
	waterShader.setFloat("dt", dt);

	waterMesh->draw();
}

void WaterSimulation::sendWaves() {
	waterShader.use();
	waterShader.setFloat("w1.A", w1.A);
	waterShader.setVec2("w1.C", w1.C);
	waterShader.setVec2("w1.D", w1.D);
	waterShader.setFloat("w1.w", w1.w);
	waterShader.setFloat("w1.phi", w1.phi);

	waterShader.setFloat("w2.A", w2.A);
	waterShader.setVec2("w2.C", w2.C);
	waterShader.setVec2("w2.D", w2.D);
	waterShader.setFloat("w2.w", w2.w);
	waterShader.setFloat("w2.phi", w2.phi);
	
	waterShader.setFloat("w3.A", w3.A);
	waterShader.setVec2("w3.C", w3.C);
	waterShader.setVec2("w3.D", w3.D);
	waterShader.setFloat("w3.w", w3.w);
	waterShader.setFloat("w3.phi", w3.phi);

}

void WaterSimulation::displayGUI() {
	ImGui::InputFloat("water - transX", &translation[0], -50, 50);
	ImGui::InputFloat("water - transY", &translation[1], -50, 50);
	ImGui::InputFloat("water - transZ", &translation[2], -50, 50);

	ImGui::InputFloat("water - scaleX", &scale[0], -50, 50);
	ImGui::InputFloat("water - scaleY", &scale[1], -50, 50);
	ImGui::InputFloat("water - scaleZ", &scale[2], -50, 50);

}