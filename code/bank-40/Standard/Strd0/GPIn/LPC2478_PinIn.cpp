#include <PinIn.h>
#include <Service.h>
#include  <LPC2478_GPIO_Regs.h>

PinIn::PinIn (unsigned char portsGroup, unsigned char portNum)
{
	PCfg(portsGroup, portNum, 0);
	pBit = 1 << portNum;
	pinReg = GPIO_PIN_REG[portsGroup];
	*GPIO_DIR_REG[portsGroup] &= ~pBit;
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

