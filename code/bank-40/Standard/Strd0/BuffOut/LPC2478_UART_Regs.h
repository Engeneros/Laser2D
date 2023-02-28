#ifndef LPC2148_UART_REGS
#define LPC2148_UART_REGS
//E:\d2\www\2013Proj\soft\bank\Standard\Strd0\BuffOut\LPC2478_UART_Regs.h
	//																											0xE000C000            						0xE0010000     										 0xE0078000 									0xE007C000
volatile unsigned char* const UART_LC_REG[] = {(volatile unsigned char*) 0xE000C00C, (volatile unsigned char*) 0xE001000C,  (volatile unsigned char*) 0xE007800C, (volatile unsigned char*)   0xE007C00C,};
volatile unsigned char* const UART_DLL_REG[] = {(volatile unsigned char*) 0xE000C000, (volatile unsigned char*) 0xE0010000, (volatile unsigned char*) 0xE0078000, (volatile unsigned char*)  0xE007C000};
volatile unsigned long* const UART_IE_REG[] = {(volatile unsigned long*) 0xE000C004, (volatile unsigned long*) 0xE0010004, (volatile unsigned long*)  0xE0078004, (volatile unsigned long*)  0xE007C004};
volatile unsigned long* const UART_IID_REG[] = {(volatile unsigned long*) 0xE000C008, (volatile unsigned long*) 0xE0010008, (volatile unsigned long*)  0xE0078008, (volatile unsigned long*)  0xE007C008};
volatile unsigned char* const UART_BUFFERS_REG[] = {(volatile unsigned char*) 0xE000C000, (volatile unsigned char*) 0xE0010000, (volatile unsigned char*)  0xE0078000, (volatile unsigned char*) 0xE007C000};
volatile unsigned char* const UART_FDR_REG[] = {(volatile unsigned char*) 0xE000C028, (volatile unsigned char*) 0xE0010028, (volatile unsigned char*)  0xE0078028, (volatile unsigned char*)  0xE007C028 };
volatile unsigned char* const UART_LSTAT_REG[] = {(volatile unsigned char*) 0xE000C014, (volatile unsigned char*) 0xE0010014, (volatile unsigned char*)  0xE0078014, (volatile unsigned char*) 0xE007C014};
volatile unsigned char* const UART_FCR_REG[] = {(volatile unsigned char*) 0xE000C008, (volatile unsigned char*) 0xE0010008, (volatile unsigned char*)  0xE0078008, (volatile unsigned char*) 0xE007C008};
//struct UART_Regs
//{
//	unsigned char  buff ;       //RBR ;    //       (*((volatile unsigned char *) 0xE000C000))
//									       //	THR ;    //      (*((volatile unsigned char *) 0xE000C000))
//	unsigned char stub0;
//	unsigned short stib1;
//	unsigned long enInt;       //	IER  ;  //      (*((volatile unsigned long *) 0xE000C004))
//	unsigned long idInt_fcr;  // IIR    ; //     (*((volatile unsigned long *) 0xE000C008))
//										   //FCR ; //       (*((volatile unsigned char *) 0xE000C008))
//	unsigned char  lineCtl;    //	LCR ;	//       (*((volatile unsigned char *) 0xE000C00C))
//	unsigned char stub2;
//	unsigned short stib3;
//	
//	unsigned char  modemCtl;	//MCR;  //         (*((volatile unsigned char *) 0xE000C010))
//	unsigned char stub4;
//	unsigned short stib5;
//	
//	unsigned char  lineStatus;	//LSR  ; //        (*((volatile unsigned char *) 0xE000C014))
//	unsigned char stub6;
//	unsigned short stub7;	

//	
//	unsigned char  modemStatus;	//	MSR ; //         (*((volatile unsigned char *) 0xE000C018))
//	unsigned char stub8;
//	unsigned short stub9;
//	unsigned char stratchPad; ////SCR ;  //        (*((volatile unsigned char *) 0xE000C01C))
//	unsigned char stub10;
//	unsigned short stub11;
//	unsigned char dll;// DLL  ;  //       (*((volatile unsigned char *) 0xE000C000))
//	unsigned char stub12;
//	unsigned short stub13;

//	unsigned char dlm;//	DLM ;  //        (*((volatile unsigned char *) 0xE000C004))
//	unsigned char stub14;
//	unsigned short stub15;

//	ACR ;   //       (*((volatile unsigned long *) 0xE000C020))
//	FDR ;   //       (*((volatile unsigned long *) 0xE000C028))
//	TER  ;  //       (*((volatile unsigned char *) 0xE000C030))
//};

#endif

