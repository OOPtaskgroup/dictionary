#ifndef USERDATA_H
#define USERDATA_H

#include "data.h"

class UserData : public Data
{
    std::string passwd;
public:
    UserData(const std::string& name, const std::string& password);
    ~UserData();
    const std::string& Password();
    void setPassword(const std::string& newPassword);
};

#endif
