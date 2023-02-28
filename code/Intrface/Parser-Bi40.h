#ifndef  PARSER_H
#define PARSER_H
#include <AbstractParser-Bi40.h>
//#include <AbstractPinOut.h>
//#include <AbstractBuffOut.h>
#include <InterfaceParticularity.h>
#include <AbstractController-E.h>
#include <AbstractBuffOut.h>
//	GET,
//	SET,
//	SET_DAC,
//	GET_DAC,
//	SET_LEFT,
//	SET_RIGHT,
//	CALIBRATE,
//	HELLO,
//	CMD_NUM

class Parser : public AbstractParser
{
public:
	Parser(Abrvr** cmdSet, Abrvr** modSet, unsigned int nCmd, unsigned int nMods ) 
	: cmds (cmdSet), moduls (modSet), cmdNum(nCmd), modNum(nMods) { }
	virtual bool Translate ( char* strIn, unsigned int inputLen, Instruction* fAndAddr,  unsigned int* dataPos );
	virtual ~Parser ( ) {}
private:
	Abrvr ** cmds;
	Abrvr**  moduls;
	unsigned int cmdNum;
	unsigned  int  modNum;

};

class ProtoModul : public AbstractModul
{
public:
	ProtoModul(AbstractBuffOut* buffOut) : outIfc (buffOut) {}
protected:
	AbstractBuffOut* outIfc;
	void SendOOps (char* str, unsigned char lenght);
};	

class Modul : public ProtoModul
{
public:
	Modul (AbstractController_E* controler,  AbstractBuffOut* buffOut);
	virtual bool Router (char* strIn, unsigned int inputLen, unsigned int fNum);// );//,  Instruction* fAndAddr, char*strOut, unsigned int outputLen) = 0;	
	virtual ~Modul() {}
protected:
	static signed  char Hget(char* str, unsigned char lenght, AbstractController_E* cntrl);
	static signed  char Hset(char* str, unsigned char lenght, AbstractController_E* cntrl);
	static signed  char HDACget(char* str, unsigned char lenght,  AbstractController_E* cntrl);
	static signed  char HADCget(char* str, unsigned char lenght,  AbstractController_E* cntrl);
	static signed  char HDACset(char* str, unsigned char lenght, AbstractController_E* cntrl);
	static signed  char Hleft(char* str, unsigned char lenght,  AbstractController_E* cntrl);
	static signed  char Hright(char* str, unsigned char lenght, AbstractController_E* cntrl);
	static signed  char Hcalibr(char* str, unsigned char lenght, AbstractController_E* cntrl);
	static signed  char Hhello(char* str, unsigned char lenght, AbstractController_E* cntrl);
	signed char (*handler[CMD_NUM]) (char* str, unsigned char lenght, AbstractController_E* cntrl); 

	AbstractController_E* ctl;
};

#include <AbstractPinOut.h>

class DiscreteModul : public ProtoModul
{
public:
	DiscreteModul ( AbstractPinOut * control,  AbstractBuffOut * buffOut );
	virtual bool Router (char* strIn, unsigned int inputLen, unsigned int fNum);// );//,  Instruction* fAndAddr, char*strOut, unsigned int outputLen) = 0;	
	virtual  ~DiscreteModul() {}
protected:
	static signed  char Hget         ( char* str,  unsigned char lenght,  AbstractPinOut* cntrl);
	static signed  char Hset         ( char* str,  unsigned char lenght,  AbstractPinOut* cntrl);
	static signed  char HDACget  (char* str, unsigned char lenght,  AbstractPinOut* cntrl){return 0;}
	static signed  char HADCget  (char* str, unsigned char lenght,  AbstractPinOut* cntrl) {return 0;}
	static signed  char HDACset  (char* str, unsigned char lenght, AbstractPinOut* cntrl){return 0;}
	static signed  char Hleft(char* str, unsigned char lenght,  AbstractPinOut* cntrl) {return 0;}
	static signed  char Hright(char* str, unsigned char lenght, AbstractPinOut* cntrl ) {return 0;}
	static signed  char Hcalibr(char* str, unsigned char lenght, AbstractPinOut* cntrl ) {return 0;}
	static signed  char Hhello  ( char* str,  unsigned char lenght,  AbstractPinOut* cntrl );
	signed char (*handler[CMD_NUM]) ( char* str, unsigned char lenght, AbstractPinOut* cntrl ); 
//	{ Hget, Hset, HDACget, HDACset, Hleft, Hright, Hcalibr, Hhello };
	AbstractPinOut* ctl;
private:
	static signed char On(AbstractPinOut* mng);
	static signed  char  Off(AbstractPinOut* mng);
	static signed char Err(AbstractPinOut* mng);
};


#endif




