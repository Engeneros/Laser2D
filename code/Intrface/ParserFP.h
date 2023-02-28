#ifndef PARSER_FP_H
#define PARSER_FP_H
#include <AbstractFPParser.h>
#include <AbstractParser.h>
#include <AbstractStepMotorCtl.h>
#include <AbstractPinOut.h>
#include <AbstractBuffOut.h>
#include <InterfaceParticularity.h>


bool StringComparator (const char* str, const char* ref, unsigned int refLen);

class ParserFP : public AbstractFPParser
{
public:
	ParserFP (SMState* cristallState,  SMState* filterState);
	virtual bool Translate(const char* strIn, unsigned  int inputLen, FunAddrDat* fAddrD, char mode);
	virtual ~ParserFP(){}
private:
	 SMState*  crSmSt;
	 SMState*  filSmSt;
	void Stop(FunAddrDat* fad);
	void GetButtonSense(int* cnt, bool left, bool right, FunAddrDat* fad, SMState* state);
	int lambdaCnt;
	int pumperCnt;
};

class ParserSt : public AbstractFPParser
{
public:
	ParserSt(const  abrv* modules, const abrv* actFunct, const abrv* shFunct,  unsigned char nModules, unsigned char nFActiv, unsigned char nFShadow);
	virtual bool Translate(const char* strIn, unsigned int inputLen, FunAddrDat* fAddrD, char mode);
	virtual ~ParserSt(){}
private:
	unsigned char nFunA, nFunS;
	unsigned char nMod;
	const abrv*  modAb;
	const  abrv* fnAbActiv;	
	const  abrv* fnAbShdw;	
};

class ModulSM : public AbstractFPModul
{
public:
	ModulSM (AbstractStepMotorCtl* stMotCtl, SMState* staSM, AbstractBuffOut* ifc,  bool* ctlMode, 
	const bool* man, const char* moduleName, bool* invSM, unsigned int memAddr);	
	virtual bool Router (unsigned int fNum, int data);
	virtual ~ModulSM () { }
private:
	AbstractStepMotorCtl* smCtl;
	SMState* state;
	AbstractBuffOut* usrOut;

	bool* modeControl;
	const bool* isManCt;
	char myName [MAX_INP_STR_LEN] ;
	unsigned int nameLen;
	char* cmdAndData;
	bool* isInv;
	unsigned int mAddr;
	int preset;
	bool waitSens;
};

class DoubleSMMod :  public AbstractFPModul
{
public:	
	DoubleSMMod (AbstractFPModul* x, AbstractFPModul* y);
	virtual bool Router (unsigned int fNum, int data);
	virtual ~DoubleSMMod() {}
private:
	AbstractFPModul* first;
	AbstractFPModul* second;
};


class GeneralModul :public AbstractFPModul
{
public:
	GeneralModul ( AbstractStepMotorCtl* crMotor, AbstractStepMotorCtl* fiMotor, AbstractStepMotorCtl* etHDrive,  AbstractBuffOut* ifc,
						  bool* crOk, bool* fiOk , const bool* man);
	virtual bool Router (unsigned int fNum, int data);
	virtual ~GeneralModul() {}
private:	
	AbstractBuffOut* usrOut;
	AbstractStepMotorCtl* crisMtr;
	AbstractStepMotorCtl* filtrMtr;
	AbstractStepMotorCtl* etaHDr;
	bool*  isCrOk;
	bool*  isFlOk;
	const bool* isManCt;
};

class StubModul : public AbstractFPModul
{
	private:
		AbstractPinOut* pOut;
	public:
		StubModul(AbstractPinOut* pin) {pOut = pin; pOut->Set();}
		virtual bool Router (unsigned int fNum, int data) ;
		virtual ~StubModul(){}
};


//class ModulFPsm : public AbstractFPModul
//{
//public:
//	ModulFPsm ( AbstractStepMotorCtl* stMotCtl,   AbstractPinOut* lfRedLed, AbstractPinOut* lfGreenLed, AbstractPinOut* rgRedLed, AbstractPinOut* rgGreenLed);
//	virtual bool Router (unsigned int fNum, int data);
//	virtual  bool RouterSh (unsigned int fNum, int data);
//	virtual ~ModulFPsm() {}
//private:
//	AbstractStepMotorCtl* smCtl;
//	SMState state;
//	AbstractPinOut* leftRed;
//	AbstractPinOut* leftGreen;
//	AbstractPinOut* rightRed;
//	AbstractPinOut* rightGreen;
//};




//class ModulSMPassive : public AbstractFPModul
//{
//	ModulSMPassive (AbstractStepMotorCtl* stMotCtl, SMState* staSM, AbstractBuffOut* ifc);
//	virtual bool Router (unsigned int fNum, int data);// );//,  Instruction* fAndAddr, char*strOut, unsigned int outputLen) = 0;
//	bool RouterSh (unsigned int fNum, int data);
//	virtual ~ModulSMPassive () {}
//private:
//	AbstractStepMotorCtl* smCtl;
//	SMState* state;
//	AbstractBuffOut* usrOut;
//	AbstractPinOut* leftRed;
//	AbstractPinOut* leftGreen;
//	AbstractPinOut* rightRed;
//	AbstractPinOut* rightGreen;
//};

//class ModulSMActive : public AbstractFPModul
//{
//	ModulSMActive ( AbstractStepMotorCtl* stMotCtl,  SMState* staSM,  AbstractBuffOut* ifc, AbstractFPModul* passive,
//	AbstractPinOut* lfRedLed,  AbstractPinOut* lfGreenLed,  AbstractPinOut* rgRedLed,  AbstractPinOut* rgGreenLed);
//	virtual bool Router (unsigned int fNum, int data);// );//,  Instruction* fAndAddr, char*strOut, unsigned int outputLen) = 0;
//	virtual ~ModulSMActive () {}
//private:
//	AbstractFPModul* shadow;
//	AbstractStepMotorCtl* smCtl;
//	SMState* state;

//	AbstractBuffOut* usrOut;
//	AbstractPinOut* leftRed;
//	AbstractPinOut* leftGreen;
//	AbstractPinOut* rightRed;
//	AbstractPinOut* rightGreen;
//};



//class ModulParser : public AbstractFPModul
//{
//public:	
//		ModulParser(AbstractStepMotorCtl* stMotCtl, AbstractPinOut* lfRedLed, AbstractPinOut* lfGreenLed, AbstractPinOut* rgRedLed, AbstractPinOut* rgGreenLed,
//		const char* strIn, unsigned int inputLen);
//		virtual bool Router ();
//private:
//	AbstractStepMotorCtl* smCtl;
//	SMState state;
//	int stepsDone;
//	AbstractPinOut* leftRed;
//	AbstractPinOut* leftGreen;
//	AbstractPinOut* rightRed;
//	AbstractPinOut* rightGreen;
//};



#endif




