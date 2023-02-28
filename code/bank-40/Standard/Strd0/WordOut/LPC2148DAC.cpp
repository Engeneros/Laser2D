#include <LPC2148DAC.h>
#include <LPC214x.h>
#include <Service.h>
//E:\d2\www\2013Proj\soft\bank\Standard\Strd0\WordOut\LPC2148DAC.cpp

LPC2128DAC::LPC2128DAC()
{
	PCfg(0, 25, 2);
}

void LPC2128DAC::Send(unsigned long data)
{
	DACR = data << 6;
}
