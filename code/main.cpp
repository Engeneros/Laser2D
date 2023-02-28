#include <BoardDevices.h> 
#include <lpc214x.h>
#include <stdio.h>
#include <lpc2148_SPI_Regs.h>



//double* globAdcData [N_ADC] = {&tAADCavg, &tBADCavg, &pAADCavg,  &pBADCavg,    &iAADCavg, &uAADCavg,  &iBADCavg,  &uBADCavg}  ;

inline void SecundaEvent()
{
	vd10Green.Toggle();
//	uartTx1.Send("qq");
	

//	change();
}

inline void S100Event()
{
	ADCAveranger();
}
 
void MsEvent()
{	
	RouterAD();
}

#include <stdio.h>
#include <interfaceParticularity.h>
bool DoNoth()
{
	return false;
}

int main ()
{	
	AbstractModul* moSt [] = {&modIa, &modIb, &modTa, &modTb, &modUa,
	&modUb, &modPa, &modPb, &modFan, &modPwr};
	AbstractModul* dbg_moSt [] = {&dbg_modIa, &dbg_modIb, &dbg_modTa, &dbg_modTb, &dbg_modUa,
	&dbg_modUb, &dbg_modPa, &dbg_modPb, &dbg_modFan, &dbg_modPwr};
	AbstractCtl* ctlSt[] = { &fcCurrA, &fcCurrB, &fcTA, &fcTB,
	&fcUA, &fcUB, &fcPA, &fcPB, &fcFan, &fcPwr};
	char ctlCnt = 0;
	char ifcBuff [64];
	unsigned int cmdLen;
	unsigned int fALen;
	Instruction fAdr;
	bool isOk;
	
//	for ( int i = 0;  i < 2; ++i)
//	{			
//		tRef1 = 200000;
//		while (tRef1 > 0 )
//		{
//			tRef2 = 1000;
//			while( tRef2 > 0 )
//			{
//			}
//			MsEvent();	
//		}
//		S100Event();
//		if (pwPn.IsOn() == false)
//		{
//			tstA.Set(tstA.Get());
//			tstB.Set(tstB.Get());
//		}
//	}		
		
	while (true)
	{			
		tRef0 = 1000000; 
		while (tRef0 > 0)
		{
			
			tRef1 = 200000;
			while (tRef1 > 0 )
			{
				tRef2 = 1000;
				while( tRef2 > 0 )
				{
				}
				MsEvent();	
//				uartRx1.Router();
				ctlSt [ctlCnt]->Router();
				++ctlCnt  %= MODULES_NUM;
				cmdLen = uartRx1.Get(ifcBuff, MAX_CMD_LEN);				
				isOk =  (cmdLen == 0)?  false : parser.Translate ( ifcBuff, cmdLen, &fAdr, &fALen );
//				if(isOk != false)
//				{
//					char bfr[64];
//					sprintf (bfr, "=0=cmd = %d, mod = %d, %c%c", fAdr.func, fAdr.addr, 13, 10);
//					uartTx1.Send(bfr);
//				}
				(isOk == false)? DoNoth() : moSt[fAdr.addr]->Router(ifcBuff, fALen, fAdr.func); 
			}
			S100Event();
			cmdLen = uartRx0.Get(ifcBuff, MAX_CMD_LEN);				
			isOk =  (cmdLen == 0)?  false : parser.Translate ( ifcBuff, cmdLen, &fAdr, &fALen );
//				if(isOk != false)
//				{
//					char bfr[64];
//					sprintf (bfr, "=0=cmd = %d, mod = %d, %c%c", fAdr.func, fAdr.addr, 13, 10);
//					uartTx0.Send(bfr);
//				}
			(isOk == false)? DoNoth() : dbg_moSt[fAdr.addr]->Router(ifcBuff, fALen, fAdr.func); 
		}
		SecundaEvent();
		if (pwPn.IsOn() == false)
		{
			tstA.Set(tstA.Get());
			tstB.Set(tstB.Get());
		}
	}		
	return 0;
}
