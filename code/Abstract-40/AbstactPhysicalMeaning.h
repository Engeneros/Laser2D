#ifndef ABSTRACT_PHYSICAL_MEANING_H
#define ABSTRACT_PHYSICAL_MEANING_H
#include <string.h>

class AbstractPhysicalMeaning
{
protected:
	unsigned char  tlc;
	char* unt;

public:	
	AbstractPhysicalMeaning() { unt = 0;}
	void SetUnits ( const char* units) 
	{ 
		if(unt != 0)
			delete [] unt;
		unsigned int len = strlen (units);
		unt = new char [++len];
		for(int i = len; i > 0 ;)
			unt [i] = units[--i];
	}
	void SetTolerance ( unsigned char tolerance) { tlc = tolerance;}
	char* GetValue
	
};

#endif