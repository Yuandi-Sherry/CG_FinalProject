#include "Skybox.h"
#include "utils.h"
#include "Camera.h"
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
	cout << "cubeVertices.size() " << skyboxVertices[100]  << endl;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);


	faces.push_back("./skybox/right.jpg");
	faces.push_back("./skybox/left.jpg");
	faces.push_back("./skybox/top.jpg");
	faces.push_back("./skybox/bottom.jpg");
	faces.push_back("./skybox/front.jpg");
	faces.push_back("./skybox/back.jpg");
	skyboxTexture = utils::loadCubemap(faces);
	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);
	cout << "faces.size()" << endl;
}

void Skybox::display() {
	//cout << "display" << endl;
    glDepthFunc(GL_LEQUAL);
	skyboxShader.use();
	glm::mat4 view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
	//cout << "camera.Zoom " << glm::radians(camera.Zoom) << endl;
	glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
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