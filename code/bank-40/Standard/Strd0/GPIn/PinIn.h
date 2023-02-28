#ifndef PIN_IN_H
#define PIN__H

#include <AbstractPinIn.h>

class PinIn : public AbstractPinIn
{
public:	
	PinIn (unsigned char portsGroup, unsigned char portNum);	
	virtual bool IsOn ();
	virtual ~PinIn(){}
protected:
	unsigned long pBit;
	volatile unsigned long* pinReg;
};

class PinIn_inv : public PinIn
{
public:	
	PinIn_inv(unsigned char portsGroup, unsigned char portNum);	
	virtual bool IsOn ();
	virtual ~PinIn_inv () {}
};

#endif

