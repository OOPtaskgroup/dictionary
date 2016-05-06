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
public:
    Configuration(const int& dif, const int& num);
    Configuration(const std::string& fileName);
    ~Configuration();
    void save(const std::string& fileName);
    void load(const std::string& fileName);
    void modify(const int& dif, const int&num);
    const int DailyNumber()const;
    const int Difficulty()const;
};

#endif
