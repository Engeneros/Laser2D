#ifndef   ABSTRACT_FP_PARSER_H
#define  ABSTRACT_FP_PARSER_H
//E:\d2\www\2013Proj\soft\Abstract\AbstractFPParser.h
struct FunAddrDat
{
	unsigned int func;
	unsigned int addr;
	int data;
};

class AbstractFPParser
{
public:
	virtual bool Translate(const char* strIn, unsigned int inputLen, FunAddrDat* fAddrD, char mode) = 0;
	virtual ~AbstractFPParser() {}
};

class AbstractFPModul
{
public:
	virtual bool Router (unsigned int fNum, int data) = 0;// );//,  Instruction* fAndAddr, char*strOut, unsigned int outputLen) = 0;
	virtual ~AbstractFPModul() {}
};

#endif

