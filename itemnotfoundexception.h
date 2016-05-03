#ifndef ITEMNOTFOUNDEXCEPTION_H
#define ITEMNOTFOUNDEXCEPTION_H

#include "exception.h"

class ItemNotFoundException:public Exception
{
public:
    using Exception::Exception;
};

#endif
