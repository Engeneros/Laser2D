#include <AD5592.h>
#include <BoardDevices.h>

static const unsigned short ADC_NOP_ADDR = 0 ;
static const unsigned short ADC_DAC_RESET = 0x7d9c;
static const unsigned short ADC_PIN_CONF_ADDR = 4 <<  11;
static const unsigned short DAC_PIN_CONF_ADDR = 5 <<  11;
static const unsigned short ADC_SEQUENCE_ADDR = 2 << 11;
//static const unsigned short ADC_RESET_ADDR = 2 << 11;
static const unsigned short  ADC_REPIET_BIT = 1 << 9;

void AD5592Device::SendW(unsigned short data)
{
	chSel->Clear();
	hwIfc->TxWord ( data );
	while(hwIfc->IsReady() == false)
	{
//		vd11Yellow.Toggle();
//		vd10Green.Toggle();
	}
	chSel->Set();
	unsigned long rxData;
	hwIfc->RxWordUltimate( &rxData);
}

AD5592Device::AD5592Device (AbstractPinOut* chipSel,  AbstractSpi* interface, unsigned char dacChan, unsigned char adcChan) :
chSel(chipSel), hwIfc(interface)
{
	chSel->Set();
	hwIfc->HwPrepare();
	SendW (ADC_DAC_RESET );
	SendW (DAC_PIN_CONF_ADDR | dacChan);
	SendW (ADC_PIN_CONF_ADDR | adcChan);
	SendW (ADC_SEQUENCE_ADDR | ADC_REPIET_BIT | adcChan); 
//	unsigned char mask = 1;
//	unsigned char chanNum = 0;
//	while (chanNum < 8)
//	{
//		if((adcChan & mask) != 0)
//		{
//			adChan [nAdChans++] = chanNum; 
//		}
//		mask = 1 << ++chanNum;
//	}
	SendW (ADC_NOP_ADDR);
//	currChan = 0;
}
//xxx
#include <stdio.h>
#include <lpc2148_Spi_regs.h>
void AD5592Device::DACWrite ( unsigned char chan, unsigned short data )
{
	chSel->Clear();
	unsigned long rxDt;
//	char bfr[64];
	hwIfc->RxWordUltimate(&rxDt);
	unsigned long rdChan = rxDt >> 12;
	adData [ rdChan] = rxDt & 0x0fff;
//	sprintf ( bfr, " raw=%x ch=%x d=%x%c%c", rxDt, rdChan, adData[ rdChan],  13, 10);
//	uartTx1.Send(bfr);
//	hwIfc->RxWordUltimate(&rxDt);
//hwIfc->RxWordUltimate(&rxDt);	
	hwIfc->TxWord ( 1 << 15  |   chan <<  12   |  data);

}

void AD5592Device::DACFirstWrite ( unsigned char chan, unsigned short data )
{
	hwIfc->HwPrepare();
	DACWrite(chan, data);
}


unsigned short AD5592Device::ADCRead ( unsigned char chan)
{
	chSel->Set();
	return adData [chan];
}

AbstractADC& AD5592adcCh::operator ++ ()
{
	++samples;
	summ += chip->ADCRead ( adCh  );
	return *this;
}



void  AD5592adcCh::Accumulate ( )
{
	++samples;
	summ += chip->ADCRead ( adCh );
}


void AD5592adcCh::Start() 
{
	pair->FirstWrite(*daDat);
}

