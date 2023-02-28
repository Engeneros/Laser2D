#include <AD7694.h>


AD7694::AD7694(AbstractIO* ssp, AbstractPinOut* buttLoad)
{
	ifc = ssp;
	cSel = buttLoad;
	cSel->Set();
}

unsigned long AD7694::Read()
{
	cSel->Clear();
	unsigned long ret = ifc->TxRx( 0 );
	cSel->Set();	
	return ret;
}







	


