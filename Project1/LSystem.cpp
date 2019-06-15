#include "LSystem.h"
#include <glfw/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
extern double PI;
glm::vec3 xAxis = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 zAxis = glm::vec3(0.0f, 0.0f, 1.0f);
// Transformation trans
LSystem::LSystem() {
	
}

void LSystem::clearAll() {
	grammar.clear();
	trunks.clear();
	leaves.clear();
}

void LSystem::initGrammar(int level) { // load the grammar
	// grammar.clear();
	grammar.setLevel(1);
	grammar.Iteration();
}

void LSystem::grow() { // load the grammar
	// grammar.clear();
	// grammar.setLevel(1);
	grammar.Iteration();
	generateFractal();
}
/*
 * calculate the branches of the tree in advance
 */

void LSystem::generateFractal() { // use the grammar to generate the tree
	//cout << "generate Fractal " << grammar.getRule() << endl;
	// FA[*+FA[*+FA[*+X][-/&X][/%X]B][-/&FA[*+X][-/&X][/%X]B][/%FA[*+X][-/&X][/%X]B]B][-/&FA[*+FA[*+X][-/&X][/%X]B][-/&FA[*+X][-/&X][/%X]B][/%FA[*+X][-/&X][/%X]B]B][/%FA[*+FA[*+X][-/&X][/%X]B][-/&FA[*+X][-/&X][/%X]B][/%FA[*+X][-/&X][/%X]B]B]B
	// init
	trunks.clear();
	leaves.clear();
	curState.pos = glm::vec4(0, 0, 0, 0);
	curState.dir = glm::vec4(0, 1, 0, 0);

	State stack[3000]; // store state
	for (int i = 0; i < 3000; i++)
	{
		stack[i].pos = glm::vec4(0, 0, 0, 0);
		stack[i].dir = glm::vec4(0, 0, 0, 0);
	}
	size_t i = 0;
	// transforming matrix
	glm::mat4 T = glm::mat4(1.0f);
	while (i < grammar.getRule().length()) {
		TrunkPosition tmp_trunk;// a branch
		LeafPosition tmp_leaf;
		switch (grammar.getRule()[i]) {
			case 'F': // add a branch
				tmp_trunk.pos1 = curState.pos; // start point
				curState.pos = curState.pos + (GLfloat)length * curState.dir; 
				tmp_trunk.pos2 = curState.pos;// end point 
				tmp_trunk.radius = radius;
				trunks.push_back(tmp_trunk);
				break;
			case 'X': // add a branch with leaf
				// start points
				tmp_leaf.pos1 = curState.pos;
				tmp_trunk.pos1 = curState.pos;
				curState.pos = curState.pos + (GLfloat)length * curState.dir; 
				// end points
				tmp_trunk.pos2 = curState.pos;
				tmp_leaf.pos1 += (tmp_trunk.pos2 - tmp_trunk.pos1) * (GLfloat)((double)(rand() % 9) / 10);
				tmp_leaf.pos2 = curState.pos;
				// radius
				tmp_trunk.radius = radius;
				tmp_leaf.radius = leafRadius;
				// add to vector
				trunks.push_back(tmp_trunk);
				leaves.push_back(tmp_leaf);
				tmp_leaf.pos2 = curState.pos + (tmp_trunk.pos2 - tmp_trunk.pos1);
				tmp_leaf.pos1 = curState.pos;
				leaves.push_back(tmp_leaf);
				break;
			case 'A':
				// with the growth, both length and radius of the branch decrease
				length = length * lengthFactor;
				radius = radius * radiusFactor;
				break;
			case 'B':
				// backtrack: both length and radius of the branch increase
				length = length / lengthFactor;
				radius = radius / radiusFactor;
				break;
			case '[': // start a new branch 
				stack[stackpointer] = curState;
				stackpointer++;;
				break;
			case ']': // end of the new branch and back to its parent branch
				curState = stack[stackpointer - 1];
				stackpointer--;
				break;
			case '+': // rotate to x
				T = glm::rotate(glm::mat4(1.0f), (float)dx, xAxis);
				curState.dir = T * curState.dir;
				break;
			case '-': 
				T = glm::rotate(glm::mat4(1.0f), (float)-dx, xAxis);
				curState.dir = T * curState.dir;
				break;
			case '*': // rotate to y
				T = glm::rotate(glm::mat4(1.0f), (float)dy, yAxis);
				curState.dir = T * curState.dir;
				break;
			case '/':
				T = glm::rotate(glm::mat4(1.0f), (float)-dy, yAxis);
				curState.dir = T * curState.dir;
				break;
			case '&': // rotate to z
				T = glm::rotate(glm::mat4(1.0f), (float)dz, zAxis);
				curState.dir = T * curState.dir;
				break;
			case '%':
				T = glm::rotate(glm::mat4(1.0f), (float)-dz, zAxis);
				curState.dir = T * (curState.dir);
				break;
			default:
				;
		}
		i++;
	}
	
}

void LSystem::init(Tree tree) {
	stackpointer = 0;
	dx = tree.trunk.leap_x;
	dy = tree.trunk.leap_y;
	dz = tree.trunk.leap_z;
	length = tree.trunk.length;
	lengthFactor = tree.trunk.length_shrink;
	radius = tree.trunk.radius;
	radiusFactor = tree.trunk.radius_shrink;
	leafRadius = tree.leaf.radius;
	curState = {};
}