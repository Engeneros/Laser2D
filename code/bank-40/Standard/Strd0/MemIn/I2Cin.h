#ifndef I2C_IN_H
#define I2C_IN_H
#include <AbstractMemoryIn.h>
#include <I2Chw.h>
//E:\d2\www\2013Proj\soft\bank\Standard\Strd0\MemIn\I2Cin.h

class  AT24C04in : public AbstractMemoryIn
{
public:
	AT24C04in ( I2Chw* hwIfc, unsigned char devAddr);
	virtual bool Read( unsigned  int addr, char* data) ;
	virtual bool Read (unsigned int addr, char* data, unsigned int sz) ;
	virtual bool Read (char* data) ;
	virtual bool Read (char* data, unsigned int sz) ;
	virtual ~AT24C04in() {}
private:
	unsigned char dAdr;
	I2Chw* i2hw;
	volatile unsigned long*   CONSET;
	volatile unsigned long*   STAT;
	volatile unsigned long*   DAT;
	volatile unsigned long*   ADR;
	volatile unsigned long*   SCLH;
	volatile unsigned long*   SCLL;
	volatile unsigned long*   CONCLR;
};

class  AT24C256in : public AbstractMemoryIn
{
public:
	AT24C256in ( I2Chw* hwIfc, unsigned char devAddr);
	virtual bool Read( unsigned  int addr, char* data) ;
	virtual bool Read (unsigned int addr, char* data, unsigned int sz) ;
	virtual bool Read (char* data) ;
	virtual bool Read (char* data, unsigned int sz) ;
	virtual ~AT24C256in() {}
private:
	unsigned char dAdr;
	I2Chw* i2hw;
	volatile unsigned long*   CONSET;
	volatile unsigned long*   STAT;
	volatile unsigned long*   DAT;
	volatile unsigned long*   ADR;
	volatile unsigned long*   SCLH;
	volatile unsigned long*   SCLL;
	volatile unsigned long*   CONCLR;
};

#endif
