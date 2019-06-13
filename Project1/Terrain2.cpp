#include "Terrain2.h"
#include "utils.h"
#include <glm/glm.hpp>
Terrain2::Terrain2()
{
}

Terrain2::~Terrain2()
{
}

void Terrain2::init() {
	heightMapTexture = utils::loadTexture((GLchar*)"./textures/height.jfif");

}

void Terrain2::display() {
	heightMapTexture = utils::loadTexture((GLchar*)"./textures/height.jfif");

}
void Terrain2::loadTerrain(const string &filename, const string &texName) {

}