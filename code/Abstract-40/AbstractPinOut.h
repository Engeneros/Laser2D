#ifndef ABSTRACT_PINOUT_H
#define ABSTRACT_PINOUT_H
#include <AbstractPinIn.h>

class AbstractPinOut : public AbstractPinIn
{
public:
	virtual bool IsOn() = 0;
	virtual void Clear()= 0 ;
	virtual void  Set() = 0 ;
	virtual void Toggle()	{ (IsOn())? Clear() : Set();}
	virtual void Send(bool state) {(state == false)? Clear() : Set();} 
	virtual  ~AbstractPinOut(){}
protected:
	unsigned long pBit;
	volatile unsigned long* pinReg;
	volatile unsigned long* clrReg;
	volatile unsigned long* setReg;
};

#endif
