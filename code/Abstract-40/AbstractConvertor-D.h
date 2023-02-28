#ifndef ABSTRACT_CONVERTOR_D_H
#define ABSTRACT_CONVERTOR_D_H

class AbstractConvertor_D
{
protected:
	double minY, maxY;
	double minX, maxX;
public:	
	~AbstractConvertor_D () { }
	virtual double  GetValue( double dataIn ) = 0;
	virtual double  GetRevers (double val) = 0;
	virtual void AddPointLeft (double x, double y) = 0;
	virtual void AddPointRight (double x, double y) = 0;
	virtual void Calibrate () = 0;
//	virtual void DeleteCalibrations() = 0;
//	virtual void DeleteRightXPoint() = 0;
//	virtual void DeleteLeftXPoint() = 0;
};

#endif


