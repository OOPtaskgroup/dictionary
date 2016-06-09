#ifndef DATABASE_H
#define DATABASE_H
#include <bits/stdc++.h>
#include "data.h" 

class DataBase
{
public:
    ~DataBase();
    virtual bool empty() = 0;
    virtual int size() = 0;
    virtual void save(const std::string fileName) = 0;
};

#endif
