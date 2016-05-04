#ifndef WORDDATA_H
#define WORDDATA_H

#include "data.h"

class WordData : public Data
{
public:
    WordData(const std::string name);
    ~WordData();
    std::vector<std::string> getDetail();
};

#endif
