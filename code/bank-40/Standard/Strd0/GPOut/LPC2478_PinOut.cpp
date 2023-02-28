#include <PinOut.h>
#include <Service.h>
#include  <LPC2478_GPIO_Regs.h>

PinOut::PinOut(unsigned char portsGroup, unsigned char portNum)
{
	PCfg(portsGroup, portNum, 0);
	pBit = 1 << portNum;
	pinReg = GPIO_PIN_REG[portsGroup];
	setReg = GPIO_SET_REG[portsGroup];
	clrReg = GPIO_CLR_REG[portsGroup];
	*GPIO_DIR_REG[portsGroup] |= pBit;
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

//void PinOut_LPC2148::Toggle() 
//{
//	*pinReg ^= pBit;
//}	

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

