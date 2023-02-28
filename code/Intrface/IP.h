#ifndef  INTERFACE_PARTICULARITY
#define INTERFACE_PARTICULARITY
//E:\d2\www\2013Proj\soft\draft\0036RescuerU2=01.03.16\code\System\InterfaceParticularity.h
#include <string.h>
#include <AbstractParser.h>
#include <AbstractFPParser.h>
//E:\d2\www\2013Proj\soft\draft\0039AutoScan=08.07.2016\code\System\interfaceParticularity.h

enum CONTROL_MODES  
{
	MANUAL = 0,
	REMOTE =1
};

enum BOARD_MODULES
{
	NOWHERE = 0,
	CRISTALL_SM,
	FILTER_SM,
	ETALON_GD,
	ALL_MOTORS,
	CR_FIL,
	ETA_CR,
	ETA_FIL,
	MODULE_NUM
};

enum FUNCTION
{
	DO_NOTHING = 0,  
		MOVE,
		SET_SPEED,
		STOP,
			IS_MOVE,
			GET_VAL,
			GET_SPEED,
			GET_END_SENS,
		CALIBRATE,
			IS_CALIBRATE,	
			GET_CONNECTIONS_STATE,
	
	SET_CURR_START,
	SET_CURR_WORK,
	SET_CURR_RETENTION,
	SET_DIVIDER,
	INDICATE_SCAN,
	CTL_MODE,
	GET_CTL_MODE,
	GET_INVERTED_MODE,
	SET_INVERTED_MODE,
	PRESET,
	START,
	GET_DAC,
	FUNC_NUM
};

const unsigned char MAX_INP_STR_LEN = 32;
const unsigned char MOD_ABRV_NUM = 7;
const unsigned char ACTIV_FUNC_ABRV_NUM = FUNC_NUM - 1;
const unsigned char SHADOW_FUNC_ABRV_NUM = ACTIV_FUNC_ABRV_NUM - 7;
 const unsigned char  DBL_DATA_STR_LEN = 7;
//                                                                       DO_NOTHING    MOVE             SET_SPEED   STOP
const unsigned char ARG_NUM [ FUNC_NUM ] = { 0,                  1,                          1,                  0,

//  IS_MOVE    GET_VAL    GET_SPEED   GET_END_SENS   CALIBRATE    IS_CALIBRATE    GET_CONNECTIONS_STATE
	      0,                  0,                    0,                        0,                           0,                           0,                                 0 ,
//	SET_CURR_START,           WORK           RETENTION    DIVIDER         INDICATE_SCAN   	CTL_MODE,  	GET_CTL_MODE,   
			1,                                     1,                    1,                        1,                           1,                       1,                           0,             
//	GET_INVERTED_MODE,   	SET_INVERTED_MODE, 	PRESET,     START  GET_DAC
				0,                                      1,									1,					0,     0
};

const abrv modAb [MOD_ABRV_NUM] = {abrv ("Filter",  FILTER_SM), abrv ("Crystal", CRISTALL_SM), abrv("Etalon", ETALON_GD), 

abrv("All", ALL_MOTORS), abrv ("CrFlt", CR_FIL),  abrv ("EtaCr", ETA_CR), abrv ("EtaFlt", ETA_FIL)    }  ;

const abrv funcActivAb [ACTIV_FUNC_ABRV_NUM] = { abrv ("Move?", IS_MOVE), abrv ("Limits?", GET_END_SENS), abrv("Pos?", GET_VAL),  abrv("Vel?", GET_SPEED), 
																							abrv ("ConState?", GET_CONNECTIONS_STATE),
														abrv("Stop", STOP), abrv ("Move ", MOVE),  abrv("Vel ", SET_SPEED),  abrv ("Indicate ", INDICATE_SCAN), abrv( "FindRef", CALIBRATE),  abrv( "FindRef?", IS_CALIBRATE),
abrv("Preset ", PRESET),  abrv("Start", START),  abrv ("Control ", CTL_MODE), abrv ("Control?", GET_CTL_MODE),	abrv ("Inverted?", GET_INVERTED_MODE), 	abrv ("Inverted ", SET_INVERTED_MODE),
abrv("iS ", SET_CURR_START), abrv("iW ", SET_CURR_WORK), abrv("iR ", SET_CURR_RETENTION),  abrv("dv ", SET_DIVIDER),abrv("DAC?", GET_DAC)  };

const abrv funcShadowAb [SHADOW_FUNC_ABRV_NUM] = { abrv ("Move?", IS_MOVE), abrv ("Limits?", GET_END_SENS), abrv("Pos?", GET_VAL),  abrv ("Vel?", GET_SPEED), 
																		abrv ("ConState?", GET_CONNECTIONS_STATE), abrv( "FindRef?", IS_CALIBRATE), abrv("Vel ", SET_SPEED), abrv ("Control?", GET_CTL_MODE),	
			abrv ("Inverted?", GET_INVERTED_MODE), 	abrv ("Inverted ", SET_INVERTED_MODE),
			abrv("iS ", SET_CURR_START), abrv("iW ", SET_CURR_WORK), abrv("iR ", SET_CURR_RETENTION),  abrv("dv ", SET_DIVIDER),abrv("DAC?", GET_DAC)};




//const abrv  dbgAb [DBGFN_ABRV_NUM]= {abrv ("ctl ", GET_CONTROL), abrv ("sCtl ", SET_CONTROL),
//	abrv("lf ", LEFT_REF), abrv("rg ", RIGHT_REF), abrv ("state ", GET_STATE), abrv ("set ", SET_VALUE),
//								abrv("clbr ",  PRECISION_CALIBRATION), abrv("stop ",  STOP), abrv("cal ", CALIBRATE)};

//const abrv  usrAb [USFN_FUNC_ABRV_NUM] = {abrv ("state ", GET_STATE), abrv ("set ", SET_VALUE),
//								abrv("stop ",  STOP), abrv("cal ", CALIBRATE)};

//const abrv modulesAb[MOD_ABRV_NUM] = {abrv ("power", POWER_CONTROL),  abrv ("shtr", SHUTTER_CONTROL),
//											 abrv ("curr", LD_I),  abrv ("dioT", LD_T),  abrv ("dioPlate", RAD_LD_T),  abrv ("blPwr", LD_POWER),   abrv ("vltg", LD_U), 
//											 abrv ("vanT", VANADAD_T),  abrv ("lboT", LBO_T),  abrv ("etaT", ETALON_T),  abrv ("bsPlate", HEAD_T),  abrv ("grPwr", GREEN_POWER)};


//const char OK_STR[] = "ok";
//const char OOPS_STR[] = "oops";

#endif


//const char* MOD_ABRV[ MOD_ABRV_NUM ] = {"power", "shutter",
//											"curr", "dioT", "dioPlate", "blPwr",  "vltg", 
//											"vanT", "lboT", "etaT", "bsPlate", "grPwr"};
//const unsigned int MOD_ABRV_LEN[ MOD_ABRV_NUM ] = { strlen ("power"),  strlen ("shutter"),
//											 strlen ("curr"),  strlen ("dioT"),  strlen ("dioPlate"),  strlen ("blPwr"),   strlen ("vltg"), 
//											 strlen ("vanT"),  strlen ("lboT"),  strlen ("etaT"),  strlen ("bsPlate"),  strlen ("grPwr")};

//const unsigned int MOD_ABRV_SEMNT[ MOD_ABRV_NUM ] = {POWER_CONTROL, SHUTTER_CONTROL,
//																			LD_I, 	LD_T, 	RAD_LD_T, 	LD_POWER,	LD_U,
//																			VANADAD_T, LBO_T, ETALON_T,  HEAD_T, 	GREEN_POWER};
//const char* DBGFN_ABRV [ DBGFN_ABRV_NUM ] = { "ctl ", "sCtl", "lf",  "rg"}; 
//										
//const unsigned int DBGFN_ABRV_LEN[ DBGFN_ABRV_NUM ] = {strlen ("ctl"), strlen ("sCtl"), strlen ("lf"), strlen ( "rg")};

//const unsigned int DBGFN_ABRV_SEMNT [ DBGFN_ABRV_NUM ] = {GET_CONTROL, SET_CONTROL, LEFT_REF, RIGHT_REF};	
//const char* USFN_ABRV [ USFN_FUNC_ABRV_NUM ] = {"state", "set", "stop",  "cal"}; 
//										
//const unsigned int USFN_ABRV_LEN[ USFN_FUNC_ABRV_NUM ] = {strlen ("state"), strlen ("set"), strlen ("stop"), strlen ("cal")};

//const unsigned int USFN_ABRV_SEMNT[USFN_FUNC_ABRV_NUM ] = {GET_STATE, SET_VALUE, STOP, CALIBRATE};	

