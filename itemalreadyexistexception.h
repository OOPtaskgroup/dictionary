#ifndef ITEMALREADYEXISTEXCEPTION_H
#define ITEMALREADYEXISTEXCEPTION_H

#include "exception.h"

class ItemAlreadyExistException:public Exception
{
public:
    using Exception::Exception;
};

#endif
