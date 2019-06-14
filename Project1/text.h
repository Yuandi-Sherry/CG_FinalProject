#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <stdlib.h>
using namespace std;
#ifndef _TEXT_
#define _TEXT_

class Text
{
public:
	Text();
	~Text();
	void init();
	void display(const char* str);
	void selectFont(int size, int charset, const char* face);
	void drawString(const char* str);
	
	const int MAX_CHAR = 128;
};


#endif // !_TEXT_
