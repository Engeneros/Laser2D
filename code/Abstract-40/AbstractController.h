#ifndef ABSTRACT_CONTROLLER
#define ABSTRACT_CONTROLLER
//E:\d2\www\2013Proj\soft\Abstract\AbstractController.h

class AbstractController
{
public:
	virtual void Set(double val) = 0;
	virtual  double Get () = 0;
	virtual bool Router() = 0;
	virtual ~AbstractController() {}
};
#endif
