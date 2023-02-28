#include <BoardDevices.h>
#include <Service.h>
#include <Metronome.h>
#include <i2chw.h>
#include <i2Cin.h>
#include <I2Cout.h>
#include <PinIn.h>
#include <PinOut.h>
#include <BuffIn.h>
#include <BuffOut.h>
#include <UART.h>
#include <LPC214x.h>
#include <Constants40.h>
#include <Controller-e.h>

static Metronome m00(0, 0);
static Metronome m01(0, 1);
static Metronome m02(0, 2);
static Metronome m03(0, 4);

AbstractMetronome& tRef0  = m00;
AbstractMetronome& tRef1  = m01;
AbstractMetronome& tRef2  = m02;
AbstractMetronome& tRef3  = m03;

void DelayMs(unsigned int ms)
{
	m00.Start(1000 * ms) ;
	while ( m00.IsOver() == false)
	{
	}
}

void DelayUs(unsigned int us)
{	
	m00.Start(us) ;
	while ( m00.IsOver() == false)
	{
	}
}
///===========================================================
static  I2Chw  i2cBus (1);
static AT24C256in  memRd256 (&i2cBus, 0x50);
static AT24C256out  memWr256 (&i2cBus, 0x50);

AbstractMemoryIn& memReader = memRd256;
AbstractMemoryOut&  memWriter = memWr256;

static PinOut vd11Y (1, 31);//(1, 25);//
static PinOut vd10G (1, 30);// (1, 24);//

AbstractPinOut& vd10Green = vd10G; 
AbstractPinOut& vd11Yellow =  vd11Y;

static PinOut_inv vt8 (0, 15);
static PinOut_inv vt9 (0, 16);

AbstractPinOut& vt8EnableA = vt8;
AbstractPinOut& vt9EnableB = vt9;

#include <stdio.h>

static PinIn_inv  pi1 (1, 26);
static PinIn_inv  pi2 (1, 25);
static PinIn_inv  pi3 (1, 24);
static PinIn_inv  pi4 (1, 23);

AbstractPinIn&  conf1 = pi1;
AbstractPinIn&  conf2 =  pi2;
AbstractPinIn&  conf3 =  pi3;
AbstractPinIn&  conf4 = pi4;

static PinIn_inv pbt (0,2);
static PinOut_inv pLed (0, 13);
 
//AbstractPinIn& powrBut = pbt;
//AbstractPinOut& powerLed  = pLed;

///===========================================================

__irq void UART0_Isr(void);
__irq void UART1_Isr(void);
static UART uart0 (0);
static UART uart1 (1);
static BuffOut bo0  (&uart0, 128, (unsigned long) UART0_Isr);
static BuffOut bo1  (&uart1, 512, (unsigned long) UART1_Isr);
static BuffInTxt bi0  (&uart0,  128, 13, (unsigned long) UART0_Isr);
static BuffInTxt bi1  (&uart1,  128, 13, (unsigned long) UART1_Isr);

AbstractBuffIn& uartRx0 = bi0;
AbstractBuffIn& uartRx1 = bi1;
AbstractBuffOut& uartTx0  = bo0;
AbstractBuffOut& uartTx1 = bo1;

__irq void UART0_Isr(void)
{		
	unsigned short iSrc = U0IIR & 0xf;
	
	if ( ( iSrc == 4 ) || ( iSrc == 0xc )  ) 	
	{
		uartRx0.Router();
	}
	else if ( iSrc == 2 )	
		uartTx0.Router();
	else if ( iSrc == 6 )
		unsigned long tmp = U0LSR;	
//	IOCLR1 = 1 << 10;
	VICVectAddr = 0;
}

__irq void UART1_Isr(void)
{	
	unsigned short iSrc = U1IIR & 0xf;
	if ( ( iSrc == 4 ) || ( iSrc == 0xc )  ) 	
		uartRx1.Router();
	else if ( iSrc == 2 )	
		uartTx1.Router();
	else if ( iSrc == 6 )
		unsigned long tmp = U1LSR;
	VICVectAddr = 0;
}

//static const unsigned char ADC_NUM_SSP1 = 8;


static double tRadADCavg = ERR_VAL;

static double iAADCavg = ERR_VAL;
static double tAADCavg = ERR_VAL;
static double uAADCavg = ERR_VAL;
static double pAADCavg = ERR_VAL;

static double iBADCavg = ERR_VAL;
static double tBADCavg = ERR_VAL;
static double uBADCavg = ERR_VAL;
static double pBADCavg = ERR_VAL;

static const unsigned char N_SPI0_DAC = 4;
static AbstractDAC* dacs [ N_SPI0_DAC ] = {&dacIa, &dacIb, &dacTa, &dacTb};

/////
static unsigned short fanDAdata = 0;

static unsigned short iADAdata = 0;
static unsigned short tADAdata = 0x7fff;

static unsigned short iBDAdata = 0;
static unsigned short tBDAdata = 0x7fff;
static  unsigned short* dacSPI0Data[N_SPI0_DAC ] = {&iADAdata, &iBDAdata, &tADAdata,  &tBDAdata};

/////////////////////spi
#include <lpc2148_SPI.h>
static SSP ssp2447 (SPICfg  (32, 200, CLK_LOW,  CLK_FIRST));
static SSP ssp5592 (SPICfg  (16, 200, CLK_HIGH,  CLK_FIRST));
static SPI 	spi5662 (SPICfg   (24, 2,  CLK_LOW, CLK_SECOND));
//CLK_HIGH, CLK_SECOND) ); //CLK_LOW,  CLK_FIRST));  //CLK_LOW, CLK_SECOND)); //
//////////////////adc
static AdcStub adS;
AbstractADC& stubAd = adS;

#include <Ltc2447.h>
static PinOut da26cs (1, 22);

static Ltc2447  da26_0 (&da26cs, &ssp2447, 0);
static Ltc2447  da26_1 (&da26cs, &ssp2447, 1);
static Ltc2447 da26_2 (&da26cs, &ssp2447, 2, false, false);

AbstractADC& tLda = da26_0;
AbstractADC& tLdb = da26_1;
AbstractADC& tRada = da26_2;

#include <ad5592.h>
static PinOut  da24cs(0, 20);
//AD5592Device::AD5592Device (AbstractPinOut* chipSel,  AbstractSpi* interface, unsigned char dacChan, unsigned char adcChan)
static AD5592Device   da24  (&da24cs,  &ssp5592, 0x40, 0x3f);
static AD5592DacCh  da24_6 (6, &da24);
static AD5592adcCh   da24_0 (0, &da24, &da24_6, &fanDAdata);
static AD5592adcCh   da24_1 (1, &da24, &da24_6, &fanDAdata);
static AD5592adcCh   da24_2 (2, &da24, &da24_6, &fanDAdata);
static AD5592adcCh   da24_3 (3, &da24,&da24_6, &fanDAdata);
static AD5592adcCh   da24_4 (4, &da24, &da24_6, &fanDAdata);
static AD5592adcCh   da24_5 (5, &da24, &da24_6,&fanDAdata);

AbstractADC& iLda = da24_0;
AbstractADC& iLdb = da24_2;
AbstractADC& uLda = da24_1;
AbstractADC& uLdb = da24_3;
AbstractADC& pLda = da24_4;
AbstractADC& pLdb = da24_5;
AbstractDAC& fanDAC = da24_6;


#include <ad5662_1.h>
static PinOut da20Cs (1, 18);
static PinOut da21Cs (1, 19);
static PinOut da22Cs (1, 16);
static PinOut da23Cs (1, 17);

static AD5662 da20 (&da20Cs, &spi5662);
static AD5662 da21 (&da21Cs, &spi5662);
static AD5662 da22 (&da22Cs, &spi5662);
static AD5662 da23 (&da23Cs, &spi5662);


AbstractDAC& dacIa = da22 ;
AbstractDAC& dacIb =  da23;
AbstractDAC& dacTa = da20;
AbstractDAC& dacTb = da21;

//					//////////////convertors
#include <Convertor-D.h>
//LineConvertor_D ( AbstractMemoryIn* memoryIn, AbstractMemoryOut* memoryOut,
//	unsigned int memAddr, const char* headerStr,
//	double mini_X, double maxi_X, double mini_Y, double maxi_Y,
//	double x0, double x1, double y0, double y1);

	//	I_A,
	//	I_B,
	//	T_A,
	//	T_B,
	//	U_A,
	//	U_B,
	//	P_A,
	//	P_B,
//	T_R,
//	POWER_SUP,
//	MODULES_NUM

static LineConvertor_D c_rada (&memReader, &memWriter, ADDR_RAD_T_ADC_A, "RTa",  0.0, 1000000.0, -100.0, 100.0,
186518.0, 191325.0, 36.0, 0.0);

static LineConvertor_D c_tlda (&memReader, &memWriter, ADDR_LD_T_ADC_A, "LTa",  0.0, 1000000.0, -100.0, 100.0,
186518.0, 191325.0, 0.0, 36.0);
static LineConvertor_D c_tldb (&memReader, &memWriter, ADDR_LD_T_ADC_B, "LTb",  0.0, 1000000.0, -100.0, 100.0,
186518.0, 191325.0, 0.0, 36.0);
static LineConvertor_D c_ilda (&memReader, &memWriter, ADDR_LD_I_ADC_A, "LIa",  0.0, 4095.0, 0.0, 12.0,
273.0, 4095.0, 0.0, 12.0);
static LineConvertor_D c_ildb (&memReader, &memWriter, ADDR_LD_I_ADC_B, "LIb",  0.0, 4095.0, 0.0, 12.0,
273.0, 4095.0, 0.0, 12.0);


//	double mini_X, double maxi_X, double mini_Y, double maxi_Y,
//	double x0, double x1, double y0, double y1)


static LineConvertor_D  c_ildDAa (&memReader, &memWriter, ADDR_LD_I_DAC_A, "LIDa",  0.0, 65534.0, 0.0, 13.0, 
273.0 * 16.0, 65534.0, 0.0, 12.0);
static LineConvertor_D  c_ildDAb (&memReader, &memWriter, ADDR_LD_I_DAC_B, "LIDb", 0.0, 65534.0,  0.0, 13.0, 
273.0 * 16.0, 65534.0, 0.0, 12.0);

static LineConvertor_D c_ulda (&memReader, &memWriter, ADDR_LD_U_ADC_A, "LUa",  0.0, 4095.0, 0.0, 3.0,
0.0, 4095.0, 0.0, 3.0);
static LineConvertor_D c_uldb (&memReader, &memWriter, ADDR_LD_U_ADC_B, "LUb",  0.0, 4095.0, 0.0, 3.0,
0.0, 4095.0, 0.0, 3.0);

static LineConvertor_D c_plda (&memReader, &memWriter, ADDR_LD_P_ADC_A, "LPa",  0.0, 4095.0, 0.0, 10.0,
0.0, 4095.0, 0.0, 10.0);
static LineConvertor_D c_pldb (&memReader, &memWriter, ADDR_LD_P_ADC_B, "LPb",  0.0, 4095.0, 0.0, 10.0,
0.0, 4095.0, 0.0, 10.0);


#include <Controller-E.h>
	//	I_A,
	//	I_B,        
	//	T_A,
	//	T_B,
	//	U_A,
	//	U_B,
	//	P_A,
	//	P_B,
	//	T_R,
//	POWER_SUP,
//	MODULES_NUM
//CurrCtlLD (AbstractConvertor_D* conv, double* input, unsigned int* output, double minTg, double maxTg, double iniVal, AbstractConvertor_D* dacConv) 
//static CurrCtlLD  iAFactor  (&c_ilda,  &iAADCavg, &iADAdata, 0, 12.0, 0.0, &c_ildDAa);
//static CurrCtlLD  iBFactor  (&c_ildb,  &iBADCavg, &iBDAdata, 0, 12.0, 0.0, &c_ildDAb);
//DirectCurrCtl (AbstractConvertor_D* conv, unsigned int* output, double minTg, double maxTg, double iniVal );
static DirectCurrCtl  iAFactor  (&c_ildDAa, &iADAdata, 0, 13.0, 0.0, &vt8EnableA );
static DirectCurrCtl  iBFactor  (&c_ildDAb, &iBDAdata, 0, 13.0, 0.0, &vt9EnableB);


//TstatLD (AbstractConvertor_D* conv, double* input, unsigned int* output, double minTg, double maxTg, double iniVal ) 
static TstatLD tAFactor (&c_tlda, &tAADCavg, &tADAdata, 17.0, 32.0, 25.0);
static TstatLD tBFactor (&c_tldb, &tBADCavg, &tBDAdata, 17.0, 32.0, 25.0);

//TstatLD (AbstractConvertor_D* conv, double* input, unsigned int* output, double minTg, double maxTg, double iniVal ) 

//		TstatFan (AbstractConvertor_D* conv, double* input, unsigned int* output, double minTg, double maxTg, double iniVal, AbstractController_E* iCtl)
static TstatFan  fanFactor (&c_rada, &tRadADCavg, &fanDAdata, 15.0, 40.0, 35.0, 0);

static PinOut_inv pinPwr (0, 10);
static PowerPin powP ( &pinPwr, &iAFactor, &iBFactor, &iAADCavg, &iAADCavg, &vt8, &vt9, &pLed, &pbt );

//	Indicator (AbstractConvertor_D* conv, double* input)

static Indicator uAind (&c_ulda, &uAADCavg);
static Indicator uBind (&c_uldb, &uBADCavg);

static Indicator pAind (&c_plda, &pAADCavg);
static Indicator pBind (&c_pldb, &pBADCavg);

AbstractCtl& fcCurrA  = iAFactor;
AbstractCtl& fcCurrB  = iBFactor;

//AbstractCtl& iAAufseher
//AbstractCtl& iBAufseher


AbstractCtl& fcTA  =  tAFactor;
AbstractCtl& fcTB  =  tBFactor;
AbstractCtl& fcFan = fanFactor;
AbstractCtl& fcPwr = powP;
AbstractCtl& fcUA = uAind;
AbstractCtl& fcUB = uBind;

AbstractController_E& tstA = tAFactor;
AbstractController_E& tstB = tBFactor;


AbstractCtl& fcPA = pAind;
AbstractCtl& fcPB = pBind;
AbstractPinOut& pwPn = powP;

#include <parser-Bi40.h>
static Modul diaMd (&iAFactor, &bo0);
static Modul dibMd (&iBFactor, &bo0);
static Modul dtaMd (&tAFactor, &bo0);
static Modul dtbMd (&tBFactor, &bo0);
static Modul dfanMd (&fanFactor, &bo0);
static DiscreteModul dpwrMd (&powP, &bo0);
static Modul duaMd (&uAind, &bo0);
static Modul dubMd (&uBind, &bo0);
static Modul dpaMd (&pAind, &bo0);
static Modul dpbMd (&pBind, &bo0);

AbstractModul&  dbg_modIa = diaMd;
AbstractModul& dbg_modIb = dibMd;
AbstractModul& dbg_modTa = dtaMd;
AbstractModul& dbg_modTb = dtbMd;
AbstractModul& dbg_modFan = dfanMd;
AbstractModul& dbg_modPwr = dpwrMd;
AbstractModul&  dbg_modUa = duaMd;
AbstractModul& dbg_modUb = dubMd;
AbstractModul& dbg_modPa = dpaMd;
AbstractModul& dbg_modPb = dpbMd;



static Parser prs (firstPass, secondPass, CMD_NUM, MODULES_NUM);

static Modul iaMd (&iAFactor, &bo1);
static Modul ibMd (&iBFactor, &bo1);
static Modul taMd (&tAFactor, &bo1);
static Modul tbMd (&tBFactor, &bo1);
static Modul fanMd (&fanFactor, &bo1);
static DiscreteModul pwrMd (&powP, &bo1);
static Modul uaMd (&uAind, &bo1);
static Modul ubMd (&uBind, &bo1);
static Modul paMd (&pAind, &bo1);
static Modul pbMd (&pBind, &bo1);

AbstractParser& parser =  prs;
AbstractModul&  modIa = iaMd;
AbstractModul& modIb = ibMd;
AbstractModul& modTa = taMd;
AbstractModul& modTb = tbMd;
AbstractModul& modFan = fanMd; 
AbstractModul& modPwr =  pwrMd ;
AbstractModul&  modUa = uaMd;
AbstractModul& modUb =  ubMd ;
AbstractModul& modPa  = paMd;
AbstractModul& modPb  = pbMd;

static const unsigned  char ADC_NUM_ALL = 21;
static const unsigned  char N_ADC = 9;
  //                                                                        		 0     	                     1           2             3                     4                   5                     6                        7      
static AbstractADC* adcsStart[ADC_NUM_ALL ] =  {  &tLda,    &iLda,   &uLda,   &iLdb,           &uLdb,         &pLda,          &pLdb,          
																				&tLdb,      &iLda,   &uLda,   &iLdb,           &uLdb,         &pLda,          &pLdb,    
																				&tRada,	&iLda,   &uLda,   &iLdb,           &uLdb,         &pLda,          &pLdb };

static AbstractADC* adcsRead[ADC_NUM_ALL ] =  {  &tRada,    &iLda,   &uLda,   &iLdb,           &uLdb,         &pLda,          &pLdb,          
																				&tLda,      &iLda,   &uLda,   &iLdb,           &uLdb,         &pLda,          &pLdb,    
																				&tLdb,	   &iLda,    &uLda,   &iLdb,           &uLdb,          &pLda,         &pLdb      };

static AbstractADC* adcList[ N_ADC ] =   {  &tLda,                     &iLda,          &uLda,         &iLdb,            &uLdb,            &pLda,            &pLdb,                  &tLdb,                 &tRada};


static double* adcDataList [ N_ADC ] =     {  &tAADCavg,     &iAADCavg, &uAADCavg,  &iBADCavg,  &uBADCavg,    &pAADCavg,    &pBADCavg,   &tBADCavg,    &tRadADCavg};	

void RouterAD()
{	
	static char currAdc = 0;
	adcsRead [currAdc]->Accumulate();
	++currAdc %= ADC_NUM_ALL;
	adcsStart[currAdc]->Start();

	static char currDac = 0;
//	++fanDacData;
//	fanDacData %= 0xfff;
	dacs[currDac]->Release();
	++currDac;
//	daDat += 200;
	currDac %= N_SPI0_DAC;
	dacs[currDac]->FirstWrite ( *dacSPI0Data [currDac] );	
////	//currAdc = 1;
//////	++*adcs[currAdc];
}



void ADCAveranger()
{
//	char bu[64];
//	unsigned  int nsm, su;
//	double data;
	for(int n = N_ADC - 1; n >= 0; --n )
	{
		*adcDataList[n] = adcList[n]->Get();//adcs[n]->Get();
//		sprintf( bu, "[%d] = %.1f ", n,  *adcDataList[n] ); 
//		uartTx1.Send ( bu );
	}
//	tRadADCavg = 189212.0;
//	sprintf(bu, "--===-=-=-=%c%c", 13, 10);
//	uartTx1.Send(bu);
}
