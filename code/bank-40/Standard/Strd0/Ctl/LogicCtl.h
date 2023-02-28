#ifndef LOGIC_CTL_H
#define  LOGIC_CTL_H
#include <AbstractPinOut.h>
#include <AbstractController-C.h>

class ShutterCtl : public AbstractPinOut,  AbstractCtl
{
public:
	ShutterCtl( AbstractPinOut* control, AbstractPinIn* detector);
	virtual bool IsOn() ;
	virtual void Clear() ;
	virtual void  Set() ;
	virtual void Toggle();
	virtual void Send(bool state);
	virtual bool Router();	
	virtual ~ShutterCtl(){}
private:
	AbstractPinOut* pCtl;
	AbstractPinIn* pDtc;
	bool isOpen;
	static const int DEAD_TIME = 3;
	int dtCnt;	
};

class PowerCtl :  public AbstractPinOut,  AbstractCtl
{
public:
	PowerCtl ( AbstractPinOut* control, AbstractPinIn* detector, double* current, AbstractPinOut* shutter);
	virtual bool IsOn() ;
	virtual void Clear() ;
	virtual void  Set() ;
	virtual void Toggle();
	virtual void Send(bool state);
	virtual bool Router();	
	virtual ~PowerCtl () {}
private:
	double* ldCur;
	AbstractPinOut* shtr;
	AbstractPinOut* pCtl;
	AbstractPinIn* pDtc;
	bool isPwr;
	bool mustOn;
	bool mustOff;
	static const int DEAD_TIME = 100;
	int dtCnt;	
};

#endif

