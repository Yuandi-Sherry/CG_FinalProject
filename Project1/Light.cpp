#include "Light.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
Light::Light()
{
}



Light::~Light()
{
}


void Light::displayGUI() {
	ImGui::SliderFloat3("light color", lightColor, 0, 1);
	ImGui::SliderFloat3("light pos", lightPos, 0, 100);
	ImGui::SliderFloat3("light direction", lightDir, 0, 1);
}