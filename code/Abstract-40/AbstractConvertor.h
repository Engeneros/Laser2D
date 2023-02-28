#ifndef ABSTRACT_CONVERTOR_H
#define ABSTRACT_CONVERTOR_H

class AbstractConvertor
{
protected:
	unsigned char  tlc;
	char* unt;
	double minY, maxY;
	unsigned int minX, maxX;
public:	
	AbstractConvertor(const char* units = 0) { SetUnits(units);}	
	~AbstractConvertor () {delete [] unt;}

	virtual double  GetValue( unsigned int dataIn ) = 0;
	virtual unsigned int GetDigitInput (double val) = 0;
	virtual void AddPoint (unsigned int x, double y) = 0;
	virtual void Save() = 0;
	virtual bool Restore() = 0;

	void GetValueString (unsigned int dataIn, char* buf);
	void GetValueStringAndUnits( unsigned int dataIn, char* buf);
	void SetUnits ( const char* units);

	void SetTolerance ( unsigned char tolerance) { tlc = tolerance;}

	virtual void SetMinMaxs ( unsigned int minAbc, unsigned int maxAbc, double minOrd, double maxOrd)
	{ minY = minOrd, maxY = maxOrd, minX = minAbc, maxX = maxAbc;}
	virtual void Reset() {}
};

#endif


