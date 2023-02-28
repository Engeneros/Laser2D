#ifndef  ABSTRACT_BUFF_IN_H
#define ABSTRACT_BUFF_IN_H
//E:\d2\www\2013Proj\soft\Abstract\AbstractBuffIn.h

class AbstractBuffIn
{
protected:
	unsigned int buffSz;
	char* buff;
public:
	explicit AbstractBuffIn (unsigned int sz) {buffSz = sz; buff = new char[buffSz];}
	virtual unsigned int Get ( char* data, unsigned int maxSz = 32) = 0;
	virtual void Router () = 0;
//	virtual void Suspend() = 0;
//	virtual void Release() = 0;
	virtual unsigned int EchoRouter (char* inp) = 0;
	virtual ~AbstractBuffIn () {delete[] buff;};
};

//class AbstractRobustBufin :public AbstractBuffIn
//{
//public:
//	virtual unsigned int GetSize();
//	virtual unsigned int SkipMessage();
//}

#endif

