#ifndef ABSTRACT_CONTROLLER_E
#define ABSTRACT_CONTROLLER_E
//E:\d2\www\2013Proj\soft\draft\0040binaryRack=17.10.2016\sw\puC\puC40_0\code\Abstract-40\AbstractController-E.h

class AbstractCtl
{
public:
	virtual bool	Router() = 0;
	virtual  ~AbstractCtl()  {}
};

class AbstractController_E : public AbstractCtl
{
public:
	virtual void SetLeftRef  (double refVal) = 0;
	virtual void SetRightRef (double refVal) = 0;
	virtual void Calibrate() = 0;
	virtual void Set(double val) = 0;
	virtual  double Get () = 0;
	virtual unsigned int GetDac() = 0;
	virtual double GetAdc() = 0;
	virtual void SetDAC( unsigned int val) = 0;
	virtual bool Router() = 0;
	virtual ~AbstractController_E() {}
};


//class AbstractDiscrController
//{
//	virtual int Get() = 0;
//	virtual void Set(int state) = 0;
//	virtual int  Get  ( char* str,  unsigned char* len) = 0;
//	virtual  int Set ( const char* str,  unsigned char len) = 0;
//	
//	virtual ~AbstractDiscrController();
//};






#endif
