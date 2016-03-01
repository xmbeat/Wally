#ifndef SECURITY_EXCEPTION_H
#define SECURITY_EXCEPTION_H
#include "Exception.h"

class SecurityException: public Exception
{
public:
	SecurityException(String msg):Exception(msg){}
};

#endif
