#include <Convertor.h>
#include <stdio.h>
#include <string.h>
#include <Extractor.h>

LineConvertor::LineConvertor(AbstractMemoryIn* memoryIn, AbstractMemoryOut* memoryOut, 
unsigned int memAddr, const char* headerStr,  unsigned int mini_X, unsigned int maxi_X,
  double mini_Y, double maxi_Y, const char* units, unsigned char tolrs, double minimum, double maximum) 
 : AbstractConvertor ( units )
{
	strcpy ( hdr, headerStr );
	hdrLen = strlen ( hdr );
	SetTolerance ( tolrs );
	fromMem = memoryIn;
	toMem  = memoryOut;	
	addr = memAddr;
	SetMinMaxs(mini_X, maxi_X, minimum, maximum);
	AddPoint(mini_X, mini_Y);
	AddPoint (maxi_X, maxi_Y);
	if (Restore() == false)
		Save();
	
}

bool LineConvertor::IsCheckSummOk(const record*  rec)
{
	return ( rec->chsum == (float) rec->x_0 + (float) rec->x_1 + rec->y_0 + rec->y_1 )? true : false;
}	

void LineConvertor::Save()
{
	stRec rcdr;
	rcdr.dgs.x_0 = (unsigned short) clbX[0];
	rcdr.dgs.x_1 = (unsigned short) clbX[1];
	rcdr.dgs.y_0 = (float) clbY[0];
	rcdr.dgs.y_1 = (float) clbY[1];
	rcdr.dgs.chsum = (float)rcdr.dgs.x_0 + (float)rcdr.dgs.x_1 + rcdr.dgs.y_0 + rcdr.dgs.y_1;
	toMem->Write ( addr, rcdr.str, 16);
}

#include <BoardDevices.h>	
bool LineConvertor::Restore()
{
	stRec rcdr;
	fromMem->Read (addr, rcdr.str, 16);
	bool ret = IsCheckSummOk(  &rcdr.dgs );
	if( ret == true)
	{
		AddPoint((unsigned int) rcdr.dgs.x_0, (double) rcdr.dgs.y_0);
		AddPoint((unsigned int) rcdr.dgs.x_1, (double) rcdr.dgs.y_1);
	}
	return ret;		
}

	
//void LineConvertor::SetMinMaxs ( double minimum, double maximum)
//{
//	min = minimum;
//	max = maximum;
//														//	brdX [0] = shiftX = clbX[0] = (double) minAbc;
//														//	brdX [1] =  clbX[1] =  (double) maxAbc;
//														//	minY = brdY [0] = shiftY =  clbY[0]= minOrd;
//														//	maxY =  brdY [1] = clbY[1]  = maxOrd;
//														//	scale = (brdY[1] - brdY[0]) / (brdX[1] - brdX[0]);
//														//	minX = minAbc;
//														//	maxX  = maxAbc;
//}
	
double LineConvertor::GetValue( unsigned int dataIn )
{
	double ret = ((double) dataIn  -  shiftX) * scale + shiftY;
	ret = (ret > maxY)? maxY :  ret;
	ret = (ret < minY)? minY : ret;
	return ret; 
}
	
unsigned int LineConvertor::GetDigitInput (double val)
{
	double tmp = (val - shiftY) / scale + shiftX;
	unsigned int ret = (tmp >(double) maxX)? maxX : tmp;
	ret = (tmp < (double) minX)? minX : tmp;
	return ret;
}


void LineConvertor::AddPoint (unsigned int x, double y)
{
	if( ( x - minX ) >  ( maxX - x ) )
	{
		clbX[1]= (double) x;
		clbY[1]  = y;
	}
	else
	{
		clbX[0] = (double) x;
		clbY[0] = y;
	}
	scale = (clbY[1] - clbY[0]) / ( clbX [1] - clbX [0] );
	scale = (scale == 0.0)? 0.000001 : scale;
//	double yo= clbY[1] - clbX[1] * scale; //Y axis cross
	double xo = clbX[1] - clbY[1] / scale; //X axis cross
	shiftX = shiftY / scale + xo;
}
	

void LineConvertor::Reset()
{
	SetMinMaxs(minX, maxX, minY, maxY);
}


///strig format
//bool LineConvertor::IsCheckSummOk(const char* buff)
//{
//	unsigned int summ = 0;
//	bool ret;
//	unsigned int len = strlen(buff);
//	for ( int i = len; i > 0 ; )
//		summ += buff[--i];
//	++len;
//	int pos = GetSeparatorLen(buff + len, 48 - len);
//	if (pos >0)
//	{
//		pos += len;
//		unsigned  int cs;
//		pos = GetUnsignedInt(buff + pos, 48 - pos, &cs);
//		ret = ((pos > 0 )  && (cs == summ))? true : false;
//	}
//	else
//		ret = false;
//	return ret;
//}

//void LineConvertor::Save()
//{
//	char buf [48];// = {'Y'};
//	for (int i = 48; i > 0; )
//		buf[--i] = ' ';
//	sprintf (buf, "%s %d %d %.*f %.*f ", hdr, (unsigned int) clbX[0], (unsigned int) clbX[1], tlc, clbY[0], tlc, clbY[1]);
//	unsigned int summ = 0;
//	for ( int i = strlen(buf); i > 0 ; )
//		summ += buf[--i];
//	char csStr[6];
//	sprintf(csStr, "%d ", summ);
//	int j = 48;
//	for (int i = strlen (csStr); i > 0;)
//		buf[--j] = csStr[--i];
//	toMem->Write ( addr,  buf, 48);
//}
//#include <BoardDevices.h>	
//bool LineConvertor::Restore()
//{
//	char buf [48];
//	unsigned int x[2];
//	double y[2];
//	fromMem->Read (addr, buf, 48);
//	bool ret = IsCheckSummOk(  buf );
//	if( ret == true)
//	{
////		GetUARTtx2()->Send(" checkSummOk");
////		DelayMs(10);
//		for(int i = hdrLen; i >  0 && ret == true;)
//			ret = (hdr[--i] == buf[i])? true: false;
//		if (ret == true)
//		{		
////			GetUARTtx2()->Send(" headerOk");
////			DelayMs(10);
//			int pos = GetSeparatorLen( buf + hdrLen, 48);
//			if(pos > 0)
//			{
//				pos += hdrLen;
////				char txt [64];
////				sprintf (txt, "separator1  = %d",  pos);
////				GetUARTtx2()->Send(txt);
////				DelayMs(10);
//				int delta = GetUnsignedInt( buf + pos, 48 - pos, &x[0]);			
//				if(delta > 0)
//				{			
////					sprintf (txt, " x[0]  = %d",  x[0]);
////					GetUARTtx2()->Send(txt);
////					DelayMs(10);

//					pos +=delta;
//					delta = GetSeparatorLen(buf + pos, 48 - pos);
//					if (delta > 0)
//					{
//						pos += delta; 
//						delta = GetUnsignedInt(buf + pos, 48 - pos, &x[1]);
//						if(delta > 0)
//						{
//							pos += delta; 
//							delta = GetSeparatorLen(buf + pos, 48 - pos);
//							if (delta > 0)
//							{
//								pos += delta;
//								delta = GetDouble( buf + pos, 48 - pos, &y[0]);					
//								if(delta > 0)
//								{
//									pos += delta; 
//									delta = GetSeparatorLen(buf + pos, 48 - pos);
//									if (delta > 0)
//									{
//										pos += delta;
//										delta = GetDouble(buf + pos, 48 - pos, &y[1]);		
//										ret = (delta > 0)? true : false;
//									}
//									else // y0 sp
//									ret = false;
//								}
//								else // y0
//									ret = false;							
//							}// x1  sp
//							else //
//								ret = false;
//						}// x1
//						else
//							ret = false;
//					}// x0 sp
//					else
//						ret = false;
//				} // x0
//				else
//					ret = false;
//			}
//			else/// CMD_sp
//				ret = false;
//		}
//	}
//	if (ret == true)
//		for(int i = 0; i < 2; ++i)
//			AddPoint(x[i], y[i]);
//	return ret;		
//}
