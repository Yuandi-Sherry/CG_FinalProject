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
private:
	Shader waterShader;
	Mesh* waterMesh;
	glm::vec4 color;
	Wave w1, w2, w3;
	void sendWaves();
	bool firstRender;
	GLfloat firstRenderTime;
};


#endif // !_WATER_SIMULATION_

