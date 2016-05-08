#ifndef WORDDATA_H
#define WORDDATA_H

#include <bits/stdc++.h>
#include "data.h"
#include "logging.h"

class WordData : public Data
{
    int times;
public:
    WordData(const std::string name,const int type);
    ~WordData();
    std::vector<std::string> getDetail();
    void setTimes(const int x);
    const int& Times();
};

#endif
