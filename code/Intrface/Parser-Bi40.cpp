#include <Parser-Bi40.h>
#include <Extractor.h>
#include <stdio.h>
#include <string.h>
#include <constants40.h>
#include <lpc214x.h>
#include <boardDevices.h>

bool Parser::Translate ( char* strIn, unsigned int inputLen, Instruction* fAndAddr,  unsigned int* dataPos )
{
//	IOSET1 =31;
	unsigned  int fNum, mNum;
	bool ret  = false;
	unsigned char cmdL = 0, modL = 0;	
	for (fNum = 0; fNum < cmdNum && cmdL  == 0; ++fNum)
		cmdL = cmds[fNum]->Compare(strIn, inputLen);
	if (cmdL > 0)
	{
		char* modName = strIn + cmdL;

		unsigned char mStrLen = inputLen - cmdL;
		for (mNum = 0; mNum < modNum && modL == 0; ++mNum)
			modL = moduls [mNum]->Compare(modName, mStrLen);
		if ( modL > 0)
		{
			ret = true;
			fAndAddr->func = fNum - 1;
			fAndAddr->addr = mNum -1;
			*dataPos = cmdL + modL;
		}
		else
			for(signed char i = MAX_CMD_LEN; i >= 0; --i)
				strIn[i] = 0;
	}
	else
		for(signed char i = MAX_CMD_LEN; i >= 0; --i)
			strIn[i] = 0;
	return ret;
}

Modul::Modul  (AbstractController_E*  controler,  AbstractBuffOut* buffOut ) : ProtoModul(buffOut), ctl (controler)
{
	//(*options[i])(); /* §Ó§í§á§à§Ý§ß§Ö§ß§Ú§Ö */
	handler[GET]  = Hget; 
	handler [SET] = Hset;
	handler [GET_DAC] = HDACget;
	handler [GET_ADC] = HADCget;
	handler [SET_DAC] = HDACset;
	handler [SET_LEFT] = Hleft;
	handler [SET_RIGHT] = Hright;
	handler [CALIBRATE] = Hcalibr;
	handler [HELLO] = Hhello;
}

void ProtoModul::SendOOps (char* str, unsigned char lenght)
{
	sprintf(str+ lenght, "_OOPS!%c%c", 13, 10);
	char totLn = lenght + 8;
	outIfc->Send(str, totLn);
	for(signed char i = totLn; i >= 0; --i)
		str[i] = 0;
}

bool  Modul::Router (char* strIn, unsigned int inputLen, unsigned int fNum)
{
	bool ret;
	signed  char outlen = 0;
	if(fNum < CMD_NUM)
	{ 
//		char buff[64];		
		outlen = (*handler [ fNum])( strIn, inputLen, ctl);	
//		sprintf ( buff, "fNum = %d, outLen = %d%c%c", fNum, outlen, 13, 10);
//		uartTx1.Send(buff);
		if ( outlen >= 0)
		{
			char totLn = inputLen + outlen;;
			outIfc->Send(strIn, totLn);
			ret = true;
			for(signed char i = totLn; i >= 0; --i)
				strIn[i] = 0;
		}
		else 
		{
			SendOOps (strIn, inputLen);
			ret = false;
		}
	}
	else
	{
		SendOOps (strIn, inputLen);
		ret = false;
	}
	return ret;
}

static unsigned char  PrintData(char* str, double data)
{
	if(data < 0.01)
		sprintf (str, "   0.00%c%c",  13, 10);
	else if(data < 9.995)
		sprintf (str, "   %.2f%c%c", data, 13, 10);
	else if (data < 99.995)
		sprintf (str, "  %.2f%c%c", data, 13, 10);
	else
		sprintf (str, " %.2f%c%c", data, 13, 10);
	return 9;
}

signed char Modul::Hget(char* str, unsigned char lenght, AbstractController_E* cntrl)
{
//	uartTx1.Send("GET");
	return PrintData( str + lenght, cntrl->Get() );
}

signed char Modul::Hset(char* str, unsigned char lenght, AbstractController_E* cntrl)
{
	double val;
	int spaceLen = GetSeparatorLen(str + lenght,  4);
	signed char ret = lenght +  spaceLen;
	int datalen = GetDouble ( str + ret, 7,    &val);
	if (datalen + spaceLen == 7)
	{
		cntrl->Set(val);
		str [lenght + 7] =13;
		str [lenght + 8] = 10;
		return 9;
	}
	else
		ret = -1;
	return ret;
}

signed char Modul::HDACget(char* str, unsigned char lenght, AbstractController_E* cntrl)
{
	sprintf (str + lenght, " %d%c%c", cntrl->GetDac(), 13, 10);
	return strlen (str + lenght);
}

signed char Modul::HADCget(char* str, unsigned char lenght, AbstractController_E* cntrl)
{
//	uartTx1.Send("ADC_GET");
	sprintf (str + lenght, " %.2f%c%c", cntrl->GetAdc(), 13,10); 
	return strlen (str + lenght);
}


signed char Modul::HDACset(char* str, unsigned char lenght, AbstractController_E* cntrl)
{
//	uartTx1.Send("DAC_SET");
	unsigned int val;
	signed char ret;// = lenght + spaceLen;
	int datalen = GetUnsignedInt ( str + lenght + 1, 6, &val);
	if (datalen < 6 && datalen > 0)
	{
		cntrl->SetDAC(val);
		unsigned int pos = lenght +1 + datalen;
		str[pos++] = 13;
		str[pos] = 10;
		ret = datalen + 3;
	}
	else
		ret = -1;
	return ret;
}

signed char Modul::Hleft(char* str, unsigned char lenght, AbstractController_E* cntrl)
{
//	uartTx1.Send("LEFT");
	double val;
	int spaceLen = GetSeparatorLen(str + lenght,  4);
	signed char dataPos = lenght +  spaceLen;
	int dataLen = GetDouble ( str + dataPos, 7,    &val);
	signed char ret;
	if (dataLen > 0)
	{
		cntrl->SetLeftRef(val);
		char pos = dataPos + dataLen;
		str[pos++] = 13;
		str[pos] = 10;
		ret = spaceLen + dataLen + 2;
	}
	else
		ret = -1;
	return ret;
}
	
signed char Modul::Hright(char* str, unsigned char lenght, AbstractController_E* cntrl)
{
//	uartTx1.Send("RIGHT");
	double val;
	int spaceLen = GetSeparatorLen(str + lenght,  4);
	signed char dataPos = lenght +  spaceLen;
	int dataLen = GetDouble ( str + dataPos, 7,    &val);
	signed char ret;
	if (dataLen > 0)
	{
		cntrl->SetRightRef(val);
		char pos = dataPos + dataLen;
		str[pos++] = 13;
		str[pos] = 10;
		ret = spaceLen + dataLen + 2;
	}
	else
		ret = -1;
	return ret;
}

signed char Modul::Hcalibr(char* str, unsigned char lenght, AbstractController_E* cntrl)
{
//	uartTx1.Send("CALIBR");
	cntrl->Calibrate();
	str [ lenght++ ] = 13;
	str [ lenght ] = 10;
	return 2;
}

signed char  Modul::Hhello(char* str, unsigned char lenght, AbstractController_E* cntrl)
{
//	uartTx1.Send("HELLO");
	sprintf (str + lenght, "%s%c%c", I_AM, 13, 10);
	return strlen(str+lenght);
}

DiscreteModul::DiscreteModul ( AbstractPinOut * control,  AbstractBuffOut * buffOut ) : ProtoModul(buffOut),
ctl (control)
{
	handler [GET]  = Hget; 
	handler [SET] = Hset;
	handler [SET_DAC] = HDACset;
	handler [GET_ADC] = HADCget;
	handler [GET_DAC] = HDACget;
	handler [SET_LEFT] = Hleft;
	handler [SET_RIGHT] = Hright;
	handler [CALIBRATE] = Hcalibr;
	handler [HELLO] = Hhello;
}

bool DiscreteModul::Router (char* strIn, unsigned int inputLen, unsigned int fNum)
{
	bool ret;
	signed  char outlen = 0;
	if(fNum <   CMD_NUM)
	{ 
		outlen = (*handler [fNum])(strIn, inputLen, ctl);	
		if ( outlen >= 0)
		{
			
			char totLn = inputLen + outlen;;
			outIfc->Send(strIn, totLn);
			ret = true;
			for(signed char i = totLn; i >= 0; --i)
				strIn[i] = 0;
		}
		else 
		{
			SendOOps (strIn, inputLen);
			ret = false;
		}
	}
	else
	{
		SendOOps (strIn, inputLen);
		ret = false;
	}
	return ret;
}

signed  char  DiscreteModul::Hget    ( char* str,  unsigned char lenght,  AbstractPinOut* cntrl)
{
	//uartTx1.Send("disGET");
	bool isOn = cntrl->IsOn();
	sprintf(str + lenght, (isOn == false)? " off%c%c" : " on%c%c", 13, 10);
	return  (isOn == false)? 6 : 5 ;
}

signed char DiscreteModul::On(AbstractPinOut* mng)
{
//	uartTx1.Send("disON");
	mng->Set();
	return 3;
}

signed char DiscreteModul::Off(AbstractPinOut* mng)
{
	//uartTx1.Send("disOFF");
	mng->Clear();
	return 4;
}

signed char DiscreteModul::Err(AbstractPinOut* mng)
{ 
	return 0;
}


signed  char DiscreteModul::Hset    ( char* str,  unsigned char lenght,  AbstractPinOut* cntrl)
{
//	uartTx1.Send("disHSet");
	static Abrvr off (" off", 0),  on (" on", 1);
	signed char (*action)(AbstractPinOut* mng);
	char* data = str + lenght;
	action = (off == str + lenght)? Off : (on ==  str + lenght)? On : Err;
	signed char dLen =  (*action)(cntrl) ;
	sprintf(data + dLen,   "%c%c" , 13, 10);
	return dLen + 2;
}

signed char DiscreteModul::Hhello (char* str,  unsigned char lenght,  AbstractPinOut* cntrl )
{
//	uartTx1.Send("disHELLO");
	char* data = str +lenght;
	sprintf(data, "hi, i'm PowerContrl Modul%c%c", 13, 10);
	return (strlen (data));
}

