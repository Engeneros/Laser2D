#ifndef CONTROLLER_E_H
#define CONTROLLER_E_H
#include <AbstractController-E.h>
#include <AbstractConvertor-D.h>
#include <AbstractPinOut.h>

class Controller_E : public AbstractController_E
{
public:
	Controller_E (AbstractConvertor_D* conv, double* input, unsigned short* output, double minTg, double maxTg, double iniVal );
	virtual void SetLeftRef  (double refVal);
	virtual void SetRightRef (double refVal);
	virtual void Calibrate();
	virtual void Set(double val);
	virtual  double Get ();
	virtual unsigned int GetDac() {return *effector;};
	virtual double GetAdc() {return *msr;}
	virtual void SetDAC( unsigned int val) { *effector = val; isStab= false;}
	virtual bool Router() = 0;
	virtual ~Controller_E() {}
protected:
	AbstractConvertor_D* cnv;	
	double* msr;
	unsigned short* effector;
	double  min, max;
	double tgVal;	
	double prevMsr;
	double dacVal;
	bool isStab;
	double minBrd;
	double maxBrd;
};

class DirectCurrCtl : public AbstractController_E
{
public:
	DirectCurrCtl (AbstractConvertor_D* conv, unsigned short* output, double minTg, double maxTg, double iniVal,  AbstractPinOut* en );
	virtual void SetLeftRef  (double refVal);
	virtual void SetRightRef (double refVal);
	virtual void Calibrate();
	virtual void Set(double val);
	virtual  double Get ();
	virtual unsigned int GetDac() {return *effector;};
	virtual double GetAdc() {return  (double)*effector;}
	virtual void SetDAC( unsigned int val) {  *effector = val; isStab= false;  (val > 0)? currEn->Set() : currEn->Clear(); }
	virtual bool Router();
	virtual ~DirectCurrCtl() {}
protected:
	AbstractConvertor_D* cnv;	
	unsigned short* effector;
	double  min, max;
	double tgVal;	
	double tgSlow;
	double prevMsr;
	double dacVal;
	bool isStab;
	AbstractPinOut* currEn;
};


class TstatFan : public Controller_E
{
public:
	TstatFan (AbstractConvertor_D* conv, double* input, unsigned short* output, double minTg, double maxTg, double iniVal, AbstractController_E* iCtl) : 
	Controller_E ( conv, input, output, minTg, maxTg, iniVal), currentCtl(iCtl) {}
	virtual bool Router();
	virtual ~TstatFan(){}
private:
	AbstractController_E* currentCtl;
	double* cur;
};


//class CurrCtlLD : public Controller_E
//{
//public:
//	CurrCtlLD (AbstractConvertor_D* conv, double* input, unsigned int* output, double minTg, double maxTg, double iniVal, AbstractConvertor_D* dacConv) : 
//	Controller_E ( conv, input, output, minTg, maxTg, iniVal), dacCnv (dacConv) { tgDac = dacCnv->GetValue(iniVal); }
//	virtual void Set(double val);
//	virtual bool Router();
//	virtual ~CurrCtlLD(){}
//private:
//	double tgSlow;
//	double tgDac;
//	double msrAvg;
//	AbstractConvertor_D* dacCnv;	
//};

class TstatLD : public Controller_E
{
public:
	TstatLD (AbstractConvertor_D* conv, double* input, unsigned short* output, double minTg, double maxTg, double iniVal ) : 
	Controller_E ( conv, input, output, minTg, maxTg, iniVal) { }
	virtual bool Router();
	virtual ~TstatLD(){}
};

class Indicator : public  AbstractController_E
{
	private:
	AbstractConvertor_D* cnv;	
	double* msr;	
public:
	Indicator (AbstractConvertor_D* conv, double* input) :  cnv (conv), msr (input) {}
	virtual void SetLeftRef  (double refVal) { cnv->AddPointLeft(*msr, refVal);}
	virtual void SetRightRef (double refVal) {cnv->AddPointRight(*msr, refVal);}
	virtual void Calibrate() {cnv->Calibrate();}
	virtual void Set(double val) {}
	virtual  double Get () {return cnv->GetValue(*msr);}
	virtual unsigned int GetDac() { return 0;};
	virtual double GetAdc() {return *msr;}
	virtual void SetDAC( unsigned int val) {};
	virtual bool Router() { return false;};
	virtual ~Indicator() {}
};

#include <AbstractPinOut.h>

//class PowerCtl :  public AbstractPinOut,   AbstractController_E
//{
//public:
//	PowerCtl ( AbstractPinOut* control,  double* current);
//	virtual bool IsOn() ;
//	virtual void Clear() ;
//	virtual void  Set() ;
//	virtual void Toggle();
//	virtual void Send(bool state);
//	virtual bool Router();	
//	
//	virtual void SetLeftRef  (double refVal) {}
//	virtual void SetRightRef (double refVal) {}
//	virtual void Calibrate() {}
//	virtual void Set(double val);
//	virtual  double Get ();
//	virtual unsigned int GetDac() {return 0;}
//	virtual void SetDAC( unsigned int val) {};
//	virtual ~PowerCtl () {}
//private:
//	AbstractPinOut* pCtl;
//	double* ldCur;
//	bool mustOn;
//	bool mustOff;
//	int dtCnt;	

//	bool isPwr;
//	static const int DEAD_TIME = 100;
//};

class PowerPin : public AbstractPinOut, public AbstractCtl
{
public:
	PowerPin ( AbstractPinOut* effector,AbstractController_E* currCtlA,  AbstractController_E* currCtlB, double* currentA,  double* currentB,
					 AbstractPinOut* luminaEnA, AbstractPinOut* luminaEnB, AbstractPinOut* powerIndicator, AbstractPinIn* powerButton);
	virtual bool IsOn()  { return pin->IsOn(); }
	virtual void Clear ();
	virtual void  Set();// { pin->Set(); mustOff =  false;} 
	virtual void Toggle() {}
	virtual bool Router();
	virtual ~PowerPin() {}	
private:
	AbstractPinOut* pin;
	AbstractPinOut* currEnA;
	AbstractPinOut* currEnB;
	AbstractController_E *cuCtlA, *cuCtlB;
	double	*currA, *currB;		
	bool mustOff;
	int offCnt, indicCnt, buttCnt;
	static const int SLEEP_TIME = 30;
	bool dacOff,  enbOff,  pwrOff;
	AbstractPinOut* pwLED;
	AbstractPinIn* pwBt;	
};

#endif

