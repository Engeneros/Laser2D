//E:\d2\www\2013Proj\soft\Abstract\AbstractWordIn.h
#ifndef ABSTRACT_WORD_IN_H
#define ABSTRACT_WORD_IN_H

class AbstractRO
{
protected:
	int val;
public:	
	virtual int Read() {return val;}
	virtual ~AbstractRO(){}
};



class AbstractWordIn
{
public:
	virtual  unsigned long  Read() = 0 ;
	virtual  ~AbstractWordIn(){}
};

//class AbstractWordIn_Ifc : public AbstractWordIn
//{
//public:
//	virtual unsigned int Router() = 0;
//	virtual ~AbstractWordIn_Ifc() {};
//};
		
//class AbstractEncoder
//{
//public: 
//	virtual int GetValue() = 0;
//	virtual ~AbstractEncoder(){};
//};

//class EncoderWIn : public AbstractEncoder
//{
//protected:
//	int val;
//public:
//	EncoderWIn(int iniVal = 0) { val = iniVal; }
//	virtual int GetValue() {return val;}
//	virtual void SetVal (int v) { val = v;}
//	virtual ~EncoderWIn(){}
//};





//class AbstractEncoderWInRouter : public EncoderWIn
//{
//protected:
//	int outCfgNum; 
//public:
//	AbstractEncoderWInRouter( int num) { outCfgNum = num; }
//	virtual AbstractEncoderWInRouter* Router() = 0;
//	virtual unsigned int GetOutConfig() { return outCfgNum;}
//	virtual ~AbstractEncoderWInRouter(){}
//};
#endif





