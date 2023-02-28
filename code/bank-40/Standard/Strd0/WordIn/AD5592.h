#ifndef  AD5592_H
#define AD5592_H
#include  <AbstractADC.h>
#include <AbstractDAC.h>
#include  <AbstractpinOut.h>
#include <AbstractSpi.h>
#include <AbstractRouter.h>


class AD5592Device 
{
public:	
	AD5592Device (AbstractPinOut* chipSel,  AbstractSpi* interface, unsigned char dacChan, unsigned char adcChan);	
	void DACWrite ( unsigned char chan, unsigned short data );
	void DACFirstWrite ( unsigned char chan, unsigned short data );
	unsigned  short ADCRead ( unsigned char chan);
	 ~AD5592Device() {}
private:
	unsigned short adData[16];
//	unsigned char adChan[16];
//	unsigned char currChan;
	unsigned char nAdChans;
	void SendW(unsigned short data);
	AbstractPinOut* chSel;
	AbstractSpi* hwIfc;
};

class AD5592DacCh : public AbstractDAC
{
public:
	AD5592DacCh (unsigned char chanal, AD5592Device* dev) : daCh(chanal), chip(dev) {}
	virtual void FirstWrite(unsigned int data) {chip->DACFirstWrite(daCh, data);}
	virtual void Write(unsigned int data) {chip->DACWrite(daCh, data);}
	virtual void Release() {}
	virtual ~AD5592DacCh(){}
private:
	unsigned char daCh;
	AD5592Device* chip;
};

//class AD5592DacFirst : public AbstractDAC
//{
//public:
//	AD5592DacFirst(unsigned char chanal, AD5592Device* dev) : daCh(chanal), chip(dev) {}
//	virtual void Write( unsigned int data) {chip->DACFirstWrite(daCh, data);}
//	virtual ~AD5592DacFirst(){}
//private:
//	unsigned char daCh;
//	AD5592Device* chip;
//};


class AD5592adcCh : public AbstractADC
{
public:
	AD5592adcCh (unsigned char chanal, AD5592Device* dev, AD5592DacCh* dac, unsigned short* dacData) 
	: AbstractADC(),  adCh(chanal), chip(dev), pair(dac), daDat (dacData) {}
	virtual void Start();
	virtual void Stop() {}
	virtual AbstractADC& operator ++ ();
	virtual void Accumulate ( );
	virtual ~AD5592adcCh() {}
private:
	unsigned char adCh;
	AD5592Device* chip;
	AD5592DacCh* pair;
	unsigned short* daDat;
};
#endif
