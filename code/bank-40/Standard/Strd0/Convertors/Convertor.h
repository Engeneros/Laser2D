#ifndef CONVERTOR_H
#define CONVERTOR_H
#include <AbstractConvertor.h>
#include <AbstractMemoryIn.h>
#include <AbstractMemoryOut.h>


struct record
{
	unsigned short x_0;
	unsigned short x_1;
	float y_0;
	float y_1;
	float chsum;
};
union stRec
{
	record dgs;
	char str[16];
};	

class LineConvertor : public AbstractConvertor
{
public:	
	LineConvertor(AbstractMemoryIn* memoryIn, AbstractMemoryOut* memoryOut, unsigned int memAddr, const char* headerStr,
	unsigned int mini_X, unsigned int maxi_X,
	double mini_Y, double maxi_Y, const char* units, unsigned char tolrs, double minimum, double maximum);
//	virtual void SetMinMaxs ( double minimum, double maximum);
	virtual double GetValue( unsigned int dataIn );
	virtual unsigned int GetDigitInput (double val);
	virtual void AddPoint ( unsigned int x, double y);
	virtual void Save();
	virtual bool Restore();
	virtual void Reset() ;
private:

	char hdr[8];
	unsigned char hdrLen;
	unsigned int addr;
	double clbY [2];
	double clbX [2];
//	double brdX [2];
//	double brdY [2];
	double scale;
	double shiftX, shiftY;
	AbstractMemoryIn* fromMem;
	AbstractMemoryOut* toMem;
	bool IsCheckSummOk(const record*  rec);
	double max, min;
};

#endif

