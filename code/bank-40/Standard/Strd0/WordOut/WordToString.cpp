//E:\d2\www\2013Proj\soft\draft\0023FrontPanel=03.02.2015\code\WordOut\WordToString.cpp
#include <WordToString.h>
#include <stdio.h>
#include <string.h>

const char ENTER [] = {10, 13, 0}; 

PreEntIntOut::PreEntIntOut( AbstractBuffOut* dst, const char* prefix)//, const char* postfix)
{
	out = dst;
 //   tail = strOut + strlen(prefix);
	strcpy (strOut, prefix);
	prefixLen = strlen(prefix);
    //int len = strlen(postfix) + 1;
//    sufix = new char[len];
//    strcpy( sufix, postfix);
//    sufix[len - 1] = 0;
}

void PreEntIntOut::Send(int data)
{
   sprintf(tail, "%d", data);
//	strcat (tail, ENTER);
   out->Send(strOut, prefixLen);
	out->Send(tail, strlen(tail));
	out->Send(ENTER, 2);
	
}

DoubleOut::DoubleOut ( AbstractBuffOut* dst, unsigned int tolerance)
{
	dgTolerance = tolerance;
	out = dst;
}

void DoubleOut::Send(int data)
{
	char buf[16];
	//printf("%0*.*f%n\n", w, p, number, &kk);    // §Ó§í§é§Ú§ã§Ý§Ö§ß§Ú§Ö §Ü§à§Ý§Ú§é§Ö§ã§ä§Ó§Ñ
	sprintf ( buf, "%0.*f ", dgTolerance, (double) data / 1000);
	out->Send(buf);
}

DoubleOutPrefix::DoubleOutPrefix( AbstractBuffOut* dst, unsigned int tolerance, const char* prefix )
{
	dgTolerance = tolerance;
	out = dst;
	tail = strOut + strlen(prefix);
	strcpy (strOut, prefix);
}

void DoubleOutPrefix::Send( int data)
{
	sprintf(tail, "%0.*f ", dgTolerance, (double) data / 1000);
	out->Send(strOut);
};


DoubleOutPostfix::DoubleOutPostfix( AbstractBuffOut* dst, unsigned int tolerance, const char* sufix )
{
	dgTolerance = tolerance;
	out = dst;
	psScr = new char [strlen (sufix) +1];
	strcpy(psScr, sufix);
}

void DoubleOutPostfix::Send( int data)
{
	sprintf ( strOut, "%0.*f", dgTolerance, (double) data / 1000);
	strcat( strOut, psScr );
	out->Send( strOut );
}

LabelOut::LabelOut( AbstractBuffOut* dst, const char* lbl )
{
	out = dst;
	labOut = new char [ strlen ( lbl ) + 1];
	strcpy ( labOut, lbl );
}

void LabelOut::Send ( int data )
{
	out->Send(labOut);
}






