#ifndef   ABSTRACT_PARSER_H
#define  ABSTRACT_PARSER_H

struct Instruction
{
	unsigned int func;
	unsigned int addr;
};

class AbstractParser
{
public:
	virtual bool Translate(const char* strIn, unsigned int inputLen, Instruction* fAndAddr,  unsigned int* dataPos) = 0;
	virtual ~AbstractParser() {}
};

class AbstractModul
{
public:
	virtual bool Router (const char* strIn, unsigned int inputLen, unsigned int fNum, char** strOut, unsigned int* outputLen) = 0;// );//,  Instruction* fAndAddr, char*strOut, unsigned int outputLen) = 0;
	virtual ~AbstractModul() {}
};

#include <string.h>
struct abrv
{
	unsigned char len;
	const char* txt;
	unsigned int smnt;
	abrv(const char* str, unsigned int sens) { txt= str; len = strlen(txt); smnt = sens;}
};


#endif

