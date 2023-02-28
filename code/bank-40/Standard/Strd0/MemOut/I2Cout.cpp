#include <lpc2478_I2C_Regs.h>
#include <I2Cout.h>
#include <BoardDevices.h>
//E:\d2\www\2013Proj\soft\draft\0040binaryRack=17.10.2016\sw\puC\puC40_0\code\bank-40\Standard\Strd0\MemOut\I2Cout.cpp

AT24C04out::AT24C04out(I2Chw* hwIfc, unsigned char devAddr)
{
	i2hw = hwIfc;
	dAdr = devAddr << 1 ;
}
bool AT24C04out::Write( unsigned  int addr, char data)
{
	unsigned char status = i2hw->Start();	
	if(status == 8)
	{
		status = i2hw->RawWrite (dAdr  |  ( addr >> 7 & 2) );
		if(status == 0x18)
		{
			status = i2hw->RawWrite((unsigned char)  (addr & 0xff) );
			if(status == 0x28)
			{
				status = i2hw->RawWrite((unsigned char) data);// I2cRawWrite (ifcNum, data);
				currAdr = (status == 0x28) ? currAdr : addr;
			}
		}
	}
	i2hw->StopWrite(); // I2cStopWr (ifcNum);
	return (status == 0x28)? true : false; 
}

bool AT24C04out::BlockWrite(unsigned int addr, const char* data, unsigned int sz)
{
	unsigned char status = i2hw->Start();	
	if(status == 8)
	{
		status = i2hw->RawWrite (dAdr  |  ( addr >> 7 & 2) );
		if(status == 0x18)
		{
			status = i2hw->RawWrite((unsigned char)  (addr & 0xff) );
//			if(status == 0x28)
				unsigned char incr = 0;
				bool ok = (status == 0x28)?  true :false;
				while( sz-- > 0 &&  ok)
				{
					status = i2hw->RawWrite((unsigned char) data[incr++]);// I2cRawWrite (ifcNum, data);
					ok = (status ==0x28)?  true : false;
				}
				if(ok && incr > 0) 
					currAdr = addr + incr - 1;				
				else if( incr > 1)
					currAdr = addr + incr -  2;
		}
	}
	i2hw->StopWrite(); // I2cStopWr (ifcNum);
	return (status == 0x28)? true : false; 	
}


bool AT24C04out::PageFastWrite (unsigned int addr, const char* data, unsigned int sz)
{
	//	size < 16
	return  BlockWrite (addr, data, sz);
}

bool AT24C04out::Write (unsigned int addr, const char* data, unsigned int sz)
{
	unsigned short szCurr  = ( addr + 16  &  0x3f0 )  -  addr; 
	szCurr = (szCurr > sz) ? sz : szCurr;
	unsigned short szRem = sz - szCurr;
	bool isOk = BlockWrite(addr, data, szCurr);
	unsigned  short currAddr = addr + szCurr & 0x1ff;
	unsigned short dataPtr = szCurr;
	while(isOk == true &&  szRem > 0)
	{
		DelayMs(5);
		szCurr = ( szRem >= 16 )? 16 : szRem;
		isOk = BlockWrite( currAddr,  data + dataPtr, szCurr);
		dataPtr +=szCurr;
		currAddr += szCurr;
		currAddr &=0x1ff;
		szRem -= szCurr;
	}
	DelayMs(5);
	return isOk;
}

bool AT24C04out::Write (char data)
{
	return true;
}

bool AT24C04out::Write (const char* data, unsigned int sz) 
{
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////
AT24C256out::AT24C256out(I2Chw* hwIfc, unsigned char devAddr)
{
	i2hw = hwIfc;
	dAdr = devAddr << 1 ;
}
bool AT24C256out::Write( unsigned  int addr, char data)
{
	unsigned char status = i2hw->Start();	
	if(status == 8)
	{
		status = i2hw->RawWrite (dAdr);
		if(status == 0x18)
		{	
			status = i2hw->RawWrite((unsigned char)  (addr >> 8) );
			if(status == 0x28)
			{			
				status = i2hw->RawWrite((unsigned char)  (addr & 0xff) );
				if(status == 0x28)
				{
					status = i2hw->RawWrite((unsigned char) data);// I2cRawWrite (ifcNum, data);
					currAdr = (status == 0x28) ? currAdr : addr;
				}
			}
		}
	}
	i2hw->StopWrite(); // I2cStopWr (ifcNum);
	return (status == 0x28)? true : false; 
}

bool AT24C256out::BlockWrite(unsigned int addr, const char* data, unsigned int sz)
{
	unsigned char status = i2hw->Start();	
	if(status == 8)
	{
//		GetOKLed1()->Toggle();
		status = i2hw->RawWrite (dAdr );
		if(status == 0x18)
		{
//			GetOKLed2()->Toggle();
			status = i2hw->RawWrite((unsigned char)  (addr >> 8) );
//			if(status == 0x28)
			if(status == 0x28)
			{			
					status = i2hw->RawWrite((unsigned char)  (addr & 0xff) );										
					unsigned char incr = 0;
					bool ok = (status == 0x28)?  true :false;
					while( sz-- > 0 &&  ok)
					{
						status = i2hw->RawWrite((unsigned char) data[incr++]);// I2cRawWrite (ifcNum, data);
						ok = (status ==0x28)?  true : false;
					}
					if(ok && incr > 0) 
						currAdr = addr + incr - 1;				
					else if( incr > 1)
						currAdr = addr + incr -  2;
				}
		}
	}
	i2hw->StopWrite(); // I2cStopWr (ifcNum);
	return (status == 0x28)? true : false; 	
}

bool AT24C256out::Write (unsigned int addr, const char* data, unsigned int sz)
{
	unsigned short szCurr  = ( addr + 64  &  0xffc0 )  -  addr; 
	szCurr = (szCurr > sz) ? sz : szCurr;
	unsigned short szRem = sz - szCurr;
	bool isOk = BlockWrite(addr, data, szCurr);
	unsigned  short currAddr = addr + szCurr & 0x7fff;
	unsigned short dataPtr = szCurr;
	while(isOk == true &&  szRem > 0)
	{
		DelayMs(5);
		szCurr = ( szRem >= 64 )? 64 : szRem;
		isOk = BlockWrite( currAddr,  data + dataPtr, szCurr);
		dataPtr +=szCurr;
		currAddr += szCurr;
		currAddr &=0x7fff;
		szRem -= szCurr;
	}
	DelayMs(5);
	return isOk;
}

bool AT24C256out::PageFastWrite (unsigned int addr, const char* data, unsigned int sz)
{
//	size < 64 
	return  BlockWrite (addr, data, sz);
}


bool AT24C256out::Write (char data)
{
	return Write (currAdr, data);
}

bool AT24C256out::Write (const char* data, unsigned int sz) 
{
	return  Write (currAdr, data, sz);
}



