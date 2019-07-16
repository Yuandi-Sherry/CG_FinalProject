#ifndef _UTILS_H_
#define _UTILS_H_
#include <stb_image.h>
#include <iostream>

#include <glad/glad.h>
#include <vector>
using namespace std;

class utils
{
public:
	static int _nTextures;
	static vector <int> _textureIDs;
	static GLuint loadTexture(GLchar* path) {
		// Generate texture ID and load texture data 
		GLuint textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		// Parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		int width, height, n;
		//stbi_set_flip_vertically_on_load(true);
		unsigned char *image = stbi_load(path, &width, &height, &n, 0);// Assign texture to ID
		if (image) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
			printf("%d, %d, %d\n", width, height, n);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			cout << "fail to load texture in " << path << endl;
		}
		stbi_image_free(image);
		glBindTexture(GL_TEXTURE_2D, 0);
		return textureID;
	}
	/*
	 * the white part of the texture will be transparent
	 */
	static GLuint loadTextureCutout(GLchar* path) {
		// Generate texture ID and load texture data 
		GLuint textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		// Parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, n;
		//stbi_set_flip_vertically_on_load(true);
		unsigned char *image = stbi_load(path, &width, &height, &n, STBI_rgb_alpha);// Assign texture to ID
		if (image) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
			printf("%d, %d, %d\n", width, height, n);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			cout << "fail to load texture in cutout" << endl;
		}

		stbi_image_free(image);
		return textureID;
	}

	static unsigned int loadCubemap(vector<std::string> faces)
	{
		unsigned int textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

		int width, height, nrChannels;
		for (unsigned int i = 0; i < faces.size(); i++)
		{
			unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
			if (data)
			{
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				stbi_image_free(data);
			}
			else
			{
				std::cout << "Cubemap texture failed to load at path: " << std::endl;
				stbi_image_free(data);
			}
		}
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		return textureID;
	}

	static GLuint LoadTextureRAW(const char * filename, int wrap, int width, int height) {
		GLuint texture;
		GLubyte * data;
		FILE * file;

		//char * folder = "Textures\\";

		// open texture data
		file = fopen(filename, "rb");

		if (file == NULL) {
			throw "File not found";
		}

		// allocate buffer
		width = width;
		height = height;

		int memorySize = width * height * 3;

		data = (GLubyte *)malloc(memorySize);

		// read texture data
		fread(data, memorySize, 1, file);
		fclose(file);

		// allocate a texture name
		glGenTextures(1, &texture);

		// select our current texture
		glBindTexture(GL_TEXTURE_2D, texture);

		// select modulate to mix texture with color for shading
		// glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		// glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

		// when texture area is small, bilinear filter the closest mipmap
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

		// when texture area is large, bilinear filter the first mipmap
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// if wrap is true, the texture wraps over at the edges (repeat)
		//       ... false, the texture ends at the edges (clamp)
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		// build our texture mipmaps
	//	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	

		// free buffer
		free(data);

		std::cout << filename << " loaded \n";

		return texture;
	}


	static GLuint setTexture(const GLuint textureIndex, int textureID, Shader shader, std::string uniformName) {

		//if (textureID < 0) {
			//cout << "[DEBUG]" <<  uniformName << " id < 0" << endl;
			//glGenTextures(1, (GLuint*)&textureID);
		//}
			
		//glActiveTexture(GL_TEXTURE0 + textureIndex);
		//cout << "[glActiveTexture] " << textureIndex << " ID: " << textureID <<  endl;

//		glBindTexture(GL_TEXTURE_2D, textureID);

		if (!uniformName.empty()) {
			shader.setInt(uniformName.c_str(), textureIndex);
		}

		_textureIDs.push_back(textureID);
		_nTextures++;
		return textureID;

	}

	static glm::vec3 arrayToVec3(float * input) {
		glm::vec3 ans(input[0], input[1], input[2]);
		return ans;
	}

	static float* vec3ToArray(glm::vec3 input) {
		float ans[3] = {
			input.x, input.y, input.z
		};
		return ans;
	}
private:

};
#endif // !_UTILS_H_
