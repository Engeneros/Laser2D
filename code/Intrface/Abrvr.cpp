#include <Abrvr.h>
#include <string.h>
//xxx
#include <boardDevices.h>
#include <stdio.h>

Abrvr::Abrvr (const char* str, unsigned int num) : txt(str), abN (num), len (strlen(txt))
{
	endPos = len - 1;
}
bool Abrvr::operator == (const char* str)
{
	bool ret = true;
	for (signed  char pos = endPos; ret != false   &&  pos >= 0; --pos)
		ret = str[pos] == txt[pos];
	return ret;
}

bool Abrvr::IsEqual( const char*str)
{
	bool ret = true;
//	char buf[64];
	for (signed  char pos = endPos; ret != false   &&  pos >= 0; --pos)
	{
		ret = str[pos] == txt[pos];
//		sprintf (buf, "in=%c, ref=%c %s%c%c", str[pos], txt[pos], (ret == false)? "false" : "true",  13, 10);
//		uartTx1.Send(buf);
	}
	return ret;
}


bool Abrvr::operator != (const char* str)
{
	bool ret  = true;
	for (signed  char pos = endPos; ret != false   &&  pos >= 0; --pos)
		ret = str[pos] == txt[pos];
	return !ret;
}

unsigned  char Abrvr::Compare (const char* str, unsigned  char strL)
{
//	char buf[64];
//	sprintf (buf, "strL=%d, len= %d, %c%c", strL, len, 13, 10);
//		uartTx1.Send(buf);
	return (strL >= len && IsEqual (str) )?  len : 0;
}
