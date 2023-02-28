#include <lpc3250_I2C_Regs.h>
#include <i2CoutLPC3250.h>
//#include <BoardDevices.h>
#include <sleep.h>

I2cOut::I2cOut(I2Chw* hwIfc)//, unsigned char devAddr)
{
	i2hw = hwIfc;
}
bool I2cOut::Write( unsigned  int addr, char data)
{
	return i2hw->SendByte ( addr, data );
}

bool I2cOut::Write (unsigned int addr, const char* data, unsigned int sz)
{
	return i2hw->SendBuf ( addr, data, sz );
}

bool I2cOut::Write (char data)
{
	return true;
}

bool I2cOut::Write (const char* data, unsigned int sz) 
{
	return true;
}


