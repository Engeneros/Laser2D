#ifndef AD5662_h
#define ad5662_h
#include <AbstractDAC.h>
#include <AbstractPinOut.h>
#include <AbstractSPI.h>

class AD5662 : public AbstractDAC
{
public:	
	AD5662 (AbstractPinOut* chipSel,  AbstractSpi* interface) : csPin (chipSel), hwIfc(interface) {csPin->Set();}
	virtual void FirstWrite(unsigned int data);
	virtual void Write (unsigned int data );
	virtual void Release() { csPin->Set();}
	virtual ~AD5662(){}
private:
	AbstractPinOut* csPin;
	AbstractSpi* hwIfc;
};
#endif
