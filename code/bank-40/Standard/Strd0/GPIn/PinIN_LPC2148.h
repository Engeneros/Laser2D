#ifndef PIN_IN_LPC2148_H
#define PIN_IN_LPC2148_H
#include <AbstractPinIn.h>
//E:\d2\www\2013Proj\soft\draft\0035Rescuer=28.01.16\code\GPIn\PinIn_LPC2148.h

class PinIn_LPC2148 : public AbstractPinIn
{
public:	
	PinIn_LPC2148(unsigned char portsGroup, unsigned char portNum);	
	virtual bool IsOn ();
	virtual ~PinIn_LPC2148(){}
protected:
	unsigned long pBit;
	volatile unsigned long* pinReg;
};

class PinIn_LPC2148_inv : public PinIn_LPC2148
{
public:	
	PinIn_LPC2148_inv(unsigned char portsGroup, unsigned char portNum);	
	virtual bool IsOn ();
	virtual ~PinIn_LPC2148_inv () {}
};

#endif

