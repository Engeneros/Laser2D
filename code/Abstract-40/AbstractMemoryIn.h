#ifndef ABSTRACT_MEMORY_IN_H
#define ABSTRACT_MEMORY_IN_H

class AbstractMemoryIn
{
protected:
	unsigned int currAdr;	
public:
	virtual bool Read( unsigned  int addr, char* data) = 0;
	virtual bool Read (unsigned int addr, char* data, unsigned int sz) = 0;
	virtual bool Read (char* data) = 0;
	virtual bool Read (char* data, unsigned int sz) = 0;
	virtual unsigned int GetCurrentAddr() { return currAdr; }
	virtual void SetCurrentAddr ( unsigned int addr ) { currAdr = addr;}
	virtual ~AbstractMemoryIn() {}
};

#endif


