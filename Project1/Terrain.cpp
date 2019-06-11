#include "Terrain.h"
#include "utils.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include "Camera.h"
extern Camera camera;
static GLuint textureNumber;
const unsigned int N = 128;
const unsigned int nVertices = N * N;
const unsigned int nIndices = (N - 1)*(N - 1) * 6;

Terrain::Terrain(){
	//init();
}

Terrain::~Terrain()
{
	
}

void Terrain::init() {
	terrainShader.init("terrain.vs", "terrain.fs");
	terrainTexture = utils::loadTexture((GLchar * )"./Mossy_Rock.tga");

	glGenVertexArrays(1, &terrainVAO);
	glBindVertexArray(terrainVAO);
	// generate 
		/// Generate the vertices (line by line) : 16^2 = 256 vertices.
	glm::vec2 vertices[nVertices];
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			vertices[y*N + x] = glm::vec2(float(2.0*x) / (N - 1) - 1, float(2.0*y) / (N - 1) - 1);
		}
	}
	// cout << sizeof(vertices) << " = " << nVertices * sizeof(glm::vec2) << endl;

	/// Copy the vertices to GPU in a vertex buffer.
	glGenBuffers(1, &terrainVBO);
	glBindBuffer(GL_ARRAY_BUFFER, terrainVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/// Indices that form the triangles.
	/// Grid of 15x15 squares : 225 squares -> 450 triangles -> 1350 indices.
	unsigned int indices[nIndices];
	for (int y = 0; y < N - 1; y++) {
		for (int x = 0; x < N - 1; x++) {
			/// Upper left triangle of the square.
			indices[y*(N - 1) * 6 + x * 6 + 0] = y * N + x + 0;
			indices[y*(N - 1) * 6 + x * 6 + 1] = y * N + x + 1;
			indices[y*(N - 1) * 6 + x * 6 + 2] = y * N + x + N;
			/// Lower right triangle of the square.
			indices[y*(N - 1) * 6 + x * 6 + 3] = y * N + x + 1;
			indices[y*(N - 1) * 6 + x * 6 + 4] = y * N + x + N + 1;
			indices[y*(N - 1) * 6 + x * 6 + 5] = y * N + x + N;
		}
	}

	// Copy the indices to GPU in an index buffer.
	glGenBuffers(1, &terrainEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	/// light
	terrainShader.use();
	glm::vec3 light_dir_tmp(1.0f, 0.5f, 1.0f);
	glm::vec3 Ia(1.0f, 1.0f, 1.0f);
	glm::vec3 Id(1.0f, 1.0f, 1.0f);
	glm::vec3 Is(1.0f, 1.0f, 1.0f);
	terrainShader.setVec3("light_dir_tmp", light_dir_tmp);
	terrainShader.setVec3("Ia", Ia);
	terrainShader.setVec3("Id", Id);
	terrainShader.setVec3("Is", Is);

	/// Define the material properties and pass them to the shaders.
	glm::vec3 ka(0.65f, 0.7f, 0.65f);
	glm::vec3 kd(0.25f, 0.15f, 0.25f);
	glm::vec3 ks(0.35f, 0.25f, 0.35f);
	float p = 60.0f;

	
	terrainShader.setVec3("ka", ka);
	terrainShader.setVec3("kd", kd);
	terrainShader.setVec3("ks", ks);
	terrainShader.setFloat("p", p);

	terrainShader.setInt("N", N);

	cout << terrainVAO << " " << terrainVBO << " " << terrainEBO << endl;

	/// Set uniform IDs.
	//_modelviewID = glGetUniformLocation(_programID, "modelview");
	//_projectionID = glGetUniformLocation(_programID, "projection");

	//_timeID = glGetUniformLocation(_programID, "time");

	//_vertexAttribID = glGetAttribLocation(_programID, "position");
}

void Terrain::display() {

	/// Set the context FBO as the rendering target.
	//glBindFramebuffer(GL_FRAMEBUFFER, _frameBufferID);

	/// Specify the transformation from normalized device coordinates
	/// to texture/window coordinates.
	//glViewport(0, 0, _width, _height);

	/// Select the shader program.
	terrainShader.use();
	/// Bind all the necessary textures.

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, terrainTexture);

	/*
	 * Bind vertex array
	 * A vertex array object holds references to the vertex buffers, the index
	 * buffer and the layout specification of the vertex itself. At runtime,
	 * you can just glBindVertexArray to recall all of these information.
	 */
	glBindVertexArray(terrainVAO);

	/// Vertex attribute "position" points to data from the currently binded array buffer.
	glBindBuffer(GL_ARRAY_BUFFER, terrainVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainEBO);
	glEnableVertexAttribArray(terrainVAO);
	glVertexAttribPointer(terrainVAO, 2, GL_FLOAT, GL_FALSE, 0, 0);

	/// Update the content of the uniforms.
	terrainShader.setMat4("modelview", camera.GetViewMatrix());
	terrainShader.setMat4("projection", camera.GetProjectionMatrix());

	

	/// Spot light projection.
	float fieldOfView = 45.0f;
	float aspectRatio = 1.f;
	float nearPlane = 0.1f;
	float farPlane = 10.f;
	static glm::mat4 lightProjection = glm::perspective(fieldOfView, aspectRatio, nearPlane, farPlane);

	/// Light position.
	glm::vec3 lightPosition(0.0, 3.0, 0.0);
	glm::vec3 lightAt(0.0, 0.0, 0.0);
	glm::vec3 lightUp(0.0, 0.0, 1.0);
	static glm::mat4 view = glm::lookAt(lightPosition, lightAt, lightUp);

	/// Assemble the lightMVP matrix for a spotlight source.
	glm::mat4 lightMVP = lightProjection * view;

	/* This can be fixed by tweaking the fetch coordinates directly in the fragment
	 *  shader but it¡¯s more efficient to multiply the homogeneous coordinates by the
	 * following matrix, which simply divides coordinates by 2 ( the diagonal : [-1,1]
	 * -> [-0.5, 0.5] ) and translates them ( the lower row : [-0.5, 0.5] -> [0,1] ).
	 */

	float tmp[4][4] = {
		0.5f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.5f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f
	};
	glm::mat4 biasMatrix= glm::make_mat4x4((float * )&tmp);
	glm::mat4 lightOffsetMVP = biasMatrix * lightMVP;
	terrainShader.setMat4("lightOffsetMVP", lightOffsetMVP);
	/// Clear the screen framebuffer.
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/// Render the terrain from camera point of view to default framebuffer.
	glDrawElements(GL_TRIANGLES, nIndices, GL_UNSIGNED_INT, 0);


	glDisableVertexAttribArray(terrainVAO);
}