#include <Extractor.h>
//E:\d2\www\2013Proj\soft\bank\Standard\Strd0\Convertors\Extractor.cpp
////////=========  String to digit
int GetSeparatorLen(const char* inS, unsigned int len)
{
	int pos = 0;
	while ( pos < len && inS[pos] == ' ')
		++pos;
 	return pos;
}

int GetUnsignedInt ( const char* inS, unsigned int len, unsigned int* val )
{
	signed char symb  = inS[0] -	'0';
	int pos = 0;
	 if(symb > 0  && symb < 10)	
	{	
		*val = 0; 
		while(++pos <= len && symb >= 0 && symb < 10)
		{
			*val *= 10;
			*val += symb;
			symb  = inS[pos] - '0';
		}
		--pos;
	}
	else 	if(symb == 0 )
	{
		*val = 0;
		pos = 1;
//		symb  = inS[1] -	'0';
//		if(symb < 0 || symb > 9)
//		{
//			*val = 0;
//			pos = 1;
//		}
//		else 
//			pos = -1;
	}
	else 
		pos = -1;
	return pos;
}

int GetSignedInt(const char* inS, unsigned int len, int* val)
{
	bool isNegativ = (inS[0] == '-')? true : false;
	int pos = (isNegativ == false)? 0 : 1;
	unsigned int uVal;
	int dgLen = GetUnsignedInt(inS + pos, len - pos, &uVal);
	if(dgLen > 0)
	{
//		char  bfr[64];
		//sprintf(bfr, " uVal0 =%d ", uVal);
	//	GetUARTtx1()->Send(bfr);
		*val = uVal;
		*val = (isNegativ)? -*val : *val;
//			sprintf(bfr, " val =%d, isNeg =  %d",  *val , (int) isNegativ);
//		GetUARTtx1()->Send(bfr);
		pos += dgLen;
	}
	else
		pos = -1;
	return pos;
}

int DoubleTailExtractor(const char* inS, unsigned int len, double* val)
{
	double factor = 0.1;
	int pos = 0;
	char symb = inS[0];
	bool ret  = (symb >= '0' && symb <= '9')? true : false;
	if(ret == true)
	{
		*val = 0.0;
		signed int digit ;
		
		do 
		{			
			digit = symb - '0';
			*val += (double) digit * factor;
			factor *= 0.1;
			++pos;
			symb = (--len > 0)? inS[pos] : 'x';
		}
		while ( symb  >= '0' && symb <= '9');
	}
	return pos;
}

int GetDouble (const char* inS, unsigned int len, double* val)
{
	int iVal;
	int iPos = GetSignedInt(inS, len, &iVal);
	int pos;
//	char bfr[64];
//	sprintf (bfr, " iPos= %d,  iVal = %d   ", iPos, iVal);
//	GetUARTtx1()->Send(bfr);
	if (iPos > 0) //&& iVal != 0)
	{
		if(iVal != 0)
		{
			if(inS[iPos] == '.')
			{
				pos = iPos + 1;
				pos += DoubleTailExtractor ( inS + pos, len - pos, val );					
				*val = (iVal < 0)?  (double) iVal - *val :  (double) iVal + *val ;
			}
			else
			{
				pos = iPos;
				*val = (double) iVal;
			}
		}
		else 
		{
			if(inS[iPos] == '.')
			{
				bool isNeg = (inS[0] == '-')? true : false;
				pos = iPos + 1;
				pos += DoubleTailExtractor ( inS + pos, len - pos, val );					
				*val = (isNeg)? - *val :  *val ;
			}
			else
			{
				pos = iPos;
				*val = 0.0;
			}
		}
	}
	else
	{	
		bool isNegativ ;
		if (inS[0] == '-')
		{
			isNegativ = true;
			pos = 1;
		}
		else 
		{
			isNegativ = false;
			pos = 0;
		}
//		if(inS[pos] == '0')
//		{
//			++pos;
//		}
		if(inS[pos] == '.')
		{
			++pos;
			int rPos = DoubleTailExtractor(inS + pos, len - pos, val);
//			char bfr[64];
//			sprintf (bfr, " rPos = %d,  pos = %d, isNegativ %d", rPos, pos, (int) isNegativ);
//			GetUARTtx1()->Send(bfr);
			if(rPos > 0)
			{
				pos += rPos;
				*val = (isNegativ)? -*val  : *val;
			}
			else
				pos = -1;
		}	
		else
			pos  = -2;
	}
	return pos;
}


//////////////////////////////////////////////////////////////////////////////////////


