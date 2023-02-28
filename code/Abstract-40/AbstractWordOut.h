#ifndef ABSTRACT_WORD_OUT_H
#define ABSTRACT_WORD_OUT_H

#include <AbstractWordIn.h>

class AbstractRW : public AbstractRO
{
public:
	virtual void Write( int x){val = x;}
	virtual int Add ( int x) { Write (val + x); return val;}
	virtual ~AbstractRW(){}
};

class AbstractRWdiscCheking : public AbstractRW
{
protected: 
	bool isWrited;
public:
	virtual bool IsWrited()    {return isWrited;}	
	virtual void Write (int x) { val = x;  isWrited = true;}
	virtual int Read () {isWrited = false;  return val;}
};

class AbstractWordOut
{
public:
	virtual void Send(unsigned long data) = 0;
	virtual  ~AbstractWordOut(){}
};

class AbstractIntOut
{
public:
	virtual void Send(int data = 0) = 0;
	virtual  ~AbstractIntOut(){}
};

class AbstractBitWordOut
{
public:
	virtual void Send(unsigned long data) = 0;
	void Clear(unsigned long data) { Send (~data & oState);}
	void  Set(unsigned long data)   { Send (data | oState);}
	virtual  ~AbstractBitWordOut(){}
protected :
	unsigned long  oState;
};
#endif





