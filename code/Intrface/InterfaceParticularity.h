#ifndef   INTERFACE_PARTICULARITY_H
#define  INTERFACE_PARTICULARITY_H
#include <Abrvr.h>
//E:\d2\www\2013Proj\soft\draft\0040binaryRack=17.10.2016\sw\puC\puC40_0\code\Intrface\InterfaceParticularity.h

const char I_AM[] = "Hello! I'am Fiber binary diode laser, interface v.nu0";
const unsigned char MAX_CMD_LEN = 32;

enum COMMANDOS
{
	GET,
	SET,
	GET_DAC,
	GET_ADC,
	SET_DAC,
	SET_LEFT,
	SET_RIGHT,
	CALIBRATE,
	HELLO,
	CMD_NUM
};

//////////////////////extern Abrvr getAb ("g ", GET);
//////////////////extern Abrvr setAb ("s ", SET);
//////////////////extern Abrvr getDacAb ("gDAC ", GET_DAC);
//////////////////extern Abrvr setDacAb ( "sDAC ", SET_DAC);
//////////////////extern Abrvr leftAb ("lf ", SET_LEFT);
//////////////////extern Abrvr rightAb ("rg ", SET_RIGHT);
//////////////////extern Abrvr clbAb ("clbr ", CALIBRATE);
//////////////////extern Abrvr helloAb ("hello", HELLO);
extern Abrvr getAb ;
extern Abrvr setAb;
extern Abrvr getDacAb;
extern Abrvr getAdcAb;
extern Abrvr setDacAb ;
extern Abrvr leftAb ;
extern Abrvr rightAb;
extern Abrvr clbAb ;
extern Abrvr helloAb ;
const unsigned char MAX_CMD_ABRV_LEN = 8;

//Abrvr* firstPass[CMD_NUM] = {&getAb, &setAb, &getDacAb, &setDacAb, &leftAb, &rightAb, &clbAb, &helloAb};
extern Abrvr* firstPass[CMD_NUM];
enum MODUL
{
	I_A,
	I_B,
	T_A,
	T_B,
	U_A,
	U_B,
	P_A,
	P_B,
	T_R,
	POWER_SUP,
	MODULES_NUM
};

//Abrvr iaAb ( "currOne", I_A);
//Abrvr ibAb ( "currTwo", I_B);
//Abrvr taAb ( "doiOneT", T_A);
//Abrvr tbAb ( "dioTwoT", T_B);
//Abrvr uaAb ("vltgOne", U_A);
//Abrvr ubAb ("vltgTwo", U_B);
//Abrvr paAb ("powOneW", P_A);
//Abrvr pbAb ("powTwoW", P_B);
//Abrvr trAb ("radT", T_R);
//Abrvr sppAb ("power", POWER_SUP);

extern  Abrvr iaAb ;
extern  Abrvr ibAb;
extern  Abrvr taAb;
extern  Abrvr tbAb;
extern  Abrvr uaAb;
extern  Abrvr ubAb;
extern  Abrvr paAb;
extern  Abrvr pbAb;
extern  Abrvr trAb;
extern  Abrvr sppAb;


//Abrvr* secondPass[MODULES_NUM] = { &iaAb, &ibAb,  &taAb, &tbAb,  &uaAb, &ubAb,  &paAb, &pbAb , &trAb, &sppAb};
extern  Abrvr* secondPass[MODULES_NUM] ;
#endif
