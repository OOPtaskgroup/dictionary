#ifndef NOSUCHFILEEXCEPTION_H
#define NOSUCHFILEEXCEPTION_H

#include "exception.h"

class NoSuchFileException:public Exception
{
public:
    using Exception::Exception;
};

#endif
