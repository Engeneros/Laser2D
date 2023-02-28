#include <AD53x8.h>

AD53x8::AD53x8 (AbstractIO* ssp, AbstractPinOut* synkPin, AbstractPinOut* loadPin)
{
	ifc = ssp;
	sync = synkPin;
	sync->Set();
	loadPin->Clear();
	Send(0x8000);//Vdd as Vref
	Send(0xa000); //LDAC == 0
//	Send(0xe000); //data reset;
}

void AD53x8::Send(unsigned long data)
{
	sync->Clear();
	ifc->Tx(data);
	sync->Set();
}
//////////////

AD5308ch::AD5308ch (AbstractWordOut* dac, unsigned long chan, unsigned long val)
{
	preamble = chan << 12;
	chip = dac;
	Send(val);
}
	
void AD5308ch::Send(unsigned long data)
{
	chip->Send(data << 4 | preamble);
}

////////////////

AD5328ch::AD5328ch (AbstractWordOut* dac, unsigned long chan, unsigned long val)
{
	preamble = chan << 12;
	chip = dac;
	Send(val);
}
	
void AD5328ch::Send(unsigned long data)
{
	chip->Send (data | preamble);
}



