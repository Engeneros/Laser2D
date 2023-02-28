#include <AD5662.h>

AD5662::AD5662  (AbstractIO* ssp, AbstractPinOut* chipSel)
{
	ifc = ssp;
	sync = chipSel;
	sync->Set();
//	Send(0xe000); //data reset;
}

void AD5662::Send(unsigned long data)
{
	sync->Clear();
	ifc->Tx(data);
	sync->Set();
}

AD5662Fast::AD5662Fast  (AbstractIO* ssp, AbstractPinOut* chipSel)
{
	ifc = ssp;
	sync = chipSel;
	sync->Set();
//	Send(0xe000); //data reset;
}

void AD5662Fast::Send(unsigned long data)
{
	sync->Set();
	sync->Clear();
	ifc->FastTx(data);
}
//////////////


