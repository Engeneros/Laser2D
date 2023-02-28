#include <controller.h>
//E:\d2\www\2013Proj\soft\bank\Standard\Strd0\Ctl\Controller.cpp

//	double max, min;
//	double tgVal;
//	double* msr;
//	double prevMsr;
//	unsigned int* effector;
//	AbstractConvertor_D* cnv;	
#include <stdio.h>
#include <BoardDevices.h>
//E:\d2\www\2013Proj\soft\bank\Standard\Strd0\Ctl\Controller.cpp

Controller::Controller (AbstractConvertor_D* conv, double* input, unsigned int* output, double minTg, double maxTg, double iniVal )
{
	cnv = conv;
	msr = input;
	effector = output;
	min = minTg;
	max = maxTg;
	Set(iniVal);
}

void Controller::Set(double val)
{
	double v1  = (val < min )? min  
	: val;
	double v2  = ( val > max)? max : v1; 
	tgVal = cnv->GetRevers(v2);
	
//	char buf[64];
//	sprintf(buf, "S%.3f, v1 %.3f, v2 %.3f", val, v1, v2);
//	GetUARTtx1()->Send(buf);
}

double Controller::Get ()
{
	return cnv->GetValue(*msr);
}

//bool TermostatVanadat::Router()
//{ 
//	double qwants = *msr;
//	double deltaMsr;
//	double speed = 0.0;//,  axl =0.0;
////	static double vZ = 0.0, vZ2 = 0.0, sV = 0;
//	static double sV = 0.0, prevFactor = 0.0;
//	double deltaP;//, factor;
//	const double TAU = 0.9;
//	static int  shockCnt = 0;
//	static const  int SHOCK_FACTORS_NUM = 8;
//	static const double X = 50.0;
//	static const double  shockFactors  [ 16 ] = { X / 4.0 , X / 2.0, X, X,
//	X, X, X, X, 		1.0, 1.0, 1.0, 1.0,    1.0, 1.0, 1.0, 1.0};	      
//	//	1.0, 1.0, 1.0, 1.0, 		1.0, 1.0, 1.0, 1.0,    1.0, 1.0, 1.0, 1.0};	                    		
//	
////	cnt++;
//	if( qwants != 999999.9 )
//	{

//		deltaMsr = qwants  - tgVal;
//		speed = deltaMsr - prevMsr;
////		axl = speed - vZ;
//		prevMsr = deltaMsr;
////		vZ2 = vZ;
////		vZ = speed;
//		double  factor = deltaMsr * speed;
//		sV *= TAU;
//		sV += speed * (1 - TAU);
//		if (factor > 0.08  && factor >  prevFactor + 0.1 ) 
//		{
////
//			if(shockCnt >= 0 &&  shockCnt < SHOCK_FACTORS_NUM)
//				deltaP =  shockFactors [shockCnt++] * (0.3 * deltaMsr +  8.0 *  speed);
//			else
//				deltaP = 0.3 * deltaMsr +  8.0 *  speed;
////				deltaP *=shockFactors [shockCnt++];
//		}
//		else if(factor > 0.01)
//				deltaP =  0.02 * (deltaMsr + 194.0 * 1.3 * speed);	
//		else
//		{
//			deltaP =  0.02 * (deltaMsr + 194.0 * 1.15 * speed);	
//			if (shockCnt > 0)
//				shockCnt = -500.0;
//			else if( shockCnt < 0)
//				++shockCnt ;
//		}
//		
////		else
////			deltaP =  0.02 * (deltaMsr + 194.0 * 1.2 *  speed);	
//	//	deltaP =  0.02 * (deltaMsr + 194.0  * 2.0 * speed);	
//		dacVal += deltaP;// +/* 0.05 * sdp*/ + 0.00001 * sdp * sdp * sdp;//  +  0.01 * factor * factor * deltaP;

//		dacVal = (dacVal < 1.0)? 1.0 : dacVal;
//		dacVal = (dacVal > 4094.0) ? 4094.0 : dacVal;
//		 *effector =  (unsigned int ) dacVal ;//++cnt << 4 & 0xfff; //
//		prevFactor = factor;
//	}
//	return true;
//}
#include <math.h>

bool TermostatVanadat::Router()
{ 
	double qwants = *msr;
	double deltaP;
	double deltaMsr;
	double speed = 0.0;//,  axl =0.0;
	static double prevFactor = 0.0;
	static int factorCnt = 0;
	static int  relaxCnt = 0;
	static const int NFP = 700;
	static const int NRP = 50;
	static int  cnt = 0;
	char buf[128];

	if( qwants != 999999.9 )
	{
		deltaMsr = qwants  - tgVal;
		speed = deltaMsr - prevMsr;
		prevMsr = deltaMsr;
		double  factor = deltaMsr * speed;

		if (factor > 0.2  && factor >  prevFactor + 0.1 ) 
		{
			relaxCnt = 0;
			if(++factorCnt < NFP ) 
				deltaP  = 2.0 * deltaMsr + 3.0 * speed;
			else
				deltaP  = 0.4 * deltaMsr + 4.0 * speed;
				//deltaP  = 10.0 * deltaMsr + 8.0 * speed;			
		}
		else if (factor > 0.1)
			deltaP  =  0.03 * deltaMsr + 6.0 * speed;
		else
		{	
			deltaP  =  0.02 * deltaMsr + 4.0 * speed;
			if (++relaxCnt   < NRP)
				factorCnt = NFP;
			else
			{
				factorCnt = 0;	
				relaxCnt = NRP;				
			}
		}
		dacVal += deltaP;// +/* 0.05 * sdp*/ + 0.00001 * sdp * sdp * sdp;//  +  0.01 * factor * factor * deltaP;
		dacVal = (dacVal < 1.0)? 1.0 : dacVal;
		dacVal = (dacVal > 4094.0) ? 4094.0 : dacVal;
		 *effector =  (unsigned int ) dacVal ;//++cnt << 4 & 0xfff; //
		cnt++;
		sprintf (buf, "  cycle =  %d; fCnt = %d, rxCnt = %d, fx =  %.3f %c %c",
							cnt,              factorCnt,   relaxCnt,      factor,  13, 10);
		GetUARTtx0()->Send(buf);
		prevFactor = factor;
	}
	return true;
}


bool TermostatLD::Router()
{
	double qwants = *msr;
	double deltaMsr;
	double speed;
	double deltaP;
	if( qwants != 999999.9 )
	{

		deltaMsr = qwants  - tgVal;
		speed = deltaMsr - prevMsr;
		prevMsr = deltaMsr;
		deltaP =  0.05 * (deltaMsr + 194.0  * speed);
		dacVal -= deltaP;///!!!! AHTUNG inverted by Yura
		dacVal = (dacVal < 1.0)? 1.0 : dacVal;
		dacVal = (dacVal > 4094.0) ? 4094.0 : dacVal;
//		if (++cnt % 20 == 0 )
//		{
//			char buf [128];
//			sprintf (buf, " meanVal = %.3f,  tg = %.3f, delta = %.3f, dM = %.3f, dac = %.3f%c%c", 
//			qwants,  tgVal, deltaMsr, deltaP, dacVal, 13, 10);
//			GetUARTtx1()->Send(buf);
//		}
		 *effector =  (unsigned int ) dacVal ;//++cnt << 4 & 0xfff; //
	}
//	 *effector = ++cnt & 0xfff; 
	return true;
}

///////////////////
////////////////////////////
/////////////////////////////////
bool TermostatLBOPrecision::Router()
{
	double qwants = *msr;
	double deltaMsr;
	double speed;
	double deltaP;
	if( qwants != 999999.9 )
	{

		deltaMsr = qwants  - tgVal;
		speed = deltaMsr - prevMsr;
		prevMsr = deltaMsr;
		deltaP =  (0.05  / 4.0) * (deltaMsr +500.0 * speed);
		dacVal -= deltaP;
		dacVal = (dacVal < 1.0)? 1.0 : dacVal;
		dacVal = (dacVal > 4094.0) ? 4094.0 : dacVal;
		 *effector =  (unsigned int ) dacVal ;//++cnt << 4 & 0xfff; //
	}		
	return true;
}

bool TermostatLBORough::Router()
{
	double qwants = *msr;
	double deltaMsr;
	double speed;
	double deltaP;
	if( qwants != 999999.9 )
	{
		deltaMsr = qwants - tgVal;
		speed = deltaMsr - prevMsr;
		prevMsr = deltaMsr;
		deltaP =  (0.05  / 4.0)* (deltaMsr + 500.0 * speed);
		dacVal -= deltaP;
		dacVal = (dacVal < 1.0)? 1.0 : dacVal;
		dacVal = (dacVal > 4094.0) ? 4094.0 : dacVal;
		 *effector =  (unsigned int ) dacVal ;//++cnt << 4 & 0xfff; //
	}
	return true;
}

TermostatLBO::TermostatLBO(AbstractController*  ctlPrecision, AbstractController*  ctlRough)
{
	prec = ctlPrecision;
	rough = ctlRough;
	isLock = false;
}

void TermostatLBO::Set(double val)
{
//	rough->Set(val);
	prec->Set(val);
}
double TermostatLBO::Get()
{
//	double temp = meanVal[AnDvcs::AD_LBO_PR_T];
//	return (temp > 100.0 && temp < 4000.0)? prec->Get() : rough->Get();
	return  prec->Get();
}

bool TermostatLBO::Router()
{
//	double temp = meanVal[AnDvcs::AD_LBO_PR_T];
//	(temp > 100.0 && temp < 4000.0)? prec->Router() :
	prec->Router();
	return true;
}
	

