#include <StepMotorCtl.h>
#include <stdio.h>
#include <ParserFP.h>
#include <Extractor.h>
#include <InterfaceParticularity.h>
#include <constants.h>
#include <boardDevices.h>
//E:\d2\www\2013Proj\soft\bank\Standard\Strd0\Ctl\StepMotorCtl.cpp
StepMotorClt::StepMotorClt(AbstractBuffIn* strIn, AbstractBuffOut* strOut, SMState* smStatus, unsigned int addR)
{
	stin = strIn;
	stout = strOut;
	speed = 2000;
	stt = smStatus;
	memAddr = addR;
	shiftPos = 0;
	refreshCounter = 20;
	Router (0);
	DelayMs (20);
	Router (0);
	DelayMs(20);
	Router (0);
	DelayMs (20);
	Router (0);
	DelayMs(20);
	memData buff;
	GetAT24C256Reader()->Read( memAddr, buff.block, 4); 
	if (buff.positions > -1000000 && buff.positions < 1000000)
	{
		savedPos = buff.positions;
		shiftPos = savedPos - stt->curPos;
		stt->curPos  = savedPos;
	}
	else
	{
		savedPos = buff.positions = stt->curPos;
		shiftPos = 0;
		GetAT24C256Writer()->Write( memAddr, buff.block, 4);
	}	
	isMoveEnable = 0;
}

#include <boardDevices.h>
void StepMotorClt::Move (int nSteps)
{
	char buff [32];
	sprintf( buff, "move %d%c%c", nSteps, 13, 10);	
	stout->Send(buff, strlen(buff));	
	tgStep = nSteps;
	stt->speedInst = (nSteps < 0)? -1 * speed : speed;
	isMoveEnable = 2;
}

void StepMotorClt::Stop()
{
	char buff [32];
//	GetOKLed1()->Toggle();
	sprintf( buff, "stop%c%c",  13, 10);	
	stout->Send(buff, 6);	
	isMoveEnable = 2;
	stt->speedInst = 0;
}

bool  StepMotorClt::Router( char mode )
{
	bool ret = false;
	char buff[256];
	int len  = stin->Get(buff);
	while ( len > 0  )
	{
		if ( StringComparator ( buff, "state", 5 ) != false)
		{
			len -= 6;
			if(len > 0)
			{

				char* pos = buff + 6;
				unsigned int isMoving, edges, isCI;
				int sMPosition;//, real;
				int dataLen =  GetUnsignedInt(pos, len, &isMoving);/// MovinG???

				if( dataLen > 0 && isMoving < 2 )
				{
					len -= 2;
					if(len > 0)
					{
						pos += 2;	
						dataLen =  GetUnsignedInt(pos, len, &edges); ///Edges?
						if( dataLen > 0 && edges < 3 )	
						{
							len -=2;
							if(len > 0)
							{
								pos += 2;
								dataLen =  GetSignedInt (pos, len, &sMPosition); ///Targets
								if( dataLen > 0 )	
								{
									len -= dataLen + 1 ;
									if (len > 0)
									{
										pos += dataLen +1;
										dataLen =  GetUnsignedInt (pos, len, &isCI); ///realSteps
										if(dataLen > 0)
										{
											ret = true;
											if(edges == 0)
											{
												stt->leftEnd = stt->rightEnd = false;
											}
											else 
											{
												if (edges == 1)
												{
													stt->leftEnd  = true;
													shiftPos = 0;
												}
												stt->rightEnd = (edges == 2)? true : false;
											}
											if (isMoveEnable <= 0)
											{
												if(isMoving != 0)
													stt->speedInst = (tgStep < 0 )? -1 * speed : speed;
												else
												stt->speedInst = 0;
											}
											else
												--isMoveEnable;
											stt->isClbrt = (isCI == 0)? false : true ;	
											stt->curPos = sMPosition + shiftPos;
										
						
											
										}
									}																			
								}						
							}						
						}
					}
				}
			}	
		}
		len  = stin->Get(buff);
	}
	static const char STATE_REQ[] = {'s', 't', 'a', 't', 'e', 13, 10};
	stout->Send ( STATE_REQ, 7 );
	if (--refreshCounter < 0)
	{
		refreshCounter = 20;
		if(stt->speedInst == 0 && stt->curPos != savedPos)
		{
			memData bufff;
			bufff.positions = savedPos = stt->curPos;
			GetAT24C256Writer()->PageFastWrite (memAddr, bufff.block, 4);
		}
	}
	return ret;
}

 bool StepMotorClt::GetState ( SMState* state )
{
	state->leftEnd = stt->leftEnd;;
	state->rightEnd = stt->rightEnd;
	state->speedInst = stt->speedInst;
	state->curPos = stt->curPos;
	state->isClbrt = stt->isClbrt;
	return true;
}

 bool StepMotorClt::GetPosition( int* steps)
{
	* steps = stt->curPos;
	return true;
}

unsigned int StepMotorClt::GetSpeed()
{
	return speed;
}

void StepMotorClt::SetSpeed (unsigned int stepsPerSecond)
{
	char buff [32];
	sprintf( buff, "speed %d%c%c", stepsPerSecond, 13, 10);	
	stout->Send(buff, strlen(buff));	
	speed = stepsPerSecond;
}

void StepMotorClt::SetStartCur (unsigned int qw) 
{
	char buf[16];
	sprintf (buf, "iS %d%c%c", qw, 13, 10);
	stout->Send(buf, strlen(buf));
}

void StepMotorClt::SetWorkCur (unsigned int qw)
{
	char buf[16];
	sprintf (buf, "iW %d%c%c", qw, 13, 10);
	stout->Send(buf, strlen(buf));
}

void StepMotorClt::SetKeepCur (unsigned int qw)
{
	char buf[16];
	sprintf (buf, "iR %d%c%c", qw, 13, 10);
	stout->Send(buf, strlen(buf));
}

void StepMotorClt::SetDivider ( unsigned int div )
{
	char buf[16];
	sprintf (buf, "dv %d%c%c", div, 13, 10);
	stout->Send(buf, strlen(buf));
}



HalvoDrvCtl::HalvoDrvCtl ( unsigned int * fpDac, double*  fpAdc, SMState* smStatus )
{
	dac = fpDac;
	qwpmSecAb = 10.0;
 	qpSAb = 10000.0;
	qwpmSec = qpS = 0.0;
	val = tgVal = 0x7fff;
	realVal = (double) val;
	delta = 0;
	adc = fpAdc;
	stt = smStatus;
}

bool HalvoDrvCtl::Router(char mode)
{ 
	if(mode == MANUAL)
	{
		val = (*adc != ERR_VAL)? (int) *adc : val;
		tgVal = val;
		realVal = (double) val;
	}
	else
	{
		realVal +=  qwpmSec;
		int  tmpVal  = (int) realVal;
		if((delta > 0 &&  tmpVal < tgVal) ||  (delta < 0 &&  tmpVal > tgVal)  ) 
			val = tmpVal;
		else
		{
			val = tgVal;
			realVal = (double) tgVal;
			delta = 0;
			qpS = qwpmSec = 0.0;
			stt->speedInst = 0;
		}	
	}
	*dac = val;
	stt->curPos = *adc - 0x7fff; //val - 0x7fff;
	stt->leftEnd = (val > LEFT_EDGE)? false : true;
	stt->rightEnd = (val < RIGHT_EDGE)? false : true;		
 	return true;
}

void HalvoDrvCtl::Move(int  nSteps)
{
	if  (nSteps <= RIGHT_EDGE && nSteps >= LEFT_EDGE)
	{
		int pos = nSteps + 0x7fff;
		tgVal = pos;
		delta = tgVal - val;		
		stt->speedInst = qpS = (delta < 0)? -qpSAb : qpSAb;
		qwpmSec = qpS / 1000.0;
	}
	else if (nSteps == -99999)
	{
		val = tgVal = 0x7fff;
		realVal = (double) tgVal;
		delta = 0;
		qpS = qwpmSec = 0.0;
		stt->speedInst = 0;
		*dac = val;
	}
}

void HalvoDrvCtl::Stop()
{
	tgVal  = val;
	delta = 0;
	stt->speedInst = qpS = qwpmSec = 0.0;
}
	
bool HalvoDrvCtl::GetState(SMState* state)
{
	state->leftEnd = (val == LEFT_EDGE)? true : false;
	state->rightEnd = (val == RIGHT_EDGE)? false : true;
	state->curPos = val;
	state->speedInst = (int) qpS; 
	return  true;
}

bool HalvoDrvCtl::GetPosition( int* steps)
{
	*steps = val;
	return  true;
}

void HalvoDrvCtl::SetSpeed (unsigned int stepsPerSecond)
{
	qpSAb = (double) stepsPerSecond;
	qwpmSecAb = qpSAb / 1000.0;
	stt->speedInst =  qpS  = (delta < 0 )? -qpSAb : qpSAb;
	qwpmSec = qpS / 1000.0;
}

unsigned int  HalvoDrvCtl::GetSpeed ()
{
	return (int) qpSAb;
}

int HalvoDrvCtl::isMoving()
{
	return (int) qpS;
}





