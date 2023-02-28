#include <LogicCtl.h>
//E:\d2\www\2013Proj\soft\bank\Standard\Strd0\Ctl\LogicCtl.cpp

ShutterCtl:: ShutterCtl(AbstractPinOut* control, AbstractPinIn* detector)
{
	pCtl = control;
	pDtc = detector;
	dtCnt = 0;
}

bool ShutterCtl::IsOn()
{
	return isOpen;
}

void ShutterCtl::Clear()
{
	if(dtCnt == 0 && isOpen != false)
	{
		pCtl->Set();
		dtCnt = DEAD_TIME;
		isOpen = false;
	}
}

void ShutterCtl::Set()
{
	if(dtCnt == 0 && isOpen == false)
	{
		pCtl->Set();
		dtCnt = DEAD_TIME;
		isOpen = true;
	}
}

void ShutterCtl::Toggle( )
{
	if(dtCnt == 0)
	{ 
		pCtl->Set();
		dtCnt = DEAD_TIME;
		isOpen = !isOpen;
	}
}

void ShutterCtl::Send (bool state)
{
	if(dtCnt == 0 && isOpen != state)
	{
		pCtl->Set();
		dtCnt = DEAD_TIME;
		isOpen = state;
	}
}	

bool ShutterCtl::Router()
{
	bool ret;
	if(dtCnt > 0)
	{
		--dtCnt;
		ret = false;
	}
	else 
	{
		isOpen = pDtc->IsOn();
		pCtl->Clear();
		ret = true;
	}
	return ret;
}

//class PowerCtl :  public AbstractPinOut,  AbstractCtl
//{
//public:
//	PowerCtl ( AbstractPinOut* control, AbstractPinIn* detector, double* current, AbstractPinOut* shutter);
//	virtual bool IsOn() ;
//	virtual void Clear() ;
//	virtual void  Set() ;
//	virtual void Toggle();
//	virtual void Send(bool state);
//	virtual bool Router();	
//	virtual ~PowerCtl () {}
//private:
	//	double* ldCur;
	//	AbstractPinOut* shtr;
	//	AbstractPinOut* pCtl;
	//	AbstractPinIn* pDtc;
	//	bool isPwr;
	//	bool mustOn;
	//	bool mustOff;
	//	static const int DEAD_TIME = 5;
	//	int dtCnt;	
//};

PowerCtl::PowerCtl(AbstractPinOut* control, AbstractPinIn* detector, double* current, AbstractPinOut* shutter)
{
	pCtl = control;
	pDtc = detector;
	ldCur = current;
	shtr = shutter;
	mustOn = mustOff = false;
//	if(*ldCur > 1000.0)
//	{
//		isPwr = true;
//		pCtl->Set();
//	}
//	else
//	{
//		isPwr = pDtc->IsOn();
//		pCtl->Send(isPwr);
//	}
		isPwr = false;
		pCtl->Clear();
	dtCnt = 0;
}

bool PowerCtl::IsOn()
{
	return isPwr;
}

void PowerCtl::Clear()
{
	mustOn = false;
	if(isPwr != false)
	{
		mustOff = true;
		isPwr = false;
	}
}

void PowerCtl::Set()
{
	mustOff = false;
	if(isPwr == false)
	{
		mustOn = true;
		isPwr = true;
	}
}

void PowerCtl::Send( bool state)
{
	if(state != isPwr)
	{
		mustOn = state;
		mustOff = !state;
	}
}

void PowerCtl::Toggle()
{
}

#include <boardDevices.h>
bool PowerCtl::Router()
{
	bool ret;
	if(dtCnt > 0)
	{
		--dtCnt;
		ret = false;
	}
	else
	{	
		ret = true;
		if(mustOn != false)
		{
			pCtl->Set();
			dtCnt = DEAD_TIME;
			mustOn = false;
		}
		else if (mustOff != false)
		{
			shtr->Clear();
			if(*ldCur < 500.0)
			{
				pCtl->Clear();
				dtCnt = DEAD_TIME;
				mustOff = false;
			}
//			else
	//			isPwr = true;
		}
		else
			isPwr = pDtc->IsOn();	
	}
	return ret;
}



