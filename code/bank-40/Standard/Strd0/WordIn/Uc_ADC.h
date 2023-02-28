#ifndef UC_ADC_H
#define UC_ADC_H
#include <AbstractWordIn.h>

class UC_ADC : public AbstractWordIn
{
public:
	UC_ADC (unsigned char adcChan, unsigned char devNum = 0);
	virtual  unsigned long  Read();
	virtual ~UC_ADC() {}
private:
	unsigned char  adCh;
	volatile unsigned long*  dataRg; //= {(volatile unsigned char*) 0xE000C00C, (volatile unsigned char*) 0xE001000C};
};

#endif

