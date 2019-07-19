#ifndef  _GRAMMAR_H_
#define _GRAMMAR_H_
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Grammar
{
private:
	string Gname; 
	int level = 5; 
	string grammar = "FA[*+X][-/&X][/%X]B";
	string rule;
public:
	Grammar() {}
	void clear();
	void Iteration();

	void setGrammarName(const string& ref);
	void setLevel(int num);
	string getGrammarName();
	int getLevel();
	string getRule();
};
#endif // ! _GRAMMAR_H_

