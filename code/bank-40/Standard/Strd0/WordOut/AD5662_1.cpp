#include <AD5662_1.h>

void AD5662::Write(unsigned int data)
{
	csPin->Set();
	unsigned long rxd;
	hwIfc->RxWordUltimate( &rxd);
	csPin->Clear();
	hwIfc->TxWord(data);
}

void AD5662::FirstWrite( unsigned int data)
{
	csPin->Set();
	hwIfc->HwPrepare();
	unsigned long rxd;
	hwIfc->RxWordUltimate( &rxd);
	csPin->Clear();
	hwIfc->TxWord((data >> 12) & 0xf);
	while(hwIfc->IsReady() == false)
	{
	}
	hwIfc->RxWordUltimate( &rxd);
	hwIfc->TxWord(data & 0xfff);

	hwIfc->Write(data);
}
