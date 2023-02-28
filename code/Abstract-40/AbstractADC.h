#ifndef ABSTRACT_ADC_H
#define ABSTRACT_ADC_H

class AbstractADC 
{
protected:
	unsigned int samples;
	int summ;
public:
	AbstractADC() : samples(0), summ(0) {}
	virtual void Start() = 0;
	virtual void Stop() = 0;
	//virtual int operator = ( AbstractADC& )  
	virtual int Get()	
	{  
		int ret;
		switch (samples)
		{ 
			case 1: ret = summ;
			break;
			case 0 :  ret = -1; 
			break;
			default : ret = summ / samples;
		}
		summ = samples = 0;
		return ret;
	}
	virtual AbstractADC& operator ++ () = 0;
	virtual void Accumulate ( ) = 0;
	virtual unsigned int GetNSamp ( ) {return samples;}
	virtual unsigned int GetSumm ( ) {return summ;}
	virtual ~AbstractADC(){}
};

class AdcStub : public AbstractADC
{
public: 
	AdcStub (){}
	virtual void Start() {}
	virtual void Stop() {}
	virtual AbstractADC& operator ++ () {return *this;}	
	virtual void Accumulate () {}
	virtual ~AdcStub(){}
};



#endif
