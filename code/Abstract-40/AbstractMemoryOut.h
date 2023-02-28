#ifndef ABSTRACT_MEMORY_OUT_H
#define ABSTRACT_MEMORY_OUT_H

class AbstractMemoryOut
{	
protected:
	unsigned int currAdr;	
public:
	virtual bool Write( unsigned  int addr, char data) = 0;
	virtual bool Write (unsigned int addr, const char* data, unsigned int sz) = 0;
	virtual bool PageFastWrite (unsigned int addr, const char* data, unsigned int sz) = 0;
	virtual bool Write (char data) = 0;
	virtual bool Write (const char* data, unsigned int sz) = 0;
	virtual unsigned int GetCurrentAddr() {return currAdr;}
	virtual void SetCurrentAddr(unsigned int addr) { currAdr = addr;}
	virtual ~AbstractMemoryOut() {}
};


#endif
