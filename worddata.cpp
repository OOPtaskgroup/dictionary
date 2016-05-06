#include "worddata.h"

WordData :: WordData(const std::string name,const int type)
    :Data(name,type),times(0)
{
    setContentFile("worddata/"+name+".information");
}

WordData :: ~WordData()
{

}

std::vector<std::string> WordData :: getDetail()
{
    std::ifstream input(ContentFile());
    std::vector<std::string> toReturn;
    std::string tmp;
    while(std::getline(input,tmp))
        toReturn.push_back(tmp);
    if(toReturn.size()<=4)
        return toReturn;
    else
    {
        std::random_shuffle(toReturn.begin(),toReturn.begin()+toReturn.size()-2);
        std::vector<std::string> Return(toReturn.rbegin(),toReturn.rbegin()+4);
        std::reverse(Return.begin(),Return.end());
        return Return;
    }
}

void WordData :: setTimes(const int x)
{
    times = x;
}

const int& WordData :: Times()
{
    return times;
}
