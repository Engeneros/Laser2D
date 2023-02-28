#ifndef CONTROLLER_C_H
#define CONTROLLER_C_H
#include <AbstractController-C.h>
#include <AbstractConvertor-D.h>

class Controller_C : public AbstractController_C
{
public:
	Controller_C (AbstractConvertor_D* conv, double* input, unsigned int* output, double minTg, double maxTg, double iniVal );
	virtual void SetLeftRef  (double refVal);
	virtual void SetRightRef (double refVal);
	virtual void Calibrate();
	virtual void Set(double val);
	virtual  double Get ();
	virtual bool Router() = 0;
	virtual ~Controller_C() {}
protected:
	double max, min;
	double tgVal;
	double* msr;
	double prevMsr;
	double dacVal;
	unsigned int* effector;
	AbstractConvertor_D* cnv;		
};

class CtlDummy : public Controller_C
{
	public:
		CtlDummy(AbstractConvertor_D* conv, double* input) :
		Controller_C (conv, input, 0, 0, 0, 0){}
		virtual bool Router() { return true;}
		virtual ~CtlDummy() {}
};


class TstatVanadat : public Controller_C
{
public:
	TstatVanadat (AbstractConvertor_D* conv, double* input, unsigned int* output, double minTg, double maxTg, double iniVal ) : 
	Controller_C ( conv, input, output, minTg, maxTg, iniVal) { }
	virtual bool Router();
	virtual ~TstatVanadat(){}
};


class TstatFan : public Controller_C
{
public:
	TstatFan (AbstractConvertor_D* conv, double* input, unsigned int* output, double minTg, double maxTg, double iniVal, double* current) : 
	Controller_C ( conv, input, output, minTg, maxTg, iniVal) { cur =  current; }
	virtual bool Router();
	virtual ~TstatFan(){}
private:
	double* cur;
};


class CurrCtlLD : public Controller_C
{
public:
	CurrCtlLD (AbstractConvertor_D* conv, double* input, unsigned int* output, double minTg, double maxTg, double iniVal ) : 
	Controller_C ( conv, input, output, minTg, maxTg, iniVal) {  tgSlow =  tgVal = iniVal; }
	virtual bool Router();
	virtual ~CurrCtlLD(){}
private:
	double tgSlow;
	double msrAvg;
	
};

class TstatLD : public Controller_C
{
public:
	TstatLD (AbstractConvertor_D* conv, double* input, unsigned int* output, double minTg, double maxTg, double iniVal ) : 
	Controller_C ( conv, input, output, minTg, maxTg, iniVal) { }
	virtual bool Router();
	virtual ~TstatLD(){}
};

class TstatLBO : public Controller_C
{
public:
	TstatLBO (AbstractConvertor_D* conv, double* input, unsigned int* output, double minTg, double maxTg, double iniVal ) : 
	Controller_C ( conv, input, output, minTg, maxTg, iniVal) { }
	virtual bool Router();
	virtual ~TstatLBO(){}
};


#endif

