#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <bits/stdc++.h>
#include "logging.h"
class Exception
{
    std::string information;
public:
    Exception(const std::string& inform);
    ~Exception();
    std::string getInformation()const;
};
#endif
