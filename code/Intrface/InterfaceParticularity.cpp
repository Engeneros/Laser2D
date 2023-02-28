#include <interfaceParticularity.h>
Abrvr getAb ("g ", GET);
Abrvr setAb ("s ", SET);
Abrvr getDacAb ( "gDAC ", GET_DAC);
Abrvr getAdcAb ( "gADC ", GET_ADC);
Abrvr setDacAb ( "sDAC ", SET_DAC);
Abrvr  leftAb ("lf ", SET_LEFT);
Abrvr rightAb ("rg ", SET_RIGHT);
Abrvr clbAb ("clbr ", CALIBRATE);
Abrvr helloAb ("hello", HELLO);
Abrvr* firstPass[CMD_NUM] = {&getAb, &setAb,  &getDacAb, &getAdcAb, &setDacAb, &leftAb, &rightAb, &clbAb, &helloAb};

Abrvr iaAb ( "currOne", I_A);
Abrvr ibAb ( "currTwo", I_B);
Abrvr taAb ( "dioOneT", T_A);
Abrvr tbAb ( "dioTwoT", T_B);
Abrvr uaAb ("vltgOne", U_A);
Abrvr ubAb ("vltgTwo", U_B);
Abrvr paAb ("pwrW", P_A);
Abrvr pbAb ("powTwoW", P_B);
Abrvr trAb ("radT", T_R);
Abrvr sppAb ("power", POWER_SUP);
Abrvr* secondPass[MODULES_NUM] = { &iaAb, &ibAb,  &taAb, &tbAb,  &uaAb, &ubAb,  &paAb, &pbAb , &trAb, &sppAb};
