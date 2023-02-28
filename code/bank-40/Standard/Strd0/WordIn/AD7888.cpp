#include <AD7888.h>

AD7888::AD7888(AbstractIO* ssp, AbstractPinOut* buttLoad)
{
	ifc = ssp;
	cSel = buttLoad;
	cSel->Set();
	prevCfg = 0;
}

unsigned long AD7888::Read(unsigned long cfg)
{
	cSel->Clear();
	unsigned long ret = ifc->TxRx(cfg);
	cSel->Set();	
	if(cfg  != prevCfg)
	{
		cSel->Clear();
		ret = ifc->TxRx(cfg);
		prevCfg = cfg;
		cSel->Set();	
	}	
	
	return ret;
}

AD7888ch::AD7888ch (AD7888* adc, unsigned long chan)
{
	chip = adc;
	preamble = chan << 11 |  1 <<  10;
}

unsigned long AD7888ch::Read()
{
	return chip->Read (preamble);
}

AD7888ConMd567::AD7888ConMd567(AbstractIO* ssp,  AbstractPinOut* chipSel)
{
	cSel = chipSel;
	cSel->Set ();
	ifc = ssp;
	rdChan =  5;
	wrChan = 7;
	for(int i = 0; i < 8; ++i)
	{
		wrData[i] = ( ((unsigned short) i) << 11) |  1 <<  10;
	}
}
	
unsigned long AD7888ConMd567::Read(unsigned char chan)
{
	return rdData[chan];
}

void AD7888ConMd567::Router()
{
	cSel->Set();
	++wrChan;
	wrChan = ( wrChan > 7)? 0 : wrChan;
	++rdChan;
	rdChan = ( rdChan > 7)? 0 : rdChan;
	rdData[rdChan] = ifc->Rx();
	cSel->Clear();
	ifc->Tx(wrData[wrChan]);	
}
