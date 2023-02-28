#ifndef CONVERTOR_D_H
#define CONVERTOR_D_H
#include <AbstractConvertor-D.h>
#include <AbstractMemoryIn.h>
#include <AbstractMemoryOut.h>

struct record
{
	double x_0;
	double x_1;
	double y_0;
	double y_1;
	double checkSumm;
	char name [8];
};

union stRec
{
	record dgs;
	char str[48];
};	

//	virtual double  GetValue( double dataIn ) = 0;
//	virtual double GetDigitInput (double val) = 0;
//	virtual void AddPoint (double x, double y) = 0;
//	virtual void DeleteCalibrations() = 0;
//	virtual void DeleteRightXPoint() = 0;
//	virtual void DeleteLeftXPoint() = 0;

class LineConvertor_D : public AbstractConvertor_D
{
public:	
	LineConvertor_D ( AbstractMemoryIn* memoryIn, AbstractMemoryOut* memoryOut,
	unsigned int memAddr, const char* headerStr,
	double mini_X, double maxi_X, double mini_Y, double maxi_Y,
	double x0, double x1, double y0, double y1);
	virtual double GetValue( double dataIn );
	virtual double  GetRevers (double val);
	virtual void AddPointLeft (double x, double y);
	virtual void AddPointRight (double x, double y);
	virtual void Calibrate ();
//	virtual void DeleteCalibrations() = 0;
//	virtual void DeleteRightXPoint() = 0;
//	virtual void DeleteLeftXPoint() = 0;
protected:
	bool Calculate();
	void SetMinMaxs ( double minimumX, double maximumX, double minimumY, double maximumY )
	{minX = minimumX, maxX = maximumX, minY = minimumY, maxY =  maximumY;}
	void Save();
	void WrHdr();
	bool Restore();
private:
	char hdr[8];
	unsigned char hdrLen;
	unsigned int addr;
	double clbY [2];
	double clbX [2];
	double scale;
	double shiftX, shiftY;
	AbstractMemoryIn*  fromMem;
	AbstractMemoryOut*  toMem;
	bool IsCheckSummOk(const record*  rec);
//	double max, min;
};

#endif

