#ifndef  ABSTRACT_ROUTER_H
#define ABSTRACT_ROUTER_H

class AbstractRouter
{
public:	
	virtual AbstractRouter* Router() = 0;
	virtual ~AbstractRouter(){}
};	


#endif

