#ifndef PINOUT_H
#define PINOUT_H
#include <AbstractPinOut.h>

class PinOut : public AbstractPinOut
{
public:
	PinOut(unsigned char portsGroup, unsigned char portNum);
	virtual bool IsOn();
	virtual void Clear() ;
	virtual void  Set() ;
	virtual void Toggle() ;//				{ (IsOn())? Clear() : Set();}
	virtual  ~PinOut(){}
protected:
	unsigned long pBit;
	volatile unsigned long* pinReg;
	volatile unsigned long* clrReg;
	volatile unsigned long* setReg;
};

class PinOut_inv : public PinOut
{
public:
	PinOut_inv(unsigned char portsGroup, unsigned char portNum);
	virtual bool IsOn();
	virtual void Clear() ;
	virtual void  Set() ;
//	virtual void Toggle() ;
	virtual  ~PinOut_inv(){}
};
#endif
