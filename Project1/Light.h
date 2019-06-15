#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#ifndef _LIGHT_H_
#define _LIGHT_H_
class Light
{
public:
	Light();
	~Light();
	void displayGUI();
	float * getLightColor() {
		return lightColor;
	}
	float * getLightPos() {
		return lightPos;
	}
	float * getLightDir() {
		return lightDir;
	}
private:
	float lightColor[3] = { 1.0f, 0.0f, 0.0f };
	float lightPos[3] = { 0.0f, 0.0f, 0.0f };
	float lightDir[3] = { 1.0f, 1.0f, 1.0f };
};


#endif // !_LIGHT_H_
