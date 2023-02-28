#ifndef UART_H
#define UART_H
#include <AbstractIO.h>
//E:\d2\www\2013Proj\soft\bank\Standard\Strd0\BuffOut\UART.h
class UART : public AbstractIOasy
{
public:
	UART(unsigned int uartNum);
	virtual void Tx ( unsigned long data ) ;
	virtual void Tx (const  unsigned char* data, unsigned int sz );
	virtual unsigned long Rx () ;
	virtual bool IsRxReady () ;
	virtual bool IsTxReady () ;
	virtual void SetTxISRAddr ( unsigned long addr );
	virtual void SetRxISRAddr ( unsigned long addr );
	unsigned long intEn;
	unsigned long intDis;
	virtual void DisableInt();
	virtual void EnableInt();

	virtual  ~UART(){}
protected:
	void IntEnable(unsigned long addr);
	volatile unsigned char* buff;
	volatile unsigned char* lineStat;
	unsigned int  num;
};

//class UART_Int : public UART
//{
//public:	
//	UART_Int(unsigned int uartN);
//	virtual void Tx (unsigned long data);
//	virtual unsigned long  Rx ();
//	virtual ~UART_Int();
//protected:
//	
//};

#endif

