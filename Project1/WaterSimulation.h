#ifndef _WATER_SIMULATION_
#define _WATER_SIMULATION_
#include "Shader.h"
#include "Mesh.h"
#include "Wave.h"
class WaterSimulation
{
public:
	WaterSimulation();
	~WaterSimulation();
	void init();
	void display();
	void displayGUI();

private:
	Shader waterShader;
	Mesh* waterMesh;
	glm::vec4 color;
	Wave w1, w2, w3;
	void sendWaves();
	bool firstRender;
	GLfloat firstRenderTime;

	// model view control 

	GLfloat translation[3] = { 0.0f, 2.0f, 0.0f };
	GLfloat scale[3] = { 2.0, 0.3, 2.0 };
};


#endif // !_WATER_SIMULATION_

