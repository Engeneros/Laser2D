#include <LTC2447.h>
#include <lpc2148_SPI_Regs.h>

Ltc2447::Ltc2447 (AbstractPinOut* chipSel, AbstractSpi* interface, unsigned char chan, bool inpDif, bool refDif) :
AbstractADC(),  cSel(chipSel), hwIfc ( interface)
{
	chipSel->Set();
	hwIfc->SetDataLen(32);
	hwIfc->SetSpeed(32);
	hwIfc->SetClockType(CLK_LOW,  CLK_FIRST);
	mswMosi = 0xa000 | (chan << 8);
	if(inpDif == false )//&& refDif != false)
		mswMosi |= 0x1000;
	if (refDif == false)
		mswMosi |= 0x0400;	
}

#include <BoardDevices.h>
void Ltc2447::Start()
{
	cSel->Clear();
	hwIfc->HwPrepare();
	hwIfc->TxWord (mswMosi);
	hwIfc->TxWord ( 0 );
//	vd11Yellow.Toggle();
//	while ((SSPCPSR & BUSY_BIT) != 0)
//	{
//	}
//	unsigned short tmp = SSPDR;
//	SSPCR1 = 2;
//	SSPCR0 = 0x020f;
//	hwIfc->HwPrepare();
//	SSPDR = 0x5555;
}

void Ltc2447::Stop()
{
	cSel->Set();
}

AbstractADC& Ltc2447::operator ++ ()
{
	cSel->Set();
	unsigned long msw, lsw;
	bool isReadyM = hwIfc->RxWordUltimate(&msw);
	bool isReadyL = hwIfc->RxWordUltimate(&lsw);
	if(isReadyL && isReadyM )
	{
		summ += ((msw & 0x0000ffff ) << 4) | ((lsw >> 12) & 0x0000000f);
		++samples;
	}
	hwIfc->RxWordUltimate(&lsw);
	hwIfc->RxWordUltimate(&lsw);
	return *this;
}


void Ltc2447::Accumulate()
{
	cSel->Set();
	unsigned long msw, lsw;
	bool isReadyM = hwIfc->RxWord(&msw);
	bool isReadyL = hwIfc->RxWord(&lsw);
	if(isReadyL && isReadyM )
	{
		summ += ((msw & 0x0000ffff ) << 4) | ((lsw >> 12) & 0x0000000f);
		++samples;
	}
//	hwIfc->RxWord(&lsw);
//	hwIfc->RxWord(&lsw);
//	return *this;
}

