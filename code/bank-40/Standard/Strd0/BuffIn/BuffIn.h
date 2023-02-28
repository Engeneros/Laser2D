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
	int uniq;
	TerminatorList( unsigned int tPosition, TerminatorList* previous = 0, TerminatorList* next = 0) {pos = tPosition; prev = previous; nxt = next;}
	unsigned int GetPos() {return pos;}
	TerminatorList* GetPrev() {return prev;}
	TerminatorList * GetNext () {return nxt;}
	void SetPrev(TerminatorList* p){prev = p;}
	void SetNext(TerminatorList* n) {nxt = n;}
	~TerminatorList();
};

class BuffInTxt : public AbstractBuffIn
{
public:
	BuffInTxt (AbstractIOasy* ifc, unsigned int size, char endSymb, unsigned long addr= 0);
	virtual unsigned int Get(char* data, unsigned int maxSz = 32);
	virtual void Router();
	virtual unsigned int EchoRouter (char* inp) ;
	virtual ~BuffInTxt() {};
protected:
//AbstractBuffIn(size),  terminator (endSymb) ,  nCmd (0), cnt(40), wrPos (0), rdPos(0),
//fifoRd (0), fifoWr (0), rxSuspend(false)	
	char terminator;
	unsigned int wrPos, rdPos;	
	TerminatorList* fifoRd;
	TerminatorList* fifoWr;
	bool rxSuspend;
	AbstractIOasy* iIfc;
};
class BuffInTxtDbg : public BuffInTxt
{
public:
	BuffInTxtDbg (AbstractIOasy* ifc, unsigned int size, char endSymb, unsigned long addr= 0) : 
BuffInTxt (ifc, size, endSymb, addr)//, cnt(0), intEn(true) 
{iIfc->DisableInt();} 
	virtual unsigned int Get(char* data, unsigned int maxSz = 32);
	virtual void Router();
	virtual ~BuffInTxtDbg() {};
	private:
	//	int cnt;
	//	bool intEn;
};

#endif
