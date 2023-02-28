#ifndef METRONOME_H
#define METRONOME_H

#include <AbstractMetronome.h>

class Metronome : public AbstractMetronome
{
public:
	Metronome(unsigned char timerN, unsigned char matchN);
	virtual bool CheckAndRun (unsigned int timeUs);
	virtual bool IsOver();
	virtual void Start (unsigned int timeUs);
	virtual AbstractMetronome& operator = (unsigned int uS);
	virtual bool operator > (unsigned int uS);
	virtual ~Metronome() {}
protected:
	unsigned int GetMatchVal ( unsigned int uSec);
	unsigned long matchIdBit;
	volatile unsigned long* intIdReg;
	volatile unsigned long* matchReg;
	volatile unsigned long* countReg;
};

class PWM : public AbstractPWM
{
public:
	PWM( unsigned char nPwm, unsigned int t, unsigned int d, bool IsStarted = true);
	virtual void SetD (unsigned int dy);
	virtual void SetT (unsigned int prd);
	virtual void SetTD (unsigned int prd, unsigned int dy);
	virtual void Start();
	virtual void Stop();
	virtual ~PWM() { }	
protected:
	void PinConfig(unsigned char n);
	unsigned char num;
//	unsigned long  bit;
	volatile unsigned long*  matchReg;
};




class PWM_Lim : public AbstractPWM_Lim
{
public: 
    PWM_Lim ( unsigned char nPwm, AbstractPWM* noIntPwm, unsigned long isrAddr );
	virtual void SetD (unsigned int dy);
	virtual void SetT (unsigned int prd);
	virtual void SetTD (unsigned int prd, unsigned int dy);
    virtual void Start();
    virtual void Stop();
    virtual void Goo(unsigned int n);
    virtual unsigned int GetResidue();
    virtual void IntRoutine();
    virtual ~PWM_Lim() {}
protected:
    void WorkEnable() {};
    AbstractPWM* pwm;
	unsigned long  intReset;
};



#endif

