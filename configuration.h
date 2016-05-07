#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <bits/stdc++.h>
#include "logging.h"
#include "exceptions.h"
#include "consts.h"
class Configuration
{
    int difficulty;
    int dailyNumber;
    std::string contentFile;
public:
    Configuration(const std::string& fileName);
    ~Configuration();
    void save();
    void modify(const int& dif, const int&num);
    const int DailyNumber()const;
    const int Difficulty()const;
};

#endif
