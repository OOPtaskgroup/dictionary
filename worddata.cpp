#include <bits/stdc++.h>
#include "worddata.h"
#include "bits/stdc++.h"

WordData :: WordData(const std::string name)
    :Data(name)
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
