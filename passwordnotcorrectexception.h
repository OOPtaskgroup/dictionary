#ifndef PASSWORDNOTCORRECTEXCEPTION_H
#define PASSWORDNOTCORRECTEXCEPTION_H

#include "exception.h"

class PassWordNotCorrectException:public Exception
{
public:
    using Exception::Exception;
};

#endif
