#include "worddata.h"

WordData :: WordData(const std::string name,const int type)
    :Data(name,type),times(0)
{
    setContentFile("worddata/"+name+".info");
}

WordData :: WordData(const std::string name,const int type,const int nowTimes)
    :WordData(name,type)
{
    times = nowTimes;
}

WordData :: ~WordData()
{

}
/*
std::vector<std::string> WordData :: getDetail()
{
    Logging log("WordData :: getDetail",true);
    log << "INFO getting word " << Name() << " detail" << std::endl;
     std::ifstream input(ContentFile());
    std::vector<std::string> toReturn;
    std::string tmp;
    while(std::getline(input,tmp))
        toReturn.push_back(tmp);
    log << "INFO get " << toReturn.size() << " lines of Detail." << std::endl;
    while(toReturn.size()<4)
    {
        toReturn.insert(toReturn.begin(),"\n");
    }
    if(toReturn.size()>4)
    {
        std::random_shuffle(toReturn.begin(),toReturn.begin()+toReturn.size()-2);
        std::vector<std::string> Return(toReturn.rbegin(),toReturn.rbegin()+4);
        std::reverse(Return.begin(),Return.end());
    }
    return toReturn;
}
*/
void WordData :: setTimes(const int x)
{
    times = x;
}

const int& WordData :: Times()
{
    return times;
}
