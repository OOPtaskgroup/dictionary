#ifndef CONFIGURATION_H
#define CONFIGURATION_H

class Configuration
{
    int difficulty;
    int dailyNumber;
public:
    Configuration(const int& dif, const int& num);
    ~Configuration();
    void save(const std::string& fileName);
    void load(const std::string& fileName);
    void modify(const int& dif, const int&num);
};

#endif
