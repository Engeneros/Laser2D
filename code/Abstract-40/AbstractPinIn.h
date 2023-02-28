#ifndef ABSTRACT_PIN_IN_H
#define ABSTRACT_PIN_IN_H
//E:\d2\www\2013Proj\soft\Abstract\AbstractPinIn.h


class AbstractPinIn
{
public:	
	virtual bool IsOn () = 0;
	virtual ~AbstractPinIn(){}
};

class AbstractEncoder
{
protected:
	AbstractPinIn* contA;
	AbstractPinIn* contB;
	bool isA, isB;
	int count;
public:
	AbstractEncoder (AbstractPinIn* contactA, AbstractPinIn* contactB)
	{ 
		contA = contactA;
		contB = contactB;
		count = 0;
		isA = contA->IsOn();
		isB = contB->IsOn();
	}

	virtual void Router ()
	{
		bool aSt = contA->IsOn();
		bool bSt = contB->IsOn();
//		bool aChange = (isA != aSt)? true : false;
//		bool bChange = (isB != bSt)? true : false;
		bool front = ( isA == false && aSt == true)? true  :  false;
		if( front !=  false )
			count += (bSt == false)? -1 : 1;
		isA = aSt;
		isB = bSt;
	}
	
	virtual int GetValue()
	{
		int ret = count;
		count  = 0;
		return ret;
	}
};



#endif

