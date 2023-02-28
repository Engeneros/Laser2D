#ifndef LPC2148DAC_H
#define LPC2148DAC_H
#include <AbstractWordOut.h>

class LPC2128DAC : public AbstractWordOut
{
public:
	LPC2128DAC();
	virtual void Send(unsigned long data);
	virtual ~LPC2128DAC() {}
};
	


#endif
