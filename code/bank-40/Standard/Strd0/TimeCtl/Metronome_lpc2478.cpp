#include <Metronome.h>
#include <lpc24xx.h>
//#include <Service.h>
//#include <dbg.h>

Metronome::Metronome(unsigned char timerN, unsigned char matchN)
{
	matchIdBit = 1 << matchN;
	isStarted = false;
	if(timerN == 0)
	{
		matchReg = &T0MR0 + matchN;	
		intIdReg = &T0IR;
		*intIdReg = matchIdBit; //clear flag
		countReg = &T0TC;
		T0CCR = 0; // timer mode
		T0MCR = 1 << 3 * matchN; //interrupt when mutch
		T0TCR =  1; // enable timer
	}
	else if (timerN == 1)
	{
		matchReg = &T1MR0 + matchN;	
		intIdReg = &T1IR;
		*intIdReg = matchIdBit; //clear flag
		countReg = &T1TC;
		T1CCR = 0; // timer mode
		T1MCR = 1 << 3 * matchN; //interrupt when mutch
		T1TCR =  1; // enable timer
	}	
	else if (timerN == 2)
	{
		matchReg = &T2MR0 + matchN;	
		intIdReg = &T2IR;
		*intIdReg = matchIdBit; //clear flag
		countReg = &T2TC;
		T2CCR = 0; // timer mode
		T2MCR = 1 << 3 * matchN; //interrupt when mutch
		T2TCR =  1; // enable timer
	}	
	else if (timerN == 3)
	{
		matchReg = &T3MR0 + matchN;	
		intIdReg = &T3IR;
		*intIdReg = matchIdBit; //clear flag
		countReg = &T3TC;
		T3CCR = 0; // timer mode
		T3MCR = 1 << 3 * matchN; //interrupt when mutch
		T3TCR =  1; // enable timer
	}	
	
}

unsigned int Metronome::GetMatchVal(unsigned int uSec)
{
	unsigned int tics = 60 * uSec;
	unsigned int cnt = *countReg;
	unsigned int t1 = 0xffffffff - cnt; 
	unsigned int mVal = (t1 > tics)? cnt + tics : tics - t1;
	return  mVal;
}

void Metronome::Start(unsigned int timeUs)
{
	if(isStarted == false)
	{
		*matchReg = GetMatchVal(timeUs);
		*intIdReg = matchIdBit;
		isStarted = true;
	}
}

bool Metronome::IsOver()
{
	bool ret;
	if(isStarted == true)
	{
//		IOPIN0 ^= 1 << 28;
		if((*intIdReg  & matchIdBit) != 0)
		{
//			IOPIN0 ^= 1 << 25;
			*intIdReg = matchIdBit;
			isStarted = false;
			ret = true;
		}
		else
			ret = false;
	}
	else 
		ret = true;
	return ret;		
}

bool Metronome::CheckAndRun(unsigned int timeUs)
{
	bool ret = IsOver()	;
	Start ( timeUs);		
	return ret;
}

//////////////////////////////////////////////////////////////////////////////////////
//PWM::PWM(unsigned char nPwm, unsigned int t, unsigned int d, bool IsStarted)
//{
//	num = nPwm;
//	PinConfig(num);
//	PWMTCR = 2;
////	PWMTCR |= 2; // reset on match 0 registr
//	PWMPCR = 1 << (8 +num);
//	matchReg = ( num < 4)? &PWMMR0 + num : &PWMMR4 + (num - 4);	
//	SetTD(t, d);
//    if( IsStarted )
//        Start();
//    else
//        Stop();
//}

//void PWM::PinConfig(unsigned char n)
//{
//	if( n== 2)
//		PCfg(0, 7, 2);
//	else if (n == 5)
//		PCfg(0, 21, 1);
//}

//void PWM::SetD(unsigned int dy)
//{
//	*matchReg = dy;
//	PWMLER  = 1 << num;
//}

//void PWM::SetT(unsigned int prd)
//{
//	PWMMR0 = prd;
//	PWMLER = 1;
//}

//void PWM::SetTD(unsigned int prd, unsigned int dy)
//{
//	*matchReg = dy;
////	PWMMR5 = dy;
//	PWMMR0 = prd;
//	PWMLER  = 1 | ( 1 << num );
//}

//void PWM::Start()
//{
//	PWMTCR = 9;
//}

//void PWM::Stop()
//{
//	PWMTCR  = 8;
//}


////////////////////////////////////////////////////////////////////////////////////////
//PWM_Lim::PWM_Lim(unsigned char nPwm, AbstractPWM* noIntPwm,unsigned long isrAddr) 
//{
//	pwm =  noIntPwm;
//	if(nPwm < 4)        
//		intReset = 1 << nPwm;
//	else
//		intReset = 1 << (4 + nPwm);
//    VICVectAddr8 = isrAddr;
//	VICVectCntl8 = 0x20 | 8;     // use it for PWM Interrupt
//    VICIntEnable |= 0x00000100;  // Enable Timer0 Interrupt
//	PWMMCR =  2 | (1 << nPwm * 3);
//    PWMIR = 0x70f;
//}

//void PWM_Lim::IntRoutine()
//{
////	DbSet(DB_R);
//   (--resi > 0)? WorkEnable() : Stop();
//   PWMIR =  intReset;
////	DbClr(DB_R);
//   VICVectAddr = 0;
//}

//void PWM_Lim::Goo(unsigned int n)
//{
//    resi = n;
////	DbSet(DB_R);

//    Start();
//}

//unsigned int PWM_Lim::GetResidue()
//{
//    return resi;
//}

//void PWM_Lim::SetD(unsigned int dy)
//{
//	pwm->SetD(dy);
//}

//void PWM_Lim::SetT(unsigned int prd)
//{
//	pwm->SetT(prd);
//}

//void PWM_Lim::SetTD(unsigned int prd, unsigned int dy)
//{
//	for( int i = 0; i < 50; ++i)
//	{
////		DbSet(DB_G);
////		DbClr(DB_G);
//	}
//        pwm->SetTD(prd, dy);
//}

//void PWM_Lim::Start()
//{
//	PWMTCR = 9;
//}

//void PWM_Lim::Stop()
//{
//	PWMTCR  = 8;
//}





