#include <bits/stdc++.h>
#include "logging.h"
#include "configuration.h"
#include "exceptions.h"
#include "consts.h"

Configuration :: Configuration(const int& dif, const int& num)
{
    modify(dif,num);
}

Configuration :: ~Configuration()
{

}

void Configuration :: save(const std::string& fileName)
{
    std::ofstream output;
    output.open(fileName,std::ios_base::trunc);
    output << difficulty << std::endl << dailyNumber << std::endl;
}

void Configuration :: load(const std::string& fileName)
{
    std::ifstream input;
    input.open(fileName);
    if(!input)throw NoSuchFileException(fileName);
    int dif,num;
    input >> dif >> num;
    modify(dif,num);
}

void Configuration :: modify(const int& dif, const int& num)
{
    if(dif>5 || dif<1) throw OutOfRangeException((std::string)"difficulty out of range.");
    if(__legalDailyNumbers.find(num) == __legalDailyNumbers.end()) 
        throw OutOfRangeException((std::string)"dailyNumber out of range.");
    difficulty = dif;
    dailyNumber = num;
}
