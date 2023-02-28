#ifndef ABSTRACT_STEP_MOTOR_CTL_H
#define ABSTRACT_STEP_MOTOR_CTL_H
//D:\d2\www\2013Proj\soft\Abstract\AbstractStepMotorCtl.h
struct SMState
{
	bool leftEnd;
	bool rightEnd;
	int speedInst;
	int curPos;
	bool isClbrt;
};

class AbstractStepMotorCtl
{
public:	
	virtual bool Router(char mode) = 0;
	virtual void Move(int nSteps) = 0;
	virtual void Stop() = 0;
	virtual bool GetState(SMState* state) = 0;
	virtual bool GetPosition( int* steps) = 0;
	virtual void SetSpeed (unsigned int stepsPerSecond) = 0;
	virtual unsigned int GetSpeed () = 0;
	virtual void SetStartCur (unsigned int qw) = 0;
	virtual void SetWorkCur (unsigned int qw) = 0;
	virtual void SetKeepCur (unsigned int qw) = 0;
	virtual void SetDivider ( unsigned int div ) = 0;

	virtual int isMoving() = 0;
};

#endif

