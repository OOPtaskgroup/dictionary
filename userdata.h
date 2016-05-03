#ifndef USERDATA_H
#define USERDATA_H

#include "data.h"

class UserData : public Data
{
public:
    UserData(const std::string& name);
    ~UserData();
};

#endif
