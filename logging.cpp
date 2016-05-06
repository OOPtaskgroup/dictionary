#include "logging.h"
int Logging::tabCounts = -1;

std::ofstream Logging::output(__debugFileName == "EMPTY" ? "":__debugFileName);

Logging::Logging (std::string name , bool needPrint)
{
    tabCounts++;

    partName = name;
    doPrint = needPrint;
    *this << "Part \"" << partName << "\" begin.\n" ;
}

Logging::~Logging ()
{
    *this << "Part \"" << partName << "\" end.\n" ;

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
//template std::ofstream& Logging::operator << <int> (int x);
//template std::ofstream& Logging::operator << <std::string> (std::string x);

