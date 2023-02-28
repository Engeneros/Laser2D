#include <AbstractConvertor.h>
#include <string.h>
#include <stdio.h>

void AbstractConvertor::GetValueString (unsigned int dataIn, char* buf  )
{
	sprintf ( buf, "%.*f", tlc, GetValue(dataIn));
}

void AbstractConvertor::GetValueStringAndUnits( unsigned int dataIn, char* buf )
{
	sprintf (buf, "%.*f %s", tlc, GetValue(dataIn), unt);
}

void AbstractConvertor::SetUnits ( const char* units)
{ 
	if(unt != 0)
		delete [] unt;
	unsigned int len = strlen (units);
	unt = new char [++len];
	for(int i = len; i > 0 ;)
		unt [i] = units[--i];
}
	



