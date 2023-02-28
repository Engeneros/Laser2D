#ifndef I2C_OUT_H
#define I2C_OUT_H
#include <AbstractMemoryOut.h>
#include <I2ChwLPC3250.h>

//class AT24C04out : public AbstractMemoryOut
//{
//public:
//	AT24C04out(I2Chw* hwIfc, unsigned char devAddr);
//	virtual bool Write( unsigned  int addr, char data)  ;
//	virtual bool Write (unsigned int addr, const char* data, unsigned int sz)  ;
//	virtual bool Write (char data) ;
//	virtual bool Write (const char* data, unsigned int sz);
//	virtual ~AT24C04out() {}
//private:
//	unsigned char dAdr;
//	virtual bool BlockWrite (unsigned int addr, const char* data, unsigned int sz)  ;
//	I2Chw* i2hw;
//};

class  I2cOut : public AbstractMemoryOut
{
public:
	I2cOut( I2Chw* hwIfc );//, unsigned char devAddr);
	virtual bool Write( unsigned  int addr, char data)  ;
	virtual bool Write (unsigned int addr, const char* data, unsigned int sz)  ;
	virtual bool Write (char data) ;
	virtual bool Write (const char* data, unsigned int sz);
	virtual ~I2cOut() {}
private:
	I2Chw* i2hw;
};
	




#endif

