#ifndef PASSWORDNOTCORRECTEXCEPTION_H
#define PASSWORDNOTCORRECTEXCEPTION_H

#include "exception.h"

class PasswordNotCorrectException:public Exception
{
public:
    using Exception::Exception;
};

#endif
