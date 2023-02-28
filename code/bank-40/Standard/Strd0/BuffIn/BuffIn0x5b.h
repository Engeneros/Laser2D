#ifndef 	BUFF_IN
#define BUFF_IN

#include <AbstractBuffIn.h>
#include <AbstractIO.h>

const char PRINTABLE = 0x20;

class TerminatorList
{
private:
	unsigned int pos;
	TerminatorList* prev;
	TerminatorList* nxt; 
public:
	TerminatorList( unsigned int tPosition, TerminatorList* previous = 0, TerminatorList* next = 0) {pos = tPosition; prev = previous; nxt = next;}
	unsigned int GetPos() {return pos;}
	TerminatorList* GetPrev() {return prev;}
	TerminatorList * GetNext () {return nxt;}
	void SetPrev(TerminatorList* p){prev = p;}
	void SetNext(TerminatorList* n) {nxt = n;}
	~TerminatorList() 
	{
		if(prev != 0)
			prev->SetNext(nxt);
		if(nxt != 0)
			nxt->SetPrev(prev);
	}
};

class BuffInTxt : public AbstractBuffIn
{
public:
	BuffInTxt (AbstractIOasy* ifc, unsigned int size, char endSymb, unsigned long addr= 0);
	virtual unsigned int Get(char* data);
	virtual void Router();
	virtual unsigned int EchoRouter (char* inp) ;
	virtual ~BuffInTxt() {};
protected:
	void CreateNewTList();
	AbstractIOasy* iIfc;
	unsigned int wrPos, rdPos, prevWrPos ;	
	char terminator;
	TerminatorList* fifoWr;
	TerminatorList* fifoRd;
};
#endif
