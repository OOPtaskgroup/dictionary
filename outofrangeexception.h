#ifndef OUTOFRANGEEXCEPTION_H
#define OUTOFRANGEEXCEPTION_H

#include "exception.h"

class OutOfRangeException:public Exception
{
public:
    using Exception::Exception;
};

#endif
