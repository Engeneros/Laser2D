#include <controller-C.h>
//E:\d2\www\2013Proj\soft\bank\Standard\Strd0\Ctl\Controller-C.cpp	
#include <stdio.h>
#include <BoardDevices.h>
#include <Constants.h>

Controller_C::Controller_C (AbstractConvertor_D* conv, double* input, unsigned int* output, double minTg, double maxTg, double iniVal )
{
	cnv = conv;
	msr = input;
	effector = output;
	min = minTg;
	max = maxTg;
	Set(iniVal);
}

void Controller_C::Set(double val)
{
	double v1  = (val < min )? min  
	: val;
	double v2  = ( val > max)? max : v1; 
	tgVal = cnv->GetRevers(v2);
//	static int cnt  = 0;
//	char buf [128];
//	if (++cnt == 20)
//	{
//		sprintf (buf, " val = %.3f, target = %.3f, v1 = %.3f, v2 = %.3f%c%c", val, tgVal, v1 , v2, 13, 10);  
//		GetUARTtx0()->Send(buf);
//		cnt = 0;
	//}
}

double Controller_C::Get ()
{
	return cnv->GetValue(*msr);
}

void Controller_C::SetLeftRef(double refVal)
{
	cnv->AddPointLeft( *msr, refVal);
}

void Controller_C::SetRightRef(double refVal)
{
	cnv->AddPointRight( *msr, refVal);
}

void Controller_C::Calibrate()
{
	cnv->Calibrate();
}


#include <math.h>

//////////////24.03T2
//					bool TermostatVanadat::Router()
//					{ 
//						double qwants = *msr;
//						double deltaP;
//						double deltaMsr;
//						double speed = 0.0;//,  axl =0.0;
//						static double prevFactor = 0.0;
//						static int factorCnt = 0;
//						static int  relaxCnt = 0;
//						static const int NFP = 50;
//						static const int NRP = 50;
//					//	static int  cnt = 0;
//						//char buf[128];

//						if( qwants != 999999.9 )
//						{
//							deltaMsr = qwants  - tgVal;
//							speed = deltaMsr - prevMsr;
//							prevMsr = deltaMsr;
//							double  factor = deltaMsr * speed;

//					//		if (factor > 0.2  && factor >  prevFactor + 0.1 ) 
//					//		{
//					//			relaxCnt = 0;
//					////			if(++factorCnt < NFP )
//					////			//	deltaP  =  2.5 * deltaMsr + 20.0 * speed;//0.2C
//					////			else
//					//	//			deltaP  =  0.3 * deltaMsr + 15.0 * speed;
//					//			deltaP  =  0.2 * deltaMsr + 15.0 * speed;
//					//		}
//					//		else if (factor > 0.1)
//					//			deltaP  =  0.2 * deltaMsr + 15.0 * speed;
//					//		else
//					//		{	
//								deltaP  =  0.1 * deltaMsr + 15.0 * speed;
//					//			if (++relaxCnt   > NRP)
//					//	//			factorCnt = NFP;
//					//		//	else
//					//			{
//					//				factorCnt = 0;	
//					//				relaxCnt = NRP;				
//					//			}
//					//		}
//							dacVal += deltaP;// +/* 0.05 * sdp*/ + 0.00001 * sdp * sdp * sdp;//  +  0.01 * factor * factor * deltaP;
//							dacVal = (dacVal < 1.0)? 1.0 : dacVal;
//							dacVal = (dacVal > 4094.0) ? 4094.0 : dacVal;
//							 *effector =  (unsigned int ) dacVal ;//++cnt << 4 & 0xfff; //
//					//		cnt++;
//					//		sprintf (buf, "  cycle =  %d; fCnt = %d, rxCnt = %d, fx =  %.3f %c %c",
//					//							cnt,              factorCnt,   relaxCnt,      factor,  13, 10);
//					//		GetUARTtx0()->Send(buf);
//							prevFactor = factor;
//						}
//						return true;
//					}


//					bool TermostatLD::Router()
//					{
//						double qwants = *msr;
//						double deltaMsr;
//						double speed;
//						double deltaP;
//						if( qwants != 999999.9 )
//						{

//							deltaMsr = qwants  - tgVal;
//							speed = deltaMsr - prevMsr;
//							prevMsr = deltaMsr;
//							deltaP =  0.05 * (deltaMsr + 194.0  * speed);
//							dacVal -= deltaP;///!!!! AHTUNG inverted by Yura
//							dacVal = (dacVal < 1.0)? 1.0 : dacVal;
//							dacVal = (dacVal > 4094.0) ? 4094.0 : dacVal;
//					//		if (++cnt % 20 == 0 )
//					//		{
//					//			char buf [128];
//					//			sprintf (buf, " meanVal = %.3f,  tg = %.3f, delta = %.3f, dM = %.3f, dac = %.3f%c%c", 
//					//			qwants,  tgVal, deltaMsr, deltaP, dacVal, 13, 10);
//					//			GetUARTtx1()->Send(buf);
//					//		}
//							 *effector =  (unsigned int ) dacVal ;//++cnt << 4 & 0xfff; //
//						}
//					//	 *effector = ++cnt & 0xfff; 
//						return true;
//					}

//					///////////////////
//					////////////////////////////
//					/////////////////////////////////
//					bool TermostatLBOPrecision::Router()
//					{
//						double qwants = *msr;
//						double deltaMsr;
//						double speed;
//						double deltaP;
//						if( qwants != 999999.9 )
//						{

//							deltaMsr = qwants  - tgVal;
//							speed = deltaMsr - prevMsr;
//							prevMsr = deltaMsr;
//							deltaP =  (0.05  / 4.0) * (deltaMsr +500.0 * speed);
//							dacVal -= deltaP;
//							dacVal = (dacVal < 1.0)? 1.0 : dacVal;
//							dacVal = (dacVal > 4094.0) ? 4094.0 : dacVal;
//							 *effector =  (unsigned int ) dacVal ;//++cnt << 4 & 0xfff; //
//						}		
//						return true;
//					}


//					/////////////////




bool TstatVanadat::Router()
{ 	
	*msr = tgVal;
	double qwants = *msr;
//	static double prevFactor = 0.0;
//	static int factorCnt = 0;
//	static int  relaxCnt = 0;
//	static const int NFP = 50;
//	static const int NRP = 50;
	if( qwants != ERR_VAL )
	{
		double deltaMsr = qwants  - tgVal;
		double speed = deltaMsr - prevMsr;
		prevMsr = deltaMsr;
//		double  factor = deltaMsr * speed;
//					//		if (factor > 0.2  && factor >  prevFactor + 0.1 ) 
//					//		{
//					//			relaxCnt = 0;
//					////			if(++factorCnt < NFP )
//					////			//	deltaP  =  2.5 * deltaMsr + 20.0 * speed;//0.2C
//					////			else
//					//	//			deltaP  =  0.3 * deltaMsr + 15.0 * speed;
//					//			deltaP  =  0.2 * deltaMsr + 15.0 * speed;
//					//		}
//					//		else if (factor > 0.1)
//					//			deltaP  =  0.2 * deltaMsr + 15.0 * speed;
//					//		else
//					//		{	
				////===double deltaP  =   0.1 * deltaMsr + 15.0 * speed;===///
		double deltaP  =   0.03 * deltaMsr + 6.0 * speed;
//					//			if (++relaxCnt   > NRP)
//					//	//			factorCnt = NFP;
//					//		//	else
//					//			{
//					//				factorCnt = 0;	
//					//				relaxCnt = NRP;				
//					//			}
//					//		}
		dacVal += deltaP;// +/* 0.05 * sdp*/ + 0.00001 * sdp * sdp * sdp;//  +  0.01 * factor * factor * deltaP;
		dacVal = (dacVal < 1.0)? 1.0 : dacVal;
		dacVal = (dacVal > 65534.0) ? 65534.0 : dacVal;
		 *effector =  (unsigned int ) dacVal ;//++cnt << 4 & 0xfff; //
//							prevFactor = factor;
	}
	return true;
}

bool TstatFan::Router()
{
	double qwants = *msr;
	if( *cur > 20000.0  )
	{
		dacVal =  65534.0;
		 *effector =  65535;		
	}		
	if( qwants != ERR_VAL )		
	{
		double deltaMsr = qwants - tgVal;
		if  ( cnv->GetValue(qwants) > 33.0 )
		{
			dacVal =  65534.0;
			*effector =  65535;		
		}
		else
		{
			double speed = deltaMsr - prevMsr;
			double deltaP  =   0.1 * deltaMsr + 15.0 * speed;
			dacVal += deltaP;// +/* 0.05 * sdp*/ + 0.00001 * sdp * sdp * sdp;//  +  0.01 * factor * factor * deltaP;
			dacVal = (dacVal < 1.0)? 1.0 : dacVal;
			dacVal = (dacVal > 65534.0) ? 65534.0 : dacVal;
			 *effector =  (unsigned int ) dacVal ;//++cnt << 4 & 0xfff; //
		}
		prevMsr = deltaMsr;
	}
	return true;
}


bool CurrCtlLD::Router() // !!!modify
{
	double qwants = *msr;
	double deltaMsr;
	const double DELTA = 6000.0;
	const double STEP = 100.0;
	double minBrd = tgVal - DELTA;
	double maxBrd = tgVal + DELTA;
	minBrd = (minBrd < 1.0)? 1.0 : minBrd;
	maxBrd = (max >  65534.0)? 65534.0 : maxBrd;
	if ( tgSlow <  minBrd )
	{
		tgSlow +=STEP;
		dacVal = (tgSlow > dacVal )? tgSlow : dacVal;
		*effector =   (unsigned int ) dacVal ;//++cnt << 4 & 0xfff; //
	}
	else	if ( tgSlow >  maxBrd )
	{
		tgSlow -=STEP;
		dacVal = (tgSlow < dacVal )? tgSlow : dacVal;
		*effector =   (unsigned int ) dacVal ;//++cnt << 4 & 0xfff; //
	}
	else if( qwants !=  ERR_VAL )
	{
		deltaMsr = qwants  - tgVal;
		dacVal -= deltaMsr * 0.006;

		dacVal = (dacVal < minBrd)? minBrd : dacVal;
		dacVal = (dacVal > maxBrd)?  maxBrd : dacVal;
		*effector =   (unsigned int ) dacVal;//++cnt << 4 & 0xfff; //
	}
//	static int cnt  = 0;
//	char buf [64];
//	if (++cnt == 20)
//	{
//		sprintf (buf, " tg = %.3f, eff = %d", tgVal, *effector);  
////		GetUARTtx0()->Send(buf);
//		cnt = 0;
//	}
//	dacVal = tgVal;
//	*effector =   (unsigned int ) dacVal;
	return true;
}


bool TstatLD::Router()
{
	double qwants = *msr;
	double deltaMsr;
	double speed;
	double deltaP;
	if( qwants != ERR_VAL )
	{

		deltaMsr = qwants  - tgVal;
		speed = deltaMsr - prevMsr;
		prevMsr = deltaMsr;
//		deltaP =  0.1 * deltaMsr + 8.0  * speed;  //#13!
		deltaP =  0.025 * deltaMsr + 6.0  * speed;  //#13!
		dacVal -= deltaP;///!!!! AHTUNG inverted by Yura
		dacVal = (dacVal < 1.0)? 1.0 : dacVal;
		dacVal = (dacVal > 65534.0) ? 65534.0 : dacVal;
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
bool TstatLBO::Router()
{
	*msr = tgVal;
	double qwants = *msr;
	double deltaMsr;
	double speed;
	double deltaP;
	if( qwants != 999999.9 )
	{

		deltaMsr = qwants  - tgVal;
		speed = deltaMsr - prevMsr;
		prevMsr = deltaMsr;
		deltaP =  (0.05  / 4.0) * (deltaMsr +850.0 * speed);
		dacVal -= deltaP;
		dacVal = (dacVal < 1.0)? 1.0 : dacVal;
		dacVal = (dacVal > 65534.0) ? 65534.0 : dacVal;
		 *effector =  (unsigned int ) dacVal ;//++cnt << 4 & 0xfff; //
	}		
	return true;
}

