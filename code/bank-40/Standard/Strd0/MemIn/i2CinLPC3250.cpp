#include <I2CInLPC3250.h>

bool I2cin::Read( unsigned  int addr, char* data)
{
	i2hw->ReadByte( addr, data);
	return true;
}

bool I2cin::Read (unsigned int addr, char* data, unsigned int sz)
{
	return true;
}

bool I2cin::Read (char* data)
{
	return true;
}

bool I2cin::Read (char* data, unsigned int sz)
{
	return true;
}


//AT24C04in::AT24C04in(I2Chw* hwIfc, unsigned char devAddr)
//{
//	i2hw = hwIfc;
//	dAdr = devAddr << 1;
//}

//bool AT24C04in::Read ( unsigned  int addr, char* data )
//{
//	unsigned char status = i2hw->Start(); 
//	if(status == 8)
//	{
////		GetOKLed2()->Toggle();
//		status = i2hw->RawWrite(dAdr  | ( addr >> 7 & 2));// RawWrite (ifcNum, dev << 1);
//		if(status == 0x18)
//		{
////			GetOKLed1()->Set();
//			status = i2hw->RawWrite((unsigned char) ( addr & 0xff) ); // I2cRawWrite (ifcNum, addr);
//			if(status == 0x28)
//			{
////				GetOKLed2()->Set();
//				i2hw->ClearInterruptBit();// (*(volatile unsigned long *)(I2C_BASE[ifcNum] + 0x18 )) = 8;	
//				status = i2hw->Start();// I2cStart(ifcNum);	
//				if(status == 0x10)
//				{
////					GetOKLed3()->Set();
//					status = i2hw->RawWrite ( dAdr | ( addr >> 7 & 2) | 1  ); // I2cRawWrite (ifcNum, (dev << 1) | 1);
//					if(status == 0x40)
//					{
////						GetOKLed2()->Clear();
//						 status = i2hw->RawRead( ( unsigned char*) data); // I2cRawRead (data);
//					}
//				}
//			}	
//		}
//	}
//	else 
//		status  = 0;
//	i2hw->StopRead();
//	bool ret;
//	if(status == 0x58)
//	{
//		ret = true;
//		currAdr = addr;
//	}
//	else
//		ret = false;
//	return ret;
//}

//bool AT24C04in::Read (unsigned int addr, char* data, unsigned int sz) 
//{
//	unsigned char status = i2hw->Start(); 
//	if(status == 8)
//	{
////		GetOKLed2()->Toggle();
//		 status = i2hw->RawWrite(dAdr  | ( addr >> 7 & 2));// RawWrite (ifcNum, dev << 1);
//		if(status == 0x18)
//		{
//			status = i2hw->RawWrite((unsigned char) ( addr & 0xff) ); // I2cRawWrite (ifcNum, addr);
//			if(status == 0x28)
//			{
//				i2hw->ClearInterruptBit();// (*(volatile unsigned long *)(I2C_BASE[ifcNum] + 0x18 )) = 8;	
//				status = i2hw->Start();// I2cStart(ifcNum);	
//				if(status == 0x10)
//				{
//					status = i2hw->RawWrite ( dAdr | ( addr >> 7 & 2) | 1  ); // I2cRawWrite (ifcNum, (dev << 1) | 1);
//					unsigned short incr= 0;
//					bool ok =  (status == 0x40)?  true : false;
//					while (ok  && sz > 0 )
//					{
////						GetOKLed2()->Clear();						;
//						if(--sz > 0)
//						{
//							status = i2hw->ContinuedRead((unsigned char*) &data[incr++]);// &byte);
//							ok = (status == 0x50)? true : false;
//						}
//						else
//						{
//							status = i2hw->RawRead((unsigned char*) &data[incr++]);//  &byte);
//							ok = (status == 0x58)? true: false;
//						}
//						//data[incr++] = byte;
//					}
//					if(ok && incr > 0)
//						currAdr = addr + incr;				
//					else if( incr > 1)
//						currAdr = addr + incr -  1;
//				}
//			}	
//		}
//	}
//	else 
//		status  = 0;
//	i2hw->StopRead();
//	return (status == 0x58)? true : false;
//}

//bool AT24C04in::Read (char* data) 
//{
//	return false;
//}

//bool AT24C04in::Read (char* data, unsigned int sz) 
//{
//	return false;
//}
//	


