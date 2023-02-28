#include <PinOut.h>
#include <LPC214x.h>
//E:\d2\www\2013Proj\soft\draft\0035Rescuer=28.01.16\code\GPOut\PinOut.cpp
//E:\d2\www\2013Proj\soft\bank\Standard\Strd0\GPOut\PinOut_LPC2148.cpp

PinOut::PinOut(unsigned char portsGroup, unsigned char portNum)
{
	pBit = 1 << portNum;
	if (portsGroup == 1)
	{
		PINSEL2 = 0;
		pinReg = &IOPIN1; //&FIO1PIN;
		clrReg = &IOCLR1; // &IOCLR1;
		setReg = &IOSET1;// &IOSET1;
		IODIR1 |= pBit;
		//FIO1DIR |= pBit;
	}
	else 
	{
		if(portNum < 16)
			PINSEL0 &= ~(3 <<(portNum * 2 ));
		else 
			PINSEL1 &= ~(3 << ((portNum - 16) * 2));
		pinReg = &IOPIN0;// &FIO0PIN;	//
		clrReg = &IOCLR0;//&FIO0CLR;	// &FIO0CLR;
		setReg = &IOSET0;///&FIO0SET;	///&FIO0SET;
		IODIR0 |= pBit; 
		//FIO0DIR |= pBit;
	}
}


bool PinOut::IsOn()
{
	return ( (*pinReg & pBit) == 0)? false : true;
}

void PinOut::Set()
{
	*setReg = pBit;
}

void PinOut::Clear()
{
	*clrReg = pBit;
}

void PinOut::Toggle() 
{
	*pinReg ^= pBit;
}	

//////////////////////////////////

PinOut_inv::PinOut_inv(unsigned char portsGroup, unsigned char portNum) : PinOut(portsGroup, portNum)
{
}

bool PinOut_inv::IsOn()
{
	return ( (*pinReg & pBit) == 0)? true : false ;
}

void PinOut_inv::Set()
{
		*clrReg = pBit;
}

void PinOut_inv::Clear()
{
	*setReg = pBit;
}

//void PinOut_inv::Toggle()
//{
//	*pinReg ^= pBit;
//}	
