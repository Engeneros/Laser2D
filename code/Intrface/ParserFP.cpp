#include <ParserFP.h>
#include <interfaceParticularity.h>
#include <Extractor.h>
#include <stdio.h>
#include <string.h>
//#include <stdio.h>
//#include <boardDevices.h>
#include <constants.h>

bool StringComparator (const char* str, const char* ref, unsigned int refLen)
{
	bool ret = true;
	int i;
	for (i = refLen; i > 0 && ret != false; )
	{
		--i;
		ret = (str[i] == ref[i])? true : false;
	}
	return ret;
}

static bool GetSense (const char* strIn, unsigned int inputLen, const abrv* ref, unsigned char refNum, unsigned int* addr,  unsigned int* tailPos)
{
	bool ret = false;
	int i;
	unsigned int len;
	const abrv* mod;
	for (i = refNum; ret == false &&  i > 0; )
	{
		mod  = &ref[--i];
		len = mod->len;
		ret = StringComparator (strIn, mod->txt, len); 
	}
	if(ret != false)
	{
		*addr = mod->smnt;
		*tailPos = len;
	}
	return ret;
}

ParserSt::ParserSt(const  abrv* modules, const abrv* actFunct, const abrv* shFunct,  unsigned char nModules, unsigned char nFActiv, unsigned char nFShadow)
{
	nFunA = nFActiv;
	nFunS = nFShadow;
	nMod = nModules;
	modAb = modules;
	fnAbActiv = actFunct;
	fnAbShdw = shFunct;
}

#include <BoardDevices.h>
bool ParserSt::Translate (const char* strIn, unsigned int inputLen, FunAddrDat* fAddrD, char mode)
{
	unsigned int 	mod = 0, fncN = 0, modShift = 0,  shift= 0;
	int data;
	const abrv* fAb;
	int fNum;
	if (mode == MANUAL)
	{
		fNum = nFunS;
		fAb = fnAbShdw;
	}
	else
	{
		fNum = nFunA;
		fAb = fnAbActiv;
	}

	bool ret = GetSense ( strIn, inputLen, modAb, nMod, &mod,  &modShift);
	mod = (ret == false)? NOWHERE : mod;
	ret = GetSense ( strIn + modShift, inputLen  - modShift, fAb, fNum, &fncN,  &shift);
	if (ret != false && fncN < FUNC_NUM && ARG_NUM[fncN] > 0)
	{
		int fmLen = shift + modShift;
		int dataLen = GetSignedInt(strIn + fmLen, inputLen - fmLen, &data);
		if(dataLen > 0  && dataLen < 7)
			fAddrD->data = data;
		else ret = false;
	}
	if ( ret != false )
	{
		fAddrD->addr = mod;
		fAddrD->func = fncN;
	}
	return ret;
}

ParserFP::ParserFP(SMState* cristallState,  SMState* filterState)
{
	crSmSt = cristallState;
	filSmSt = filterState;
	lambdaCnt = pumperCnt = 0;
}

void ParserFP::Stop(FunAddrDat* fad)
{
	pumperCnt = lambdaCnt = 0;
	fad->func = STOP;
}

void ParserFP::GetButtonSense (int* cnt, bool left, bool right, FunAddrDat* fad, SMState* state)
{
	int isM = state->speedInst;
	if (left != false)
	{
		if (isM ==0)
		{
			fad->func = MOVE;
			fad->data = -99999;
			state->speedInst = -20;
		}
		else if (isM < 0 )
			fad->func = DO_NOTHING;
		else
			Stop(fad);
	}
	else if (right != false)
	{	
				
		if (isM ==0)
		{
			fad->func = MOVE;
			fad->data = 99999;
			state->speedInst = 20;
		}
		else if (isM > 0 )
			fad->func = DO_NOTHING;
		else
			Stop(fad);
	}
	else if ( isM  != 0 )
		Stop(fad);
	else
		fad->func = DO_NOTHING;			
}

bool ParserFP::Translate(const char* strIn, unsigned int inputLen, FunAddrDat* fAddrD, char mode)
{	
	bool ret = false;
	if ( strIn[2] != 0)															//encoder
	{
		fAddrD->func = MOVE;
		fAddrD->data =  ( signed char ) strIn[2];
		fAddrD->addr = FILTER_SM;
		ret = true;
	}
	else	if ( strIn[0] != 0)															//encoder
	{
		fAddrD->func = MOVE;
		fAddrD->data =  ( signed char ) strIn[0];
		fAddrD->addr = CRISTALL_SM;
		ret = true;
	}
	else
	{
		GetButtonSense( &lambdaCnt, ((strIn[1] & 0x10 ) == 0)? false : true, ((strIn[1] & 0x20 ) == 0)? false : true, fAddrD, filSmSt);
		if (fAddrD->func != DO_NOTHING)
		{
			fAddrD->addr = FILTER_SM;	
			ret = true;
		}
		else
		{
			GetButtonSense( &pumperCnt, ((strIn[1] & 4 ) == 0)? false : true, ((strIn[1] & 8 ) == 0)? false : true, fAddrD, crSmSt);
			if (fAddrD->func != DO_NOTHING)
			{
				fAddrD->addr = CRISTALL_SM;		
				ret = true;
			}
			else
			{			
				fAddrD->func = DO_NOTHING;
				fAddrD->addr = NOWHERE;
				fAddrD->data = 0;
			}						
		}
	}			
	return ret;
}

AbstractStepMotorCtl* smCtl;
SMState* state;
AbstractBuffOut* usrOut;

AbstractPinOut* leftRed;
AbstractPinOut* leftGreen;
AbstractPinOut* rightRed;
AbstractPinOut* rightGreen;

ModulSM::ModulSM (AbstractStepMotorCtl* stMotCtl, SMState* staSM, AbstractBuffOut* ifc,
/*	AbstractPinOut* lfRedLed,  AbstractPinOut* lfGreenLed,  AbstractPinOut* rgRedLed,  AbstractPinOut* rgGreenLed, */ bool* ctlMode, const bool* man,
	const char* moduleName, bool* invSM, unsigned int memAddr ) : preset (0), waitSens (false)
{
	smCtl = stMotCtl;
	state = staSM;
	usrOut = ifc;
//	leftRed = lfRedLed;
//	leftGreen = lfGreenLed;
//	rightRed = rgRedLed;
//	rightGreen = rgGreenLed;	
	modeControl = ctlMode;
	isManCt = man;
	nameLen = strlen(moduleName);
	strcpy( myName, moduleName);
	cmdAndData = myName + nameLen;
	isInv = invSM;
	mAddr = memAddr;
	char buf[4];
	GetAT24C256Reader()->Read(mAddr, buf, 1);
	*isInv = ( buf[0] == VAL_TRUE )? true : false;
}

extern unsigned int etaDac;
#include <boardDevices.h>
bool ModulSM::Router (unsigned int fNum, int data)
{
//	char buf [ MAX_INP_STR_LEN ];
	bool ret = false;
	*isInv = false;
	if (fNum == IS_MOVE)
	{
		sprintf (cmdAndData, "Move? %d%c%c", (  state->speedInst == 0 )? 0 : 1, 13, 10  );
		usrOut->Send (myName, strlen(myName) );
		ret = true;
	}
	else if (fNum == GET_END_SENS)
	{
		char end;
		//
		if (*isInv == false)
		{
			end	= (state->leftEnd != false)? 1 : 0;
			end |= (state->rightEnd != false)? 2 : 0;
		}
		else
		{
			end	= (state->leftEnd != false)? 2 : 0;
			end |= (state->rightEnd != false)? 1 : 0;
		}	
		sprintf (cmdAndData, "Limits? %d%c%c", end, 13, 10);
		usrOut->Send( myName, strlen(myName));
		ret = true;
	}
	else if (fNum == GET_VAL)
	{
		sprintf (cmdAndData, "Pos? %d%c%c",  (*isInv == false)? state->curPos : -state->curPos, 13, 10);
		usrOut->Send ( myName, strlen(myName));		
		ret = true;
	}
	else if (fNum == GET_SPEED)
	{
		sprintf (cmdAndData, "Vel? %d%c%c", smCtl->GetSpeed(), 13,10);
		usrOut->Send( myName, strlen(myName));
		ret = true;
	}	
	if ( fNum == MOVE )
	{
		smCtl->Move((*isInv == false)? data : -data);
		ret = true;
	}
	else if ( fNum == STOP )
	{
		smCtl->Stop();
		sprintf (cmdAndData, "Stop %d%c%c", (*isInv == false)? state->curPos : -state->curPos, 13, 10);
		usrOut->Send(myName, strlen(myName));		
		ret = true;
	}
	else if ( fNum == SET_SPEED )
	{
		smCtl->SetSpeed ( data );
		ret = true;
	}
	else if (fNum == IS_CALIBRATE)
	{
		sprintf (cmdAndData,  "FindRef? %d%c%c", ( state->isClbrt == false)? 0 : 1, 13, 10);
		usrOut->Send(myName, strlen(myName));
		ret = true;
	}
	else if ( fNum == CALIBRATE)
	{
		smCtl->Move ( -99999);
		waitSens = true;
		ret = true;
		GetOKLed1()->Toggle();
	}
	else if (fNum == GET_INVERTED_MODE)
	{
		sprintf (cmdAndData,  "Inverted? %d%c%c", ( *isInv == false)? 0 : 1, 13, 10);
		usrOut->Send(myName, strlen(myName));
		ret = true;
	}	
	else if (fNum == SET_INVERTED_MODE)
	{
		*isInv = ( data == 0)? false : true;
		char bfr[4];
		bfr [0] = (*isInv == false)? 0 : VAL_TRUE;
		GetAT24C256Writer()->PageFastWrite ( mAddr, bfr, 1);
		ret = true;
	}		
	else if (fNum == SET_CURR_START)
	{
		smCtl->SetStartCur( data);
		ret = true;
	}
	else if (fNum == SET_CURR_WORK)
	{
		smCtl->SetWorkCur( data);
		ret = true;
	}
	else if (fNum == SET_CURR_RETENTION)
	{
		smCtl->SetKeepCur( data );
		ret =true;
	}
	else if (fNum == SET_DIVIDER)		
	{
		smCtl->SetDivider(data);
		ret = true;
	}
	else if (fNum == START)
	{
		smCtl->Move((*isInv == false)? preset : -preset);
		ret = true;
	}
	else if (fNum == PRESET)
	{
		preset = data;
		ret = true;
	}
	else if (fNum == CTL_MODE)
	{
		if (data == 0)
		{
			*modeControl = true;
			ret = true;
		}
		else if (data == 1)
		{
			*modeControl = false;
			ret = false;
		}
//		sprintf (buf, "set: %d%c%c", (int) *modeControl, 13, 10);
//		usrOut->Send(buf, strlen(buf));
	}
	else if (fNum == GET_CTL_MODE)
	{
		sprintf (cmdAndData,  "Control? %d%c%c", ((*modeControl  != false) || (*isManCt == false))? 0 : 1, 13, 10);
		usrOut->Send(myName, strlen(myName));
		
//		sprintf (buf, "get: %d%c%c", (int) *modeControl, 13, 10);
//		usrOut->Send(buf, strlen(buf));
		ret = true;
	}
	else if (fNum == GET_DAC)
	{
		sprintf (cmdAndData, "DAC? %d%c%c", etaDac - 0x7fff, 13, 10);
		usrOut->Send ( myName, strlen(myName));		
		ret = true;
	}
	*isInv = false;
	GetOKLed2()->Send(waitSens);
	GetOKLed3()->Send(state->leftEnd);

	if(waitSens != false && state->leftEnd != false)
	{
		smCtl->SetPosition(0);
		waitSens = false;
			GetOKLed1()->Toggle();
	}
	return ret;
}

DoubleSMMod::DoubleSMMod(AbstractFPModul* x, AbstractFPModul* y) : first (x), second (y)
{
}

bool DoubleSMMod :: Router( unsigned int fNum, int data)
{
	bool ret;
	if(fNum == PRESET || fNum == START)
	{
		first->Router(fNum, data);
		second->Router(fNum, data);
		ret = true;
	}
	else 
		ret = false;
	return ret;
}

//	AbstractBuffOut* usrOut;
//	AbstractStepMotorCtl* crisMtr;
//	AbstractStepMotorCtl* filtrMtr;
//	AbstractStepMotorCtl* etaHDr;
//	bool*  isCrOk;
//	bool*  isFlOk;

GeneralModul::GeneralModul ( AbstractStepMotorCtl* crMotor, AbstractStepMotorCtl* fiMotor, AbstractStepMotorCtl* etHDrive,  AbstractBuffOut* ifc,
						  bool* crOk, bool* fiOk, const bool* man)
{
	crisMtr = crMotor;
	filtrMtr = fiMotor;
	etaHDr = etHDrive;
	usrOut = ifc;
	isCrOk = crOk;
	isFlOk = fiOk;
	isManCt = man;
}

bool GeneralModul::Router(unsigned int fNum, int data)
{
	bool ret = false;
	if (fNum == STOP)
	{
		ret = true;
		crisMtr->Stop();
		filtrMtr->Stop();
		etaHDr->Stop();
	}
	else if (fNum == GET_CONNECTIONS_STATE)
	{
		char buf [16];
		 unsigned char out = ((*isCrOk && *isFlOk) == true)? 1 : 0;
//		 unsigned char out = (*isFlOk == true)? 1 : 0;
		out |= (*isManCt == false)? 0 : 2;
		sprintf (buf, "AllConState? %d%c%c", out, 13, 10);
		usrOut->Send(buf, strlen (buf));
	}		
	return ret;
}
bool StubModul::Router(unsigned int fNum, int data)
{
	bool ret;
	if(fNum == INDICATE_SCAN)
	{
		if (data == 0)
		{
			pOut->Set();
			ret = true;
		}
		else if (data  == 1)
		{
			pOut->Clear();
			ret = true;
		}
		else 
			ret = false;
	}
	else
		ret = false;
	return ret;
}



//							ModulFPsm::ModulFPsm(AbstactStepMotorCtl* stMotCtl, AbstractPinOut* lfRedLed, AbstractPinOut* lfGreenLed, AbstractPinOut* rgRedLed, AbstractPinOut* rgGreenLed)
//							{
//								smCtl = stMotCtl;
//								smCtl->GetState(&state);	
//								leftRed = lfRedLed;
//								leftGreen = lfGreenLed;
//								rightRed = rgRedLed;
//								rightGreen = rgGreenLed;
//							}

//							bool ModulFPsm::Router(unsigned int fNum, int data)
//							{
//								unsigned int func;
//								int value;
//							//	if(fNum == REMOTE_CTL)
//							//	{
//							//		//DAbaParser->getFun, SDAta
//							//	}
//							//	else 
//							//	{
//							//		func = fNum;
//							//		value = data;
//							//	}
//								if(state.speedInst != 0 &&   fNum == STOP)
//									smCtl->Stop();
//								else if (fNum == MOVE)
//									smCtl->Move ( data );
//								else
//									smCtl->GetState ( &state );
//								leftGreen->Send   ( (state.speedInst < 0  || (fNum == MOVE && data < 0 && state.leftEnd == false))?  true : false);
//								rightGreen->Send ( (state.speedInst > 0 || (fNum == MOVE && data > 0 && state.rightEnd == false))?  true : false);	
//								leftRed->Send(state.leftEnd);
//								rightRed->Send(state.rightEnd);
//								
//								return true;
//							}

//							ModulSMPassive::ModulSMPassive ( AbstactStepMotorCtl* stMotCtl, SMState* staSM, AbstractBuffOut* ifc )
//							{
//								state = staSM;
//								smCtl = stMotCtl;
//								usrOut = ifc;	
//							}

//							//	DO_NOTHING = 0,  
//												//			IS_MOVE,
//												//			GET_VAL,
//												//			GET_SPEED,
//												//			GET_END_SENS,

//							//			IS_CALIBRATE,	
//							//			GET_CONNECTIONS_STATE,
//							//	FUNC_NUM


//							bool ModulSMPassive::Router (unsigned int fNum, int data)
//							{
//								bool ret = false;
//								char buf[32];
//								if (fNum == IS_MOVE)
//								{
//									sprintf (buf, "%d%c%c", ( smCtl->isMoving()  == 0 )? 0 : 1, 13, 10  );
//									usrOut->Send ( buf, strlen(buf) );
//									ret = true;
//								}
//								else if (fNum == GET_END_SENS)
//								{
//									char end = (state->leftEnd != false)? 1 : 0;
//									end |= (state->rightEnd != false)? 2 : 0;
//									sprintf (buf, "%d%c%c", end, 13, 10);
//									usrOut->Send( buf, strlen(buf) );
//									ret = true;
//								}
//								else if (fNum == GET_VAL)
//								{
//									sprintf (buf, "%d%c%c", state->curPos, 13, 10);
//									usrOut->Send(buf, strlen(buf));		
//									ret = true;
//								}
//								else if (fNum == GET_SPEED)
//								{
//									sprintf (buf, "%d%c%c", smCtl->GetSpeed(), 13,10);
//									usrOut->Send(buf, strlen(buf));
//									ret = true;
//								}
//								return ret;
//							}


//							ModulSMActive::ModulSMActive ( AbstactStepMotorCtl* stMotCtl,  SMState* staSM,  AbstractBuffOut* ifc, AbstractFPModul* passive,
//														AbstractPinOut* lfRedLed,  AbstractPinOut* lfGreenLed,  AbstractPinOut* rgRedLed,  AbstractPinOut* rgGreenLed)
//							{ 
//								state = staSM;
//								smCtl = stMotCtl;
//								usrOut = ifc;	
//								shadow = passive;
//								leftRed = lfRedLed;
//								leftGreen = lfGreenLed;
//								rightRed = rgRedLed;
//								rightGreen = rgGreenLed;
//							}


//							//		MOVE,
//							//		SET_SPEED,
//							//		STOP,
//							//		CALIBRATE

//							bool ModulSMActive::Router ( unsigned int fNum, int data )
//							{
//								bool ret;
//							//		if (fNum == IS_MOVE)
//							//	{
//							//		sprintf (buf, "%d%c%c", ( smCtl->isMoving()  == 0 )? 0 : 1, 13, 10  );
//							//		usrOut->Send ( buf, strlen(buf) );
//							//		ret = true;
//							//	}
//								ret = shadow->Router(fNum, data);
//								if (ret == false)
//								{
//									if ( fNum == MOVE )
//									{
//										smCtl->Move(data);
//										ret = true;
//									}
//									else if ( fNum == STOP )
//									{
//										smCtl->Stop();
//										ret = true;
//									}
//									else if ( fNum == SET_SPEED )
//									{
//										smCtl->SetSpeed ( data );
//										ret = true;
//									}
//									else if ( fNum == CALIBRATE)
//									{
//										smCtl->Move ( -99999);
//										ret = true;
//									}
//								}
//								return ret;
//							}




