#ifndef I2C_IN_H
#define I2C_IN_H
#include <AbstractMemoryIn.h>
#include <I2ChwLPC3250.h>
//E:\d2\www\2013Proj\soft\bank\Standard\Strd0\MemIn\I2Cin.h

class  I2cin : public AbstractMemoryIn
{
private:
	I2Chw* i2hw;	
public:
	I2cin ( I2Chw* hwIfc) {i2hw = hwIfc;}
	virtual bool Read( unsigned  int addr, char* data) ;
	virtual bool Read (unsigned int addr, char* data, unsigned int sz) ;
	virtual bool Read (char* data) ;
	virtual bool Read (char* data, unsigned int sz) ;
	virtual ~I2cin() {}
};
#endif
