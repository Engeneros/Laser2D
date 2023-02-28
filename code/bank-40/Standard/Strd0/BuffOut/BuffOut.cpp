#include <BuffOut.h>
#include <string.h>
#include <BoardDevices.h>

BuffOut::BuffOut(AbstractIOasy* ifc, unsigned int size,  unsigned long isrAddr ) : AbstractBuffOut(size)
{
	oIfc = ifc;
	wrPos = rdPos = 0;
	hwTxBfrSz = oIfc->GetTxHwBuffSz();
	hwRxBfrSz = oIfc->GetRxHwBuffSz();
	adrInt = isrAddr;
	if( adrInt != 0 )
		oIfc->SetTxISRAddr(adrInt);		
}

bool BuffOut::Send(const char *inp, unsigned int size)
{
	size = (size == 0)? strlen(inp) + 1 : size;
	int sizeToEnd = buffSz - wrPos;
	int sizeFirst =  (size > sizeToEnd)? sizeToEnd : size;
	int sizeSecond  = size - sizeFirst; 
	int inBuffPos = 0;
	for(int i = sizeFirst; i > 0;--i)
		buff[wrPos++] = inp[inBuffPos++];		
	wrPos %= buffSz;
	for(int i = sizeSecond; i > 0; --i)
		buff[wrPos++] = inp[inBuffPos++];	
	return Router();
}

bool  BuffOut::Router()
{
	bool ret;
	if((rdPos != wrPos) && (oIfc->IsTxReady() == true))
	{
		int  d = (int) wrPos - (int) rdPos;
		if (d > 0 )
		{
			unsigned int s = ((unsigned int) d > hwTxBfrSz)? hwTxBfrSz : d;
			oIfc->Tx((const unsigned char*) buff + rdPos, s);
			rdPos += s;
		}
		else 
		{
			int first = buffSz - rdPos;
//			int rd = rdPos;			
			if(first > hwTxBfrSz)
			{
				oIfc->Tx((const unsigned char*) buff + rdPos, hwTxBfrSz);
				rdPos +=hwTxBfrSz;
			}
			else
			{
				oIfc->Tx((const unsigned char*) buff + rdPos, first);
				rdPos =  ( first + wrPos > hwTxBfrSz)? hwTxBfrSz - first : wrPos;
				oIfc->Tx((const unsigned char*) buff, rdPos);
			}		
		}			
		ret = true;
	}
	else
		ret = false;
	return ret;
}

//bool BuffOut::Send(const char *inp, unsigned int size)
//{
//	size = (size == 0)? strlen(inp) + 1 : size;
//	int sizeToEnd = buffSz - wrPos;
//	int sizeFirst =  (size > sizeToEnd)? sizeToEnd : size;
//	int sizeSecond  = size - sizeFirst; 
//	int inBuffPos = 0;
//	for(int i = sizeFirst; i > 0;--i)
//		buff[wrPos++] = inp[inBuffPos++];		
//	wrPos %= buffSz;
//	for(int i = sizeSecond; i > 0; --i)
//		buff[wrPos++] = inp[inBuffPos++];	
//	return Router();
//}

//bool  BuffOut::Router()
//{
//	bool ret;
////	//const char stdBfr[] = "0123456789ABCDEFGHIJKLMNOPRST";
//	if((rdPos != wrPos) && (oIfc->IsTxReady() == true))
//	{
//		int  d = (int) wrPos - (int) rdPos;
//		unsigned int s;
//		if( d > 0)
//		{
//			s = ((unsigned int) d > hwTxBfrSz)? hwTxBfrSz : (unsigned int) d;
//			oIfc->Tx ((const unsigned char*) buff + rdPos, s);
//			rdPos += s;
//		}
//		else 
//		{
//			d += (int) buffSz;
//			int first = buffSz - rdPos;
//			int delta =(int) hwTxBfrSz - first;
//			if( delta <= 0)
//			{
//				oIfc->Tx ( (const unsigned char*) buff + rdPos, hwTxBfrSz);
//				rdPos  += hwTxBfrSz;
//				rdPos %= buffSz;
//			}
//			else
//			{
//				oIfc->Tx ( (const unsigned char*) buff + rdPos, first);
//				int second = (d < (int) hwTxBfrSz)? d - first : delta;
//				oIfc->Tx ( (const unsigned char*) buff, second);
//				rdPos   = (unsigned int) second;
//			}
//		}
//		ret = true;
//	}
//	else
//		ret = false;
//	return ret;
//}
