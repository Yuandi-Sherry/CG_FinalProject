// Grammar.cpp
#include "grammar.h"
/**
 * clear grammar string
 */
void Grammar::clear()
{
	grammar.clear();
}

/**
 * clear grammar string
 */
void Grammar::Iteration() {
	string temprule = grammar;
	for (int i = 1; i <= level; i++) {
		// for each level
		int curlen = temprule.length();
		int j = 0;
		while (j < curlen) {
			if (temprule[j] == 'X')// root
			{
				double x = rand() % 100; ;
				if (x > 50) {
					rule += grammar; // add a new branch 
				}
				j++;
			}
			else // rotate
			{
				rule += temprule[j]; // continue reading the grammar
				j++;
			}
		}
		temprule = rule;
		rule.clear();
	}
	rule = temprule;
}
void Grammar::setGrammarName(const string& ref)
{
	Gname = ref;
}
void Grammar::setLevel(int num)
{
	level = num;
}
string Grammar::getGrammarName()
{
	return Gname;
}
int Grammar::getLevel()
{
	return level;
}
string Grammar::getRule()
{
	return rule;
}