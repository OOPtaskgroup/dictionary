#include "logging.h"
int Logging::tabCounts = -1;

std::ofstream Logging::output("debug.log");

Logging::Logging (std::string name , bool needPrint)
{
    tabCounts++;
//    if(output)std::cout<<"open"<<std::endl;;
    partName = name;
    doPrint = needPrint;
    *this << "Part \"" << partName << "\" begin." << std::endl;
}

Logging::~Logging ()
{
    *this << "Part \"" << partName << "\" end." << std::endl;

    tabCounts--;
}

std::string Logging::newLine()
{
    std::string ret = "";
    for(int i=1;i<=tabCounts;i++)
        ret+="  ";
    return ret;
}

template < typename T >
std::ofstream& Logging::operator << ( T x )
{
    if(doPrint)
    {
        output<<newLine();
        output<<x;
    }
    return output;
}
