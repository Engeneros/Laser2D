#ifndef  ABCTRACT_DAC
#define ABCTRACT_DAC
//E:\d2\www\2013Proj\soft\draft\0040binaryRack=17.10.2016\sw\puC\puC40_0\code\Abstract-40\AbstractDAC.h
class AbstractDAC
{
public:	
	virtual void FirstWrite(unsigned int data) = 0;
	virtual void Write(unsigned int data) = 0;
	virtual void Release() = 0;
	virtual ~AbstractDAC(){}
};

#endif
