#ifndef STEP_MOTOR_CTL_H
#define STEP_MOTOR_CTL_H
#include <AbstractStepMotorCtl.h>
#include <AbstractBuffIn.h>
#include <AbstractBuffOut.h>
#include <AbstractWordOut.h>

union memData
{
	int positions;
	char block[4];
};

class StepMotorClt :public AbstractStepMotorCtl
{
private:
	AbstractBuffIn* stin;
	AbstractBuffOut* stout;
	SMState* stt;
	int speed;
	int tgStep, realStep;
	unsigned int memAddr;
	int savedPos;
	int shiftPos;
	int refreshCounter;
	char isMoveEnable;
public:	
	StepMotorClt(AbstractBuffIn* strIn, AbstractBuffOut* strOut, SMState* smStatus, unsigned int addR );
	virtual bool Router( char mode );
	virtual void Move(int nSteps);
	virtual void Stop();
	virtual bool GetState(SMState* state);
	virtual bool GetPosition( int* steps);
	virtual void SetSpeed (unsigned int stepsPerSecond);
	virtual unsigned int GetSpeed ();

	virtual void SetStartCur (unsigned int qw) ;
	virtual void SetWorkCur (unsigned int qw);
	virtual void SetKeepCur (unsigned int qw);
	virtual void SetDivider ( unsigned int div ) ;
	
	virtual int isMoving() {return stt->speedInst;}
	virtual ~StepMotorClt() {}
};

class HalvoDrvCtl : public AbstractStepMotorCtl
{
private:
	unsigned int* dac;
	double* adc;
	SMState* stt;
	double qwpmSec, qpS, qwpmSecAb, qpSAb, realVal;
	int val, tgVal, delta;	
	static const int LEFT_EDGE = -32767;
	static const int RIGHT_EDGE = 32767;
public:
	HalvoDrvCtl ( unsigned int* fpDac, double* fpAdc, SMState* smStatus ); //, AbstractWordIn* fpAdc);
	virtual bool Router( char mode );
	virtual void Move(int nSteps);
	virtual void Stop();
	virtual bool GetState(SMState* state);
	virtual bool GetPosition( int* steps);
	virtual void SetSpeed (unsigned int stepsPerSecond);
	virtual unsigned int GetSpeed ();
	virtual void SetStartCur (unsigned int qw) {}
	virtual void SetWorkCur (unsigned int qw) {}
	virtual void SetKeepCur (unsigned int qw) {}
	virtual void SetDivider ( unsigned int div ) {}

	virtual int isMoving();
	virtual ~HalvoDrvCtl() {}
};


#endif
