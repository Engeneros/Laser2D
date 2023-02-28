//E:\d2\www\2013Proj\soft\draft\0023FrontPanel=03.02.2015\code\WordOut\WordToString.h
#ifndef  WORD_TO_STRING
#define WORD_TO_STRING
#include <ABstractWordOut.h>
#include <AbstractBuffOut.h>


class PreEntIntOut : public AbstractIntOut
{
public:
  PreEntIntOut( AbstractBuffOut* dst, const char* prefix);//, const char* postfix);
  virtual void Send ( int data  = 0);
  virtual ~PreEntIntOut(){}
private:
  AbstractBuffOut* out;
   char strOut[24];
   char tail [16];
	unsigned int prefixLen;
//   char* sufix;
};
   
class DoubleOut : public AbstractIntOut
{
public:
	DoubleOut ( AbstractBuffOut* dst, unsigned int tolerance );
	virtual void Send( int data = 0 );
	virtual ~DoubleOut() { }
private:
	unsigned int dgTolerance;
	AbstractBuffOut* out;
};

class DoubleOutPrefix : public AbstractIntOut
{
public:
	DoubleOutPrefix ( AbstractBuffOut* dst, unsigned int tolerance, const char* prefix );
	virtual void Send( int data = 0 );
	virtual ~DoubleOutPrefix () { }
private:
	unsigned int dgTolerance;
	AbstractBuffOut* out;
	char strOut[16];
	char* tail;
};

class DoubleOutPostfix : public AbstractIntOut
{
public:
	DoubleOutPostfix ( AbstractBuffOut* dst, unsigned int tolerance, const char* sufix );
	virtual void Send( int data = 0);
	virtual ~DoubleOutPostfix () { delete[] psScr; }
private:
	unsigned int dgTolerance;
	AbstractBuffOut* out;
	//char psScr  [8] ;   
	char* psScr;
	char strOut[16];
};

class LabelOut : public AbstractIntOut
{
public:
	LabelOut ( AbstractBuffOut* dst, const char* lbl) ;
	virtual void Send (int data = 0) ;
	virtual ~LabelOut() {delete []labOut;}
private:
	char* labOut;
	AbstractBuffOut* out;
};
 





















#endif


