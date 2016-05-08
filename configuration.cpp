#include "configuration.h"

Configuration :: Configuration(const std::string& fileName)
{
    contentFile = fileName;
    std::ifstream input(fileName);
    if(input)
    {
        int dif,num;
        input >> dif >> num;
        modify(dif,num);
    }
    else
    {
        input.close();
        modify(1,50);
        save();
    }
}

Configuration :: ~Configuration()
{

}

void Configuration :: save()
{
    std::ofstream output;
    output.open(contentFile,std::ios_base::trunc);
    output << difficulty << std::endl << dailyNumber << std::endl;
}

void Configuration :: modify(const int& dif, const int& num)
{
    if(dif>5 || dif<1) throw OutOfRangeException((std::string)"difficulty out of range.");
    if(__legalDailyNumbers.find(num) == __legalDailyNumbers.end()) 
        throw OutOfRangeException((std::string)"dailyNumber out of range.");
    difficulty = dif;
    dailyNumber = num;
    save();
}

const int Configuration :: DailyNumber()const
{
    return dailyNumber;
}

const int Configuration :: Difficulty()const
{
    return difficulty;
}
