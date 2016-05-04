#ifndef WORDDATA_H
#define WORDDATA_H

#include "data.h"

class WordData : public Data
{
    int times;
public:
    WordData(const std::string name);
    ~WordData();
    std::vector<std::string> getDetail();
    void setTimes(const int x);
    const int& Times();
};

#endif
