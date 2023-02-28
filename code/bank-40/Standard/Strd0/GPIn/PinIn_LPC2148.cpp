#include <PinIn.h>
#include <LPC214x.h>
//E:\d2\www\2013Proj\soft\draft\0035Rescuer=28.01.16\code\GPIn\PinIn.cpp

PinIn::PinIn (unsigned char portsGroup, unsigned char portNum)
{
	pBit = 1 << portNum;
	if (portsGroup == 1)
	{
		PINSEL2 = 0;
		pinReg = &IOPIN1;// &FIO1PIN;
		IODIR1 &= ~pBit;
	}
	else 
	{
		if(portNum < 16)
			PINSEL0 &= ~(3 << portNum * 2 );
		else 
			PINSEL1 &= ~(3 << (portNum - 16) * 2);
		pinReg = &IOPIN0;// &FIO0PIN;	
		IODIR0 &= ~pBit; 
	}
}

bool PinIn::IsOn()
{
	return ( (*pinReg & pBit) == 0)? false : true;
}

PinIn_inv::PinIn_inv(unsigned char portsGroup, unsigned char portNum) : PinIn( portsGroup, portNum)
{
}

bool PinIn_inv::IsOn()
{
	return ( (*pinReg & pBit) == 0)?  true : false ;
}

