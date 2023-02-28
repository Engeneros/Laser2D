#ifndef CONSTANTS_H
#define CONSTANTS_H
//E:\d2\www\2013Proj\soft\draft\0040binaryRack=17.10.2016\sw\puC\puC40_0\code\Board\Constants40.h

const double  ERR_VAL = 999999.9;
const double  SAFE_QV_CURRENT  = 10000.0;
const double   SAFE_A_CURRENT = 0.3;
const  unsigned int RECORD_SZ = 64;

//extern AbstractADC& tLda;
//extern AbstractADC& tLdb;

//extern AbstractADC& iLda;
//extern AbstractADC& iLdb;
//extern AbstractADC& uLda;
//extern AbstractADC& uLdb;
//extern AbstractADC& pLda;
//extern AbstractADC& pLdb;


const unsigned int  ADDR_LD_T_ADC_A =  0;
const unsigned int  ADDR_LD_I_ADC_A  =  RECORD_SZ;
const unsigned int  ADDR_LD_I_DAC_A  =  2 * RECORD_SZ;
const unsigned int  ADDR_LD_U_ADC_A =  3 * RECORD_SZ;
const unsigned int  ADDR_LD_P_ADC_A =  4 * RECORD_SZ;

const unsigned int  ADDR_LD_T_ADC_B =  5 * RECORD_SZ;
const unsigned int  ADDR_LD_I_ADC_B  =  6 * RECORD_SZ;
const unsigned int  ADDR_LD_I_DAC_B  =  7 * RECORD_SZ;
const unsigned int  ADDR_LD_U_ADC_B =  8 * RECORD_SZ;
const unsigned int  ADDR_LD_P_ADC_B =  9 * RECORD_SZ;

const unsigned int  ADDR_RAD_T_ADC_A =  10 * RECORD_SZ;
const unsigned int  ADDR_RAD_T_ADC_B =  11 * RECORD_SZ;

const unsigned int  ADDR_LUMINA_T_ADC_A =  12 * RECORD_SZ;
const unsigned int  ADDR_LUMINA_T_ADC_B =  13 * RECORD_SZ;
#endif

