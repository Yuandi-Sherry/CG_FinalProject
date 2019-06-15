#include "text.h"

Text::Text()
{
}

Text::~Text()
{
	
}

void Text::init(int windowWidth, int windowHeight) {
	//glewInit();
	gladLoadGL();

	if (!oglText.init("Candy Script_48", windowWidth, windowHeight))
		if (!oglText.init("./fonts/Candy Script_48", windowWidth, windowHeight))
			exit(1);
}

void Text::display(const char* str) {	

	oglText.beginString();

	oglText.drawString(10, 800, str, 1, 0xFFFFFF70);

	oglText.endString();
}