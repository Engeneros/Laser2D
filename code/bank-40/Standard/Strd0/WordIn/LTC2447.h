#ifndef  LTC2478_H
#define LTC2478_H
#include  <AbstractADC.h>
#include  <AbstractpinOut.h>
#include <AbstractSpi.h>

class Ltc2447 : public AbstractADC
{
public:
	Ltc2447 (AbstractPinOut* chipSel,  AbstractSpi* interface, unsigned char chan, bool inpDif = true, bool refDif = true)  ;
	virtual void Start();
	virtual void Stop();
	virtual AbstractADC& operator ++ ();
	virtual void Accumulate ( );
	virtual ~Ltc2447(){}
private:
	AbstractPinOut* cSel;
	AbstractSpi* hwIfc;
	unsigned short mswMosi;
	
};
#endif
