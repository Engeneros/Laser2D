#include <Service.h>
#include <I2Chw.h>



#ifdef LPC2148
#include <LPC2148_I2Chw.h>
#include <LPC2148_I2C_Regs.h>

void I2Chw::IniHW()
{
	switch(num)
	{
		case 0 :
		{
			PCfg(0, 2, 1);//scl0
			PCfg(0, 3, 1);//sda0	
		}
		break;
		case 1 :
		{
			PCfg(0, 11, 3); // scl1
			PCfg (0, 14, 3);	// sda1
		}
		break;
		default:
		{			
		}
		break;
	}	
	*CONCLR =  0x7c;
	*SCLH = 1000;
	*SCLL  = 1000;
	*CONSET = 0x40;
}


#else
#include <LPC2478_I2C_Regs.h>



void I2Chw::IniHW()
{
	switch(num)
	{
		case 0 :
		{
			PCfg(0, 27, 1);//sda0
			PCfg(0, 28, 1);//scl0	
		}
		break;
		case 1 :
			{
				PCfg(0, 0, 3); //PCfg(2, 14, 3);// sda1
				PCfg (0, 1, 3);	//PCfg(2, 15, 3);// scl1
			}
			break;
		case 2:
			{
			PCfg(0, 10, 2);// sda2
			PCfg(0, 11, 2);// scl2
			}
			break;
		default:
			{			
			}
			break;
	}	
	*CONCLR =  0x7c;
	*SCLH = 1000;
	*SCLL  = 1000;
	*CONSET = 0x40;
}

#endif


int I2Chw::Wait()
{
	int i = 1000000;;
	for (;  i > 0 && (*CONSET & 8)  == 0; --i)
	{
	}
	if(i  == 0)
	{
		*CONCLR =  0x7c;
		*SCLH = 1000;
		*SCLL  = 1000;
		*CONSET = 0x40;
	}
	return i;
}
 
unsigned char I2Chw::RawRead(unsigned char* data)
{
	*CONCLR = 0xc; //(*(volatile unsigned long *)(I2C_BASE[ifcNum] + 0x18 )) = 0xc;//I2CxCONCLR
//	while((*CONSET & 8)  == 0)            //I2CxCONSET
//	*data = *DAT;//(*(volatile unsigned long *)(I2C_BASE[ifcNum] + 8 ));//I2CxDAT
	int isOK = Wait();	
	*data = (isOK > 0)? *DAT : *data;
	return  *STAT;//*(volatile unsigned long *)(I2C_BASE[ifcNum] + 4 );//I2CxSTAT	
}

I2Chw::I2Chw(unsigned char ifcNum)
{
	num = ifcNum;
	CONSET  = I2C_CONSET[num];
	STAT = I2C_STAT[num];
	DAT = I2C_DAT[num];
	ADR = I2C_ADR[num];
	SCLH = I2C_SCLH[num];
	SCLL = I2C_SCLL[num];
	CONCLR = I2C_CONCLR[num] ;
	IniHW();
}

unsigned char I2Chw::Start()
{
	*CONSET = 0x20;   //STA = 1, set start flag
		//	while((*CONSET & 8)  == 0)
		//	{		
		//	}
	Wait();
	unsigned char ret = *STAT;		
	*CONCLR = 0x20;
	return ret;
}

unsigned char I2Chw::RawWrite( unsigned char data )
{
	*DAT = data;
	*CONSET = 4;
	*CONCLR = 8;
//	while((*CONSET & 8) == 0)
//	{
//	}
	Wait();
	return  *STAT;		
}

void  I2Chw::StopWrite()
{
	*CONSET = 0x10;
	*CONCLR = 8;
}

void I2Chw::StopRead ()
{	
	*CONSET = 0x10;
	*CONCLR = 0xc;
//	(*(volatile unsigned long *)(I2C_BASE[ifcNum] )) = 0x10;
//	(*(volatile unsigned long *)(I2C_BASE[ifcNum] + 0x18 )) = 0xc;
}

unsigned char I2Chw::ContinuedRead(unsigned char* data)
{
	*CONSET = 4;//*CONCLR = 0xc; //(*(volatile unsigned long *)(I2C_BASE[ifcNum] + 0x18 )) = 0xc;//I2CxCONCLR
	*CONCLR = 8;
//	while((*CONSET & 8)  == 0)            //I2CxCONSET
//	{
//	}
	 int isOK = Wait();
	*data = (isOK > 0)?  *DAT : *data;//(*(volatile unsigned long *)(I2C_BASE[ifcNum] + 8 ));//I2CxDAT
	return  *STAT;//*(volatile unsigned long *)(I2C_BASE[ifcNum] + 4 );//I2CxSTAT	
}

