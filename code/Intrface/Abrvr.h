#ifndef  ABRVR_H
#define ABRVR_H

class Abrvr
{
private:
	const char* txt;
	unsigned int abN;
	signed char len;
	signed  char endPos;
public:	
	Abrvr (const char* str, unsigned int num) ;
	bool operator == (const char* str);	
	bool IsEqual (const char* str);
	bool operator != (const char* str);	
	unsigned  char Compare (const char* str, unsigned char strL);
	unsigned int GetNum () {return abN;}
	unsigned char GetLen () {return len;}
	~Abrvr(){}
};

#endif
