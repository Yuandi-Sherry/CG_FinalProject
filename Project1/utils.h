#ifndef _UTILS_H_
#define _UTILS_H_
#include <stb_image.h>
class utils
{
public:
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
		stbi_set_flip_vertically_on_load(true);
		unsigned char *image = stbi_load(path, &width, &height, &n, 0);// Assign texture to ID
		if (image) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
			printf("%d, %d, %d\n", width, height, n);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else {
			cout << "fail to load texture" << endl;
		}
		stbi_image_free(image);
		return textureID;
	}

private:

};
#endif // !_UTILS_H_
