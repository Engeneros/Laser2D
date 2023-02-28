#ifndef  BOARD_DEVICES_H
#define BOARD_DEVICES_H
#include <AbstractMetronome.h>
#include <AbstractMemoryIn.h>
#include <AbstractMemoryOut.h>
#include <AbstractPinOut.h>
#include <AbstractPinIn.h>

#include <AbstractBuffOut.h>
#include <AbstractBuffIn.h>

#include <AbstractADC.h>
#include <AbstractDAC.h>
#include <AbstractConvertor-D.h>
#include <AbstractController-E.h>
#include <AbstractParser-Bi40.h>

extern AbstractMetronome& tRef0;
extern AbstractMetronome& tRef1;
extern AbstractMetronome& tRef2;
extern AbstractMetronome& tRef3;

void DelayUs (unsigned int us);
void DelayMs (unsigned int ms);

extern AbstractMemoryOut&  memWriter;
extern AbstractMemoryIn&    memReader;

extern  AbstractPinOut& vd10Green;
extern AbstractPinOut& vd11Yellow;

extern  AbstractPinOut& vt8EnableA;
extern AbstractPinOut& vt9EnableB;

extern AbstractPinIn&  Conf1;
extern AbstractPinIn&  Conf2;
extern AbstractPinIn&  Conf3;
extern AbstractPinIn&  Conf4;

extern  AbstractBuffIn& uartRx0;
extern  AbstractBuffIn& uartRx1;

extern  AbstractBuffOut& uartTx0;
extern  AbstractBuffOut& uartTx1;


extern AbstractADC& stubAd;
extern AbstractADC& tLda;
extern AbstractADC& tLdb;

extern AbstractADC& iLda;
extern AbstractADC& iLdb;
extern AbstractADC& uLda;
extern AbstractADC& uLdb;
extern AbstractADC& pLda;
extern AbstractADC& pLdb;

extern AbstractCtl& fcCurrA ;
extern AbstractCtl& fcCurrB;

extern AbstractCtl& iAAufseher;
extern AbstractCtl& iBAufseher;

extern AbstractCtl& fcTA;
extern AbstractCtl& fcTB;
extern AbstractCtl& fcFan;
extern AbstractCtl& fcPwr;
extern AbstractCtl& fcUA;
extern AbstractCtl& fcUB;

extern  AbstractController_E& tstA;
extern  AbstractController_E& tstB;

extern AbstractCtl& fcPA;
extern AbstractCtl& fcPB;
extern AbstractPinOut& pwPn;

extern AbstractDAC& fanDAC;
extern AbstractDAC& dacIa;
extern AbstractDAC& dacIb;
extern AbstractDAC& dacTa;
extern AbstractDAC& dacTb;

extern unsigned short fanDacData;

extern AbstractParser& parser;
extern  AbstractModul&  modIa;
extern AbstractModul& modIb;
extern AbstractModul& modTa;
extern AbstractModul& modTb;
extern AbstractModul& modFan;
extern AbstractModul& modPwr;
extern AbstractModul&  modUa;
extern AbstractModul& modUb;
extern AbstractModul& modPa;
extern AbstractModul& modPb;

extern  AbstractModul&  dbg_modIa;
extern AbstractModul& dbg_modIb;
extern AbstractModul& dbg_modTa;
extern AbstractModul& dbg_modTb;
extern AbstractModul& dbg_modFan;
extern AbstractModul& dbg_modPwr;
extern AbstractModul&  dbg_modUa;
extern AbstractModul& dbg_modUb;
extern AbstractModul& dbg_modPa;
extern AbstractModul& dbg_modPb;


void RouterAD();
void ADCAveranger();


//extern AbstractCtl& chk;

















//AbstractMetronome* GetClocker();

//AbstractMetronome* GetTref0();
//AbstractMetronome* GetTref1();
//AbstractMetronome* GetTref2();
//AbstractMetronome* GetTref3();

//void DelayUs (unsigned int us);
//void DelayMs (unsigned int ms);

//AbstractMemoryOut* GetMemWriter();
//AbstractMemoryIn* GetMemReader();

//AbstractPinOut* GetGreenVD10();
////AbstractPinOut * GetYellowVD11();
//extern AbstractPinOut* VD11Yellow;

//AbstractPinIn*  GetConf1();
//AbstractPinIn*  GetConf2();
//AbstractPinIn*  GetConf3();
//AbstractPinIn*  GetConf4();

//AbstractBuffIn* GetUARTrx0();
//AbstractBuffIn* GetUARTrx1();

//AbstractBuffOut* GetUARTtx0();
//AbstractBuffOut* GetUARTtx1();

//AbstractADC& GetTldADCa();
//AbstractADC& GetTldADCb();


#endif









