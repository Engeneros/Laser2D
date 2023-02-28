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
	virtual bool Translate(char* strIn, unsigned int inputLen, Instruction* fAndAddr,  unsigned int* dataPos) = 0;
	virtual ~AbstractParser() {}
};

class AbstractModul
{
public:
	virtual bool Router (char* strIn, unsigned int inputLen, unsigned int fNum) = 0;// );//,  Instruction* fAndAddr, char*strOut, unsigned int outputLen) = 0;
	virtual ~AbstractModul() {}
};

//class AbstractCmdRouter
//{
//public:
//	virtual bool Router (const char* str, unsigned char leght) = 0;
//	virtual ~AbstractCmdRouter() {}
//};

//class AbstractParser
//{
//public:
//	virtual AbstractParser* Translate(const char* strIn, unsigned char  inputLen, unsigned char inCmd, const char* outStr, unsigned char outputLen) = 0;
//	virtual ~AbstractParser() {}
//};

#endif

