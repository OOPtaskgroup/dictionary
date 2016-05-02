#ifndef DATA_H
#define DATA_H

#include <bits/stdc++.h>
#include "logging.h"

class Data
{
    std::string name;
    int type;
    std::string contentFile;
public:
    const std::string& Name()const;
    const int& Type()const;
    void setName(const std::string& toName);
    void setType(const int& toType);

    Data(const std::string& name);
    virtual ~Data()=0;
};

#endif
