#include <Convertor-D.h>
#include <string.h>
#include <BoardDevices.h>	
//E:\d2\www\2013Proj\soft\bank\Standard\Strd0\Convertors\Convertor-D.cpp
//E:\d2\www\2013Proj\soft\draft\0040binaryRack=17.10.2016\sw\puC\puC40_0\code\bank-40\Standard\Strd0\Convertors\Convertor-D.cpp

LineConvertor_D::LineConvertor_D ( AbstractMemoryIn* memoryIn, AbstractMemoryOut* memoryOut,
	unsigned int memAddr, const char* headerStr,
	double mini_X, double maxi_X, double mini_Y, double maxi_Y,
	double x0, double x1, double y0, double y1)
{
	strcpy (hdr, headerStr );
	hdrLen = strlen ( hdr );
	fromMem = memoryIn;
	toMem  = memoryOut;	
	addr = memAddr;
	SetMinMaxs ( mini_X, maxi_X, mini_Y, maxi_Y );
	if (Restore() == false)
	{
//		vd11Yellow.Toggle();
		vd10Green.Toggle();
		AddPointLeft    (x0, y0);
		AddPointRight (x1, y1);
		Calibrate();
		DelayMs (5);
		WrHdr();
		DelayMs(5);
	}	
}

bool LineConvertor_D::IsCheckSummOk(const record*  rec)
{
	return   ( rec->checkSumm ==  rec->x_0 + rec->x_1 + rec->y_0 + rec->y_1 )? true : false;
}	

void LineConvertor_D::Save()
{
//	char buf [128];
	stRec rcdr;
	rcdr.dgs.x_0 = clbX[0];
	rcdr.dgs.x_1 =  clbX[1];
	rcdr.dgs.y_0 =  clbY[0];
	rcdr.dgs.y_1 =  clbY[1];
	rcdr.dgs.checkSumm = rcdr.dgs.x_0 + rcdr.dgs.x_1 + rcdr.dgs.y_0 + rcdr.dgs.y_1;
	bool isOk =  toMem->Write ( addr, rcdr.str, 40);  //PageFastWrite   ( addr, rcdr.str, 40);//
//	if (isOk != false)
//	{
//		vd11Yellow.Toggle();
//		uartTx1.Send(hdr, hdrLen);
//		sprintf (buf, "-save-x0=%.2f,  x1=%.2f, y0=%.2f, y1=%2f, sc=%.5f, sh=%.2f%c%c",   rcdr.dgs.x_0, rcdr.dgs.x_1, rcdr.dgs.y_0,  rcdr.dgs.y_1, scale, shiftX, 13, 10);
//		uartTx1.Send(buf);
//	}
//	else
//		for(int i = 0; i <1000000; ++i)
//			vd10Green.Toggle();
}

void LineConvertor_D::WrHdr()
{
	toMem->Write( addr + 40, hdr, hdrLen );
}

bool LineConvertor_D::Restore()
{
	stRec rcdr;
	fromMem->Read (addr, rcdr.str, 48);
//	char buf[128];
	bool ret = true;
	bool tmp ;
	for (int i = 0; i < hdrLen; ++i)
	{
		tmp = (rcdr.dgs.name[i] == hdr[i]) ?  true : false;
		ret = ret && tmp;
	}
	if ( ret == true )
	{
		ret = IsCheckSummOk(  &rcdr.dgs );
		if( ret == true)
		{
			AddPointLeft    (  rcdr.dgs.x_0,  rcdr.dgs.y_0 );
			AddPointRight  ( rcdr.dgs.x_1,   rcdr.dgs.y_1 );
			Calculate();
		}
	}
//	uartTx1.Send(hdr, hdrLen);
//	sprintf (buf, "-rS-x0=%.2f,  x1=%.2f, y0=%.2f, y1=%2f, sc=%.5f, sh=%.2f%c%c",   rcdr.dgs.x_0, rcdr.dgs.x_1, rcdr.dgs.y_0,  rcdr.dgs.y_1, scale, shiftX, 13, 10);
//	uartTx1.Send(rcdr.dgs.name, hdrLen);
//	uartTx1.Send(buf);
	return ret;		
}
	
double LineConvertor_D::GetValue(double dataIn )
{
	double  v1, v2;
	v1 = (dataIn > maxX) ? maxX : dataIn;
	v2  = (dataIn < minX)?  minX : v1;
//	char buf[64];
//	sprintf(buf, "in = %.2f, v1
	return  ( v2  -  shiftX ) * scale ;//+ shiftY;
}


//#include <stdio.h>
double LineConvertor_D::GetRevers (double val)
{
	double v1, v2;
	v1 = (val  > maxY)? maxY : val;
	v2 = (val < minY)?    minY : v1;
	double ret = v2 / scale + shiftX;
//	char buf [128];
//	sprintf (buf, "v1= %.3f, v2= %.3f, val = %.3f, scale = %.3f, shiftX = %.3f ret = %.3f%c%c", 
//	v1, v2, val,  scale,  shiftX, ret,  13, 10);
//	GetUARTtx1()->Send(buf);
	return ret;
	
//	return val / scale + shiftX;c
//	double tmp = ( val - shiftY ) / scale + shiftX;
//	double ret =  ( tmp  >  maxX ) ? maxX : tmp;
//	ret = ( tmp < minX ) ?  minX : tmp;
//	return ret;
}

void LineConvertor_D::AddPointLeft (double x, double y)
{
	clbX[0] = x;
	clbY[0] = y;
}
	
void LineConvertor_D::AddPointRight (double x, double y)
{
	clbX[1] = x;
	clbY[1] = y;
}

bool LineConvertor_D::Calculate () 
{
	double dx = clbX [1] - clbX [0];
	bool ret;
	if( dx > 10.0)
	{
		scale = (clbY[1] - clbY[0]) / dx;
		shiftX = clbX[1] -  clbY[1] / scale; //X axis cross
		ret = true;
	}
	else
		ret = false;
	return ret;
}


void LineConvertor_D::Calibrate () 
{
	 if (Calculate() != false)
		Save();
}



