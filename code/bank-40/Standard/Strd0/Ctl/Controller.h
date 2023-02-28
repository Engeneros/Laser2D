#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <AbstractController.h>
#include <AbstractConvertor-D.h>

class Controller : public AbstractController
{
public:
	Controller (AbstractConvertor_D* conv, double* input, unsigned int* output, double minTg, double maxTg, double iniVal );
	virtual void Set(double val);
	virtual  double Get ();
	virtual bool Router() = 0;
	virtual ~Controller() {}
protected:
	double max, min;
	double tgVal;
	double* msr;
	double prevMsr;
	double dacVal;
	unsigned int* effector;
	AbstractConvertor_D* cnv;		
};

class TermostatVanadat : public Controller
{
public:
	TermostatVanadat (AbstractConvertor_D* conv, double* input, unsigned int* output, double minTg, double maxTg, double iniVal ) : 
	Controller ( conv, input, output, minTg, maxTg, iniVal) { }
	virtual bool Router();
	virtual ~TermostatVanadat(){}
};

class TermostatLD : public Controller
{
public:
	TermostatLD (AbstractConvertor_D* conv, double* input, unsigned int* output, double minTg, double maxTg, double iniVal ) : 
	Controller ( conv, input, output, minTg, maxTg, iniVal) { }
	virtual bool Router();
	virtual ~TermostatLD(){}
};

class TermostatLBOPrecision : public Controller
{
public:
	TermostatLBOPrecision (AbstractConvertor_D* conv, double* input, unsigned int* output, double minTg, double maxTg, double iniVal ) : 
	Controller ( conv, input, output, minTg, maxTg, iniVal) { }
	virtual bool Router();
	virtual ~TermostatLBOPrecision(){}
};

class TermostatLBORough : public Controller
{
public:
	TermostatLBORough (AbstractConvertor_D* conv, double* input, unsigned int* output, double minTg, double maxTg, double iniVal ) : 
	Controller ( conv, input, output, minTg, maxTg, iniVal) { }
	virtual bool Router();
	virtual ~TermostatLBORough(){}
};


class TermostatLBO : public AbstractController
{
public:	
	TermostatLBO ( AbstractController*  ctlPrecision, AbstractController*  ctlRough);
	
	virtual void Set(double val);
	virtual  double Get ();
	virtual bool Router();
	virtual ~TermostatLBO() {}
protected:
	AbstractController* prec;
	AbstractController*  rough;
	bool  isLock;
//	double max, min;
//	double tgVal;
//	double* msr;
//	double prevMsr;
//	double dacVal;
//	unsigned int* effector;
//	AbstractConvertor_D* cnv;		
};



#endif

