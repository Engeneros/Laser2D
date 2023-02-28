#ifndef I2C_HW_H
#define I2C_HW_H

class I2Chw
{
public:
	I2Chw(unsigned char ifcNum, unsigned char devAddr);
	bool SendByte(unsigned  char addr, char data);
	bool SendBuf ( unsigned  char addr, const char* data, unsigned char sz );
	bool ReadByte( unsigned  char addr, char* data);
	bool ReadBuf (unsigned  char addr, char* data,  unsigned char sz);
//	unsigned char Start();
//	unsigned char RawWrite(unsigned char data);
//	unsigned char RawRead (unsigned char* data);
//	unsigned char ContinuedRead(unsigned char* data);
//	void StopWrite();
//	void StopRead();
	
//	void ClearInterruptBit () {*CONCLR = 1 << 3;}
	virtual ~I2Chw() {}
private:
	unsigned char num;
	unsigned short dAdrWr;
	unsigned short dAdrRd;
	bool SendFIFO ( const char* data, unsigned char sz );

	volatile unsigned long* RX_FIFO;
	volatile unsigned long* TX_FIFO;
	volatile unsigned long* TX_LEV;
	volatile unsigned long* RX_LEV;


//	volatile unsigned long*   CONSET;
//	volatile unsigned long*   STAT;
//	volatile unsigned long*   DAT;
//	volatile unsigned long*   ADR;
//	volatile unsigned long*   SCLH;
//	volatile unsigned long*   SCLL;
//	volatile unsigned long*   CONCLR;
	void IniHW ();
};


#endif

