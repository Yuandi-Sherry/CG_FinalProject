#include "Skybox.h"
#include "utils.h"
#include "Camera.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
extern Camera camera;
extern int windowWidth;
extern int windowHeight;
Skybox::Skybox()
{
}

Skybox::~Skybox()
{
	glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteBuffers(1, &skyboxVAO);
}

void Skybox::init() {
	skyboxShader.init("skybox.vs", "skybox.fs");
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	faces.push_back("./skybox/siege_ft.tga");
	faces.push_back("./skybox/siege_bk.tga");
	faces.push_back("./skybox/siege_up.tga");
	faces.push_back("./skybox/siege_dn.tga");
	faces.push_back("./skybox/siege_rt.tga");
	faces.push_back("./skybox/siege_lf.tga");
	skyboxTexture = utils::loadCubemap(faces);
	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);
}

void Skybox::display() {
	//cout << "display" << endl;
    glDepthFunc(GL_LEQUAL);
	skyboxShader.use();
	glm::mat4 view = glm::mat4(glm::mat3(camera.GetViewMatrix()));//!!!!这里使得天空不会放大缩小

	glm::mat4 projection = glm::perspective(glm::radians((float)zoom), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
	//skyboxShader.setMat4("model", model);
	skyboxShader.setMat4("view" , view);
	skyboxShader.setMat4("projection", projection);

	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTexture);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);
}

void Skybox::displayGUI() {
	ImGui::InputInt("skybox zoom", &zoom, 45.0f, 1000.0f);
}