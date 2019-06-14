#ifndef _L_SYSTEM_
#include <glfw/glfw3.h>
#include "Grammar.h"
#include "Tree.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class State {
public:
	glm::vec4 pos;
	glm::vec4 dir;// branch direction
	State() {}
};
class TrunkPosition {
public:
	glm::vec4 pos1; // start point 
	glm::vec4 pos2; // end point
	double radius;
	TrunkPosition() {}
};
class LeafPosition {
public:
	glm::vec4 pos1; // start point 
	glm::vec4 pos2; // end point
	double radius; // size
	LeafPosition() {}
};
class LSystem
{
public:
	int stackpointer;
	double dx, dy, dz;    // rotating angle
	double length;     // init stripe
	double lengthFactor; // increasing factor 
	double radius;   // init radius
	double radiusFactor;  // increasing factor
	State curState;  // cur Pos & cur Rotation
	double leafRadius; 
	Grammar grammar;    // analyzer

	vector<TrunkPosition> trunks; // current branch
	vector<LeafPosition> leaves; // leaves on current branch
	LSystem();
	void init(Tree tree);
	void clearAll();
	void initGrammar(int level);
	void generateFractal();
};
#endif // !_L_SYSTEM_