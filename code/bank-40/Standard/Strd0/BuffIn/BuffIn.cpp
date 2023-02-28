#include <BuffIn.h>
//#include <Dbg.h>
#include <lpc24xx.h>
#include <stdio.h>
#include <string.h>
#include <boardDevices.h>


TerminatorList::~TerminatorList()
{
	if(prev != 0)
		prev->SetNext(nxt);
	if (nxt != 0)
		nxt->SetPrev(prev);
}

//				GetOKLed3()->Set();	
//		//	if(rxSuspend == false)
//			//{
//				TerminatorList* tmp;
//				if( fifoRd != 0 )			
//				{
//					GetOKLed1()->Set();
//					tmp = new TerminatorList ( wrPos, fifoWr, 0 );
//					++cnt;
//					fifoWr->SetNext ( tmp );
//					fifoWr = tmp;
//					GetOKLed1()->Clear();
//				}
//				else
//				{
//					GetOKLed2()->Set();
//					fifoWr = new TerminatorList (wrPos, 0, 0);
//					++cnt;
//					fifoRd = fifoWr;
//					GetOKLed2()->Clear();
//				}	
//				GetOKLed3()->Clear();

BuffInTxt::BuffInTxt(AbstractIOasy* ifc, unsigned int size, char endSymb, unsigned long addr) :  
AbstractBuffIn(size), terminator (endSymb) ,   wrPos (0), rdPos(0), 
fifoRd (0), fifoWr (0), rxSuspend(false)
{
//	maxFreeSz = freeSz = size - 32;
	iIfc = ifc;
	if(addr != 0)
		iIfc->SetRxISRAddr(addr);
}

unsigned int BuffInTxt::Get(char* data, unsigned int maxSz)
{
	unsigned int ret = 0;
	int ePos ;
	unsigned int posIn, posOut, cmdSz;
	while (fifoRd != 0 && ret == 0)
	{	
		 ePos = fifoRd->GetPos();
		if(ePos < rdPos)
		{
			unsigned int first  = buffSz - rdPos;
			cmdSz = first +  ePos;
			if (cmdSz < maxSz)
			{
				posIn = buffSz;
				for (posOut  = first; posOut > 0;)
					data[--posOut] = buff[--posIn];
				ret = posOut = cmdSz;
				for ( posIn = ePos; posIn > 0;)
					data[--posOut] = buff[--posIn];
			}
		}
		else 
		{
			cmdSz = ePos - rdPos;
			if(cmdSz < maxSz)
			{
			ret = posOut = ePos - rdPos; 
			for(posIn = ePos; posOut  > 0 ;)
				data[--posOut] = buff[--posIn];
			}
		}
		rxSuspend = true;
		rdPos = ePos;
//		iIfc->DisableInt();
		TerminatorList * tmp = fifoRd;
		fifoRd = fifoRd->GetNext();
		delete 		tmp;	
//		iIfc->EnableInt();
		rxSuspend = false;
	}
	return ret;
}

void BuffInTxt::Router()
{
	char symb;
	while(iIfc->IsRxReady() != false)
	{
		symb = iIfc->Rx();
		if (symb == terminator)
		{			
			if(rxSuspend == false)
			{
				TerminatorList* tmp;
				if( fifoRd != 0 )			
				{
					tmp = new TerminatorList ( wrPos, fifoWr, 0 );
					fifoWr->SetNext ( tmp );
					fifoWr = tmp;
				}
				else
				{
					fifoWr = new TerminatorList (wrPos, 0, 0);
					fifoRd = fifoWr;
				}	
			}
//			TerminatorList* prTmp = fifoRd->GetPrev(); 
//			while( prTmp != 0)
//			{
//				delete prTmp;
//				prTmp = fifoRd->GetPrev();
//			}
		}
		else if(symb >= PRINTABLE)
		{
			buff[wrPos] = symb;
			++wrPos;
			wrPos %= buffSz;
		}	
	}
}



/////////DBG
unsigned int BuffInTxtDbg::Get(char* data, unsigned int maxSz)
{
	unsigned int ret = 0;
	int ePos ;
	unsigned int posIn, posOut, cmdSz;
	if (fifoRd != 0 )
	{	
		 ePos = fifoRd->GetPos();
		if(ePos < rdPos)
		{
			unsigned int first  = buffSz - rdPos;
			cmdSz = first +  ePos;
			if (cmdSz < maxSz)
			{
				posIn = buffSz;
				for (posOut  = first; posOut > 0;)
					data[--posOut] = buff[--posIn];
				ret = posOut = cmdSz;
				for ( posIn = ePos; posIn > 0;)
					data[--posOut] = buff[--posIn];
			}
		}
		else 
		{
			cmdSz = ePos - rdPos;
			if(cmdSz < maxSz)
			{
			ret = posOut = ePos - rdPos; 
			for(posIn = ePos; posOut  > 0 ;)
				data[--posOut] = buff[--posIn];
			}
		}
//		rxSuspend = true;
		rdPos = ePos;
//		iIfc->DisableInt();
		TerminatorList * tmp = fifoRd;
		fifoRd = fifoRd->GetNext();
		delete 		tmp;	
//		iIfc->EnableInt();
//		rxSuspend = false;
	}
//	else if(intEn == false)
//	{
//		intEn = true;
//		iIfc->EnableInt();
//	}
	return ret;
}

void BuffInTxtDbg::Router()
{

	char symb;
//	iIfc->DisableInt();
//	intEn = false;
	while(iIfc->IsRxReady() != false)
	{
	
		symb = iIfc->Rx();
		if (symb == terminator)
		{			
//			if(rxSuspend == false)
	//		{
			
				TerminatorList* tmp;
				if( fifoRd != 0 )			
				{
					tmp = new TerminatorList ( wrPos, fifoWr, 0 );
					fifoWr->SetNext ( tmp );
					fifoWr = tmp;
				}
				else
				{
					fifoWr = new TerminatorList (wrPos, 0, 0);
					fifoRd = fifoWr;
				}	
			//}
//			TerminatorList* prTmp = fifoRd->GetPrev(); 
//			while( prTmp != 0)
//			{
//				delete prTmp;
//				prTmp = fifoRd->GetPrev();
//			}
		}
		else if(symb >= PRINTABLE)
		{
			buff[wrPos] = symb;
			++wrPos;
			wrPos %= buffSz;			
		}	
	}
}








//unsigned int BuffInTxt::Get(char* data, unsigned int maxSz)
//{
//	unsigned int ret;
//	if(fifoRd == 0)
//		ret = 0;
//	else
//	{	
//		 int ePos = fifoRd->GetPos();
//		unsigned int posIn, posOut;
//		if(ePos < rdPos)
//		{
//			unsigned int first  = buffSz - rdPos;
//			posIn = buffSz;
//			for (posOut  = first; posOut > 0;)
//				data[--posOut] = buff[--posIn];
//			ret = posOut = first +  ePos;
//			for ( posIn = ePos; posIn > 0;)
//				data[--posOut] = buff[--posIn];
//		}
//		else
//		{
//			ret = posOut = ePos - rdPos; 
//			for(posIn = ePos; posOut  > 0 ;)
//				data[--posOut] = buff[--posIn];
//		}
//		
//		rdPos = ePos;
//		rxSuspend = true;
//		TerminatorList * tmp = fifoRd;
//		fifoRd = fifoRd->GetNext();
//		delete 		tmp;	
//		rxSuspend = false;
//	}
//	return ret;
//}

unsigned int  BuffInTxt::EchoRouter(char* inp)
{
	char symb;
	unsigned int ret = 0;
	while(iIfc->IsRxReady() != false)
	{
		symb = iIfc->Rx();
		inp[ret++] = symb;
//		if(symb == 13)
//			inp[ret++] = 10;
//		else if(symb == 10)
//			ret--;
		if (symb == terminator)
		{
			TerminatorList* tmp;
			if(fifoRd != 0)			
			{
				tmp = new TerminatorList(wrPos, fifoWr, 0);
		                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         		fifoWr->SetNext(tmp);
				fifoWr = tmp;
			}
			else
			{
				fifoWr = new TerminatorList (wrPos, 0, 0);
				fifoRd = fifoWr;
			}			
		}
		else if(symb >= PRINTABLE)
		{
			buff[wrPos++] = symb;
			wrPos %= buffSz;
		}
	}		
	return ret;
}



//												#include <BoardDevices.h>
//												#include <stdio.h>
//												unsigned int BuffInTxt::Get(char* data, unsigned int maxSz) 
//												{
//													unsigned int ret = 0, currSz;

//													if(fifoRd == 0)
//														freeSz = maxFreeSz;
//												//	if (--cnt == 0)
//												//	{
//												//		char buf[32];
//												//		sprintf (buf, " %d", freeSz);
//												//		GetUARTtx2()->Send(buf);
//												//		cnt = 2;
//												//	}
//												//		
//													if(nCmd > 10)
//													{
//														while (fifoRd != 0)
//														{
//															TerminatorList * tmp = fifoRd;
//															fifoRd = fifoRd->GetNext();
//															delete 		tmp;	
//														}				
//														nCmd = 0;
//														freeSz = maxFreeSz;
//													}
//													while(fifoRd != 0 && ret == 0)	 
//													{	
//														unsigned int ePos = fifoRd->GetPos();
//														unsigned int posIn, posOut;
//														if(ePos < rdPos)
//														{
//															unsigned int first  = buffSz - rdPos;
//															currSz = first + ePos;
//															if ( currSz <= maxSz)
//															{
//																posIn = buffSz;
//																for (posOut  = first; posOut > 0;)
//																	data[--posOut] = buff[--posIn];
//																ret =  posOut = currSz;
//																for ( posIn = ePos; posIn > 0;)
//																	data[--posOut] = buff[--posIn];
//															}
//														}
//														else
//														{
//															currSz = posOut = ePos - rdPos; 
//															if (currSz <= maxSz)
//															{
//																for(posIn = ePos; posOut  > 0 ;)
//																	data[--posOut] = buff[--posIn];
//																ret = currSz;
//															}
//														}
//														freeSz += currSz;
//														--nCmd;
//														rdPos = ePos;
//														TerminatorList * tmp = fifoRd;
//														fifoRd = fifoRd->GetNext();
//														delete 		tmp;	
//													}

//														
//													return ret;




//												//	unsigned int ret;
//												//	if(fifoRd == 0)
//												//		ret = 0;
//												//	else
//												//	{	
//												//		GetOKLed1()->Toggle();
//												//		 int ePos = fifoRd->GetPos();
//												////		unsigned int posIn, posOut;
//												////		if(ePos < rdPos)
//												////		{
//												////			unsigned int first  = buffSz - rdPos;
//												////			posIn = buffSz;
//												////			for (posOut  = first; posOut > 0;)
//												////				data[--posOut] = buff[--posIn];
//												////			ret = posOut = first +  ePos;
//												////			for ( posIn = ePos; posIn > 0;)
//												////				data[--posOut] = buff[--posIn];
//												////		}
//												////		else
//												////		{
//												////			ret = posOut = ePos - rdPos; 
//												////			for(posIn = ePos; posOut  > 0 ;)
//												////				data[--posOut] = buff[--posIn];
//												////		}
//												//		rdPos = ePos;
//												//		TerminatorList * tmp = fifoRd;
//												//		fifoRd = fifoRd->GetNext();
//												//		delete 		tmp;	
//												//	}
//												//	return ret;
//}



