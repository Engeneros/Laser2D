#ifndef I2C_HW_H
#define I2C_HW_H

class I2Chw
{
public:
	I2Chw(unsigned char ifcNum);
	unsigned char Start();
	unsigned char RawWrite(unsigned char data);
	unsigned char RawRead (unsigned char* data);
	unsigned char ContinuedRead(unsigned char* data);
	void StopWrite();
	void StopRead();
	
	void ClearInterruptBit () {*CONCLR = 1 << 3;}
	virtual ~I2Chw() {}
private:
	int Wait();
	unsigned char num;
	unsigned char dAdr;
#ifdef LPC2148
	volatile unsigned char*   CONSET;
	volatile unsigned char*   STAT;
	volatile unsigned char*   DAT;
	volatile unsigned char*   ADR;
	volatile unsigned short*   SCLH;
	volatile unsigned short*   SCLL;
	volatile unsigned char*   CONCLR;
#else
	volatile unsigned long*   CONSET;
	volatile unsigned long*   STAT;
	volatile unsigned long*   DAT;
	volatile unsigned long*   ADR;
	volatile unsigned long*   SCLH;
	volatile unsigned long*   SCLL;
	volatile unsigned long*   CONCLR;
#endif
	void IniHW ();
};


#endif

