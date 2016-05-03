#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <bits/stdc++.h>

class Exception
{
    std::string information;
public:
    Exception(const std::string& inform);
    virtual ~Exception()=0;
    std::string getInformation()const;
};
#endif
