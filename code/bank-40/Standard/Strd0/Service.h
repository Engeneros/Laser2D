#ifndef SERVICE_H
#define SERVICE_H

void PCfg(unsigned char portNumM, unsigned char portNumL, unsigned char func);

void  IntervalGenerator(unsigned char nT, unsigned int nClk, unsigned long isrAddr);

void TimerStop(unsigned char nT);

void TimerStart(unsigned char nT);

void TimerReset(unsigned char nT);

#endif

