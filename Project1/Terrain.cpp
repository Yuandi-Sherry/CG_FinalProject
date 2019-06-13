#include "Terrain.h"
#include "utils.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include "Camera.h"
#include <vector>
extern Camera camera;
static GLuint textureNumber;
const unsigned int N = 128;
const unsigned int nVertices = N * N;
const unsigned int nIndices = (N - 1)*(N - 1) * 6;
int utils::_nTextures = 0;
vector<int> utils::_textureIDs;
Terrain::Terrain(){
	//init();
}

Terrain::~Terrain()
{
	
}

void Terrain::init() {
	// init Shader
	/*terrainShader.init("terrain.vs", "terrain.fs");
	terrainShader.use();
	geneHeightMap();
	cout << "heightMapTexture " << heightMapTexture << endl;
	// heightMapTexture = utils::loadTexture((GLchar *)"./textures/height.jfif");
	/// RenderingContext::init(terrain_vshader, terrain_fshader);
	utils::setTexture(0, heightMapTexture, terrainShader, "heightMapTex");

	/// Load material textures and bind them to textures 1 - 6.
	
	
	utils::setTexture(1, -1, terrainShader, "sandTex");
	utils::loadTexture((GLchar *)"./textures/sand.tga"); // ´í->sand

	utils::setTexture(2, -1, terrainShader, "iceMoutainTex");
	utils::loadTexture((GLchar *)"./textures/dordona_range.tga"); // ´í->sand
	//GLuint iceTexture = utils::loadTexture((GLchar *)"./textures/dordona_range.tga"); // ´í->forest
	//utils::setTexture(2, iceTexture, terrainShader, "iceMoutainTex");
	
	utils::loadTexture((GLchar *)"./textures/forest.tga");// ´í->stone
	utils::setTexture(3, -1, terrainShader, "treeTex");

	utils::loadTexture((GLchar *)"./textures/stone_2.tga");// ´í->waterTex
	utils::setTexture(4, -1, terrainShader, "stoneTex");

	utils::loadTexture((GLchar *)"./textures/water.tga"); // ´í->snow
	utils::setTexture(5, -1, terrainShader, "waterTex");

	utils::loadTexture((GLchar *)"./textures/snow.tga"); // ´í -> waterNormalMap
	utils::setTexture(6, -1, terrainShader, "snowTex");

	utils::loadTexture((GLchar *)"./textures/water_normal_map_2.tga"); // ¶Ô
	utils::setTexture(7, -1, terrainShader, "waterNormalMap");
	
	//utils::setTexture(8, shadowTexture, terrainShader, "shadowMapTex");*/

	terrainShader.init("terrain.vs", "terrain.fs");
	terrainShader.use();
	//geneHeightMap();
	// cout << "heightMapTexture " << heightMapTexture << endl;
	heightMapTexture = utils::loadTexture((GLchar *)"./textures/height.jfif");
	cout << "heightMapTexture before set " << heightMapTexture << endl;
	/// RenderingContext::init(terrain_vshader, terrain_fshader);
	utils::setTexture(0, heightMapTexture, terrainShader, "heightMapTex");
	cout << "heightMapTexture after set " << heightMapTexture << endl;

	/// Load material textures and bind them to textures 1 - 6.
	GLuint sandTexture = utils::loadTexture((GLchar *)"./textures/sand.tga");
	// cout << "sandTexture before set " << sandTexture << endl;
	utils::setTexture(1, sandTexture, terrainShader, "sandTex");
	// cout << "sandTexture after set " << sandTexture << endl;

	
	GLuint iceTexture = utils::loadTexture((GLchar *)"./textures/dordona_range.tga");
	utils::setTexture(2, iceTexture, terrainShader, "iceMoutainTex");

	GLuint treeTexture = utils::loadTexture((GLchar *)"./textures/forest.tga");
	utils::setTexture(3, treeTexture, terrainShader, "treeTex");

	GLuint stoneTexture = utils::loadTexture((GLchar *)"./textures/stone_2.tga");
	utils::setTexture(4, stoneTexture, terrainShader, "stoneTex");

	GLuint waterTexture = utils::loadTexture((GLchar *)"./textures/water.tga");
	utils::setTexture(5, waterTexture, terrainShader, "waterTex");

	GLuint snowTexture = utils::loadTexture((GLchar *)"./textures/snow.tga");
	utils::setTexture(6, snowTexture, terrainShader, "snowTex");

	/*GLuint waterNormalTexture = utils::loadTexture((GLchar *)"./textures/height.jfif");
	utils::setTexture(7, waterNormalTexture, terrainShader, "waterNormalMap");*/

	geneTriGrid();
	

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

	// initVAO
	glGenVertexArrays(1, &terrainVAO);
	glBindVertexArray(terrainVAO);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
}

void Terrain::display() {

	/// Set the context FBO as the rendering target.
	//glBindFramebuffer(GL_FRAMEBUFFER, _heightMapVBO);

	/// Specify the transformation from normalized device coordinates
	/// to texture/window coordinates.
	//glViewport(0, 0, _width, _height);

	/// Select the shader program.
	terrainShader.use();
	/// Bind all the necessary textures.
	for (int i = 0; i < utils::_nTextures; ++i) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, utils::_textureIDs[i]);
		// cout << "_textureIDs[i] " << utils::_textureIDs[i] << endl;
	}

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

	terrainShader.use();
	/// Update the content of the uniforms.
	terrainShader.setMat4("modelview", camera.GetViewMatrix() * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::scale(glm::mat4(1.0f), glm::vec3(20.0, 20.0, 10.0)));
	terrainShader.setMat4("projection", camera.GetProjectionMatrix());

	static float time = 0;
	terrainShader.setFloat("time", time);

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

void Terrain::geneTriGrid() {
	// generate 
		/// Generate the vertices (line by line) : 16^2 = 256 vertices.
	glm::vec2 vertices[nVertices];
	for (int y = 0; y < N; y++) {
		for (int x = 0; x < N; x++) {
			vertices[y*N + x] = glm::vec2(float(2.0*x) / (N - 1) - 1, float(2.0*y) / (N - 1) - 1);
		}
	}
	// cout << sizeof(vertices) << " = " << nVertices * sizeof(glm::vec2) << endl;

	// init VBO
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

	// init EBO
	glGenBuffers(1, &terrainEBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, terrainEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void Terrain::geneHeightMap() {
	// Height map texture size.
	const int texWidth(1024);
	const int texHeight(1024);

	GLuint vertexArrayID;
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);
	heightMapShader.init("heightMap.vs", "heightMap.fs");
	heightMapShader.use();

	GLuint frameBufferID;
	glGenFramebuffers(1, &frameBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferID);
	//glViewport(0, 0, texWidth, texHeight);
	// generate 2 1D texture
	genePermutationTable();
	geneGradientVectors();

	glGenTextures(1, &heightMapTexture);
	glBindTexture(GL_TEXTURE_2D, heightMapTexture);
	// Empty image (no data), one color component, unclamped 32 bits float.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, texWidth, texHeight, 0, GL_RED, GL_FLOAT, 0);
	// Simple filtering (needed).
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	//    GLenum drawBuffers[] = {GL_COLOR_ATTACHMENT0};
	//    glDrawBuffers(1, drawBuffers);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, heightMapTexture, 0);
		/// Check that our framebuffer is complete.
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cerr << "Heightmap framebuffer not complete." << std::endl;
		exit(EXIT_FAILURE);
	}

	/// Fullscreen quad : fragment shader is executed on evey pixel of the texture.
	const GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f,
		 1.0f, -1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,
	};

	// init VBO
	glGenBuffers(1, &heightMapVBO);
	glBindBuffer(GL_ARRAY_BUFFER, heightMapVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// init VAO, bind position
	glGenVertexArrays(1, &heightMapVAO);
	glBindVertexArray(heightMapVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	
	/// Render the 2 triangles (6 vertices).
	// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / 3);

	/// Clean up the now useless objects to free GPU memory.
	//glDisableVertexAttribArray(heightMapVAO);
	glDeleteBuffers(1, &heightMapVBO);
	glDeleteTextures(1, &gradVectTexture);
	glDeleteTextures(1, &permTableTexture);
	glDeleteFramebuffers(1, &frameBufferID);
	glDeleteProgram(heightMapShader.ID);
	glDeleteVertexArrays(1, &heightMapVAO);
}

void Terrain::genePermutationTable() {
	// Pseudo-randomly generate the permutation table.
	const int size(256);
	//    GLubyte permutationTable[size];
	GLfloat permutationTable[size];
	for (int k = 0; k < size; ++k)
		permutationTable[k] = k;

	// Seed the pseudo-random generator for reproductability.
	std::srand(10);

	// Fisher-Yates / Knuth shuffle.
//    GLubyte tmp;
	GLfloat tmp;
	for (int k = size - 1; k > 0; --k) {
		// Random number with 0 <= rnd <= k.
		GLuint idx = int(float(k) * std::rand() / RAND_MAX);
		tmp = permutationTable[k];
		permutationTable[k] = permutationTable[idx];
		permutationTable[idx] = tmp;
	}

	// Print the permutation table.
	//for(int k=0; k<size; ++k)
	  //  cout << permutationTable[k] << " ";

	/// Bind the permutation table to texture 0.
	
	glGenTextures(1, &permTableTexture);
	glActiveTexture(GL_TEXTURE0 + 0);
	glBindTexture(GL_TEXTURE_1D, permTableTexture);
	heightMapShader.setInt("permTableTex", permTableTexture);
	// Filled image, one color component, unclamped 32 bits float.
	// GL_R8UI or GL_R32I does not work on my machine.
	glTexImage1D(GL_TEXTURE_1D, 0, GL_R32F, size, 0, GL_RED, GL_FLOAT, permutationTable);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

void Terrain::geneGradientVectors() {
	/// Gradients for 2D noise.
	static GLfloat gradients[] = {
		1.0f,  1.0f,
	   -1.0f,  1.0f,
		1.0f, -1.0f,
	   -1.0f, -1.0f,
		0.0f,  1.0f,
		0.0f, -1.0f,
		1.0f,  0.0f,
	   -1.0f,  0.0f,
	};

	// GLuint gradVectTexID;
	glGenTextures(1, &gradVectTexture);
	glActiveTexture(GL_TEXTURE0 + 1);
	glBindTexture(GL_TEXTURE_1D, gradVectTexture);
	heightMapShader.setInt("gradVectTex", gradVectTexture);
	// Filled image, two color components, unclamped 32 bits float.
	// GL_RG8I does not work on my machine.
	//glTexImage1D(GL_TEXTURE_1D, 0, GL_RG8I, nVectors, 0, GL_RG, GL_BYTE, gradients);
	glTexImage1D(GL_TEXTURE_1D, 0, GL_RG32F, 8, 0, GL_RG, GL_FLOAT, gradients);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

}