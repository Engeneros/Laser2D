#include <controller-E.h>
//E:\d2\www\2013Proj\soft\draft\0040binaryRack=17.10.2016\sw\puC\puC40_0\code\bank-40\Standard\Strd0\Ctl\Controller-E.cpp	
#include <stdio.h>
#include <BoardDevices.h>
#include <Constants40.h>

Controller_E::Controller_E (AbstractConvertor_D* conv, double* input, unsigned short* output, double minTg, double maxTg, double iniVal ) :
	cnv (conv),  msr (input), effector( output),  min (minTg), max(maxTg),  prevMsr (*input), isStab (true)
{
	Set(iniVal);
}

void Controller_E::Set(double val)
{
	double v1  = (val < min )? min : val;
	double v2  = ( val > max)? max : v1; 
	tgVal = cnv->GetRevers(v2);
	isStab = true;
//	static int cnt  = 0;
//	char buf [128];
//	if (++cnt == 20)
//	{
//		sprintf (buf, " val = %.3f, target = %.3f, v1 = %.3f, v2 = %.3f%c%c", val, tgVal, v1 , v2, 13, 10);  
//		GetUARTtx0()->Send(buf);
//		cnt = 0;
	//}
}

double Controller_E::Get ()
{
	return   cnv->GetValue(*msr);
}

void Controller_E::SetLeftRef(double refVal)
{
	cnv->AddPointLeft( *msr, refVal);
}

void Controller_E::SetRightRef(double refVal)
{
	cnv->AddPointRight( *msr, refVal);
}

void Controller_E::Calibrate()
{
	cnv->Calibrate();
}
/////////////

DirectCurrCtl::DirectCurrCtl (AbstractConvertor_D* conv, unsigned short* output, double minTg, double maxTg, double iniVal,
AbstractPinOut* en ) :
	cnv (conv),  effector( output),  min (minTg), max(maxTg),  isStab (true), currEn(en)
{
	Set(iniVal);
	currEn->Clear();
	tgSlow = tgVal;
}

void DirectCurrCtl::Set(double val)
{
	double v1  = (val < min )? min : val;
	double v2  = ( val > max)? max : v1; 
	tgVal = cnv->GetRevers(v2);

	isStab = true;
	if (val > 0.1)
		currEn->Set();
}

double DirectCurrCtl::Get ()
{
	return   cnv->GetValue((double) *effector);
}

void DirectCurrCtl::SetLeftRef(double refVal)
{
	cnv->AddPointLeft( (double) *effector, refVal);
}

void DirectCurrCtl::SetRightRef(double refVal)
{
	cnv->AddPointRight((double) *effector, refVal);
}

void DirectCurrCtl::Calibrate()
{
	cnv->Calibrate();
}

bool DirectCurrCtl::Router()
{
	static const double step = 8.0;
	static const double delta = 4.0 * step;
	bool ret;
	if(isStab != false)
	{
		tgSlow = ( tgVal - (double) *effector > delta)? (tgSlow + step) : (((double) *effector - tgVal > delta)? (tgSlow - step) : tgVal);
		*effector = (unsigned int) tgSlow;
		ret =true;
	}
	else ret = false;
	return ret;	
}

//#include <math.h>
#include <stdio.h>
#include <boardDevices.h>
bool TstatFan::Router()
{
	bool ret;
	double qwants = *msr;
	double speed, deltaMsr, deltaP ;
	if( *cur > 4000.0 ||  qwants == ERR_VAL  )
	{
		dacVal =  4094.0;
		 *effector =  4094;		
		ret = true;
	}		
	else if (isStab != false)
	{
		deltaMsr =  tgVal - qwants;//+  ->hot
		if  ( cnv->GetValue(qwants) > 3000.0 )
		{
			dacVal =  4094.0;
			*effector =  4094;		
		}
		else
		{
			double speed = prevMsr - qwants ;//+  -> T rise
			double deltaP  =   0.00007 * deltaMsr + 5.0 * speed;
			dacVal += deltaP;// +/* 0.05 * sdp*/ + 0.00001 * sdp * sdp * sdp;//  +  0.01 * factor * factor * deltaP;
			dacVal = (dacVal < 2000.0)? 2000.0 : dacVal;
			dacVal = (dacVal > 4094.0) ? 4094.0 : dacVal;
			 *effector =  4095;//(unsigned int ) dacVal ;//++cnt << 4 & 0xfff; //
		}
		prevMsr = qwants;
		ret = true;
	}
	else
		ret = false;
//	static signed char cnt = 100;
//	if (--cnt <= 0)
//	{
//		char buff[64];
//		sprintf (buff, "delta = %.2f,   speed = %.6f,    dP = %.3f    dacVal=%.2f", deltaMsr, speed, deltaP, dacVal);  
//		uartTx0.Send(buff);
//		cnt = 100;
//	}
	return ret;
}


bool TstatLD::Router()
{
	bool ret;
	if(isStab != false)
	{
		double qwants = *msr;
		double deltaMsr;
		double speed;
		double deltaP;
		if( qwants != ERR_VAL  && isStab != false)
		{
			deltaMsr = qwants  - tgVal;
			speed = deltaMsr - prevMsr;
			prevMsr = deltaMsr;
			deltaP =  0.01 * deltaMsr + 15.0  * speed;  //#13!
			dacVal -= deltaP; //!!!! AHTUNG inverted by Yura
			dacVal = (dacVal < 1.0)? 1.0 : dacVal;
			dacVal = (dacVal > 65534.0) ? 65534.0 : dacVal;
			 *effector =  (unsigned int ) dacVal ; //++cnt << 4 & 0xfff; //
		} 
		ret = true;
	}
	else 
		ret =false;
	return ret;
}

PowerPin::PowerPin ( AbstractPinOut* effector,AbstractController_E* currCtlA,  AbstractController_E* currCtlB, double* currentA,  double* currentB,
AbstractPinOut* luminaEnA, AbstractPinOut* luminaEnB, AbstractPinOut* powerIndicator, AbstractPinIn* powerButton)
: pin(effector), cuCtlA (currCtlA),  cuCtlB(currCtlB),  currA (currentA), currB(currentB), mustOff(false),  
currEnA(luminaEnA), currEnB(luminaEnB), offCnt(0),  indicCnt (0),  buttCnt (), dacOff (true),  enbOff (true), pwrOff (true), pwLED (powerIndicator), pwBt (powerButton)
{
	pin->Clear();
	pwLED->Clear();
}

void PowerPin::Clear()
{
	mustOff = true;
	cuCtlA->Set ( 0.0 );
	cuCtlB->Set (0.0);
}

void  PowerPin::Set()
{
	pin->Set();
	mustOff =  false;
	dacOff = enbOff = pwrOff = false;
	pwLED->Set();
} 

bool  PowerPin::Router()
{
	if( mustOff != false )
	{
		if(enbOff != false)
		{ 
			if(--offCnt <= 0)
			{
				vd11Yellow.Toggle();
				pin->Clear();
				offCnt = 0;
				mustOff = false;
				pwrOff = enbOff =dacOff = true;
				pwLED->Clear();
			}
		}
		else if(dacOff != false)
		{
			if(--offCnt <= 0)
			{
				currEnA ->Clear();
				currEnB->Clear();
				offCnt = SLEEP_TIME;
				enbOff = true;
				pwLED->Clear();
			}
		}
		else if( cuCtlA->Get() < SAFE_A_CURRENT  && cuCtlB->Get() < SAFE_A_CURRENT ) 
		{
			cuCtlA->SetDAC(0);
			cuCtlB->SetDAC(0);
			offCnt = SLEEP_TIME;
			dacOff = true;
		}
		else if (++indicCnt % 20 == 0)
			pwLED->Toggle();
	}
	if(pwBt->IsOn() != false)
	{
		if (++buttCnt > 800)
		{
			buttCnt = 0;
			Clear();
		}
	}
	else
		buttCnt = 0;
	
	return true;
}

