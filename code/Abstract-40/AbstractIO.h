//E:\d2\www\2013Proj\soft\Abstract\AbstractIO.h
#ifndef ABSTRACT_IO_H
#define ABSTRACT_IO_H

class AbstractIO
{
public: 
	virtual void Tx ( unsigned long data ) = 0;
	virtual void FastTx(unsigned long data) {}
	virtual unsigned long Rx () = 0;
	virtual unsigned long FastRx () {return 0;}
	virtual unsigned long TxRx (unsigned long data) = 0;
//	virtual  void Wait() {}
	virtual  ~AbstractIO () { }
};

class AbstractIOasy
{
public:
	virtual void Tx ( unsigned long data ) = 0;
	virtual void Tx ( const unsigned char* data, unsigned int sz ) = 0;
	virtual unsigned long Rx () = 0;
	virtual bool IsRxReady () = 0;
	virtual bool IsTxReady () = 0;
	virtual unsigned int GetRxHwBuffSz() {return 16;}
	virtual unsigned int GetTxHwBuffSz() {return 16;}
	virtual void SetTxISRAddr ( unsigned long addr ) = 0;
	virtual void SetRxISRAddr ( unsigned long addr ) = 0;
	virtual void DisableInt() = 0;
	virtual void EnableInt() = 0;
	virtual  ~AbstractIOasy(){}
};

#endif





