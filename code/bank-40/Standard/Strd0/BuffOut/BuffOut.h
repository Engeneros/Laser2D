#ifndef 	BUFF_OUT
#define BUFF_OUT

#include <AbstractBuffOut.h>
#include <AbstractIO.h>

class BuffOut : public AbstractBuffOut
{	
public:
	BuffOut(AbstractIOasy* ifc, unsigned int size, unsigned long isrAddr = 0);
	virtual bool Send(const char* inp, unsigned int size = 0);
	virtual bool Router ();
	virtual ~BuffOut() {};
protected:
	AbstractIOasy* oIfc;
	unsigned int wrPos, rdPos;
	unsigned int hwTxBfrSz, hwRxBfrSz;
	unsigned long adrInt;
};
#endif
