#ifndef LOGGING_H
#define LOGGING_H

#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include "consts.h"

class Logging
{
    static int tabCounts;
    static std::ofstream output;
    bool doPrint;
    std::string partName;

    static std::string newLine();

public:
    Logging(std::string name , bool needPrint = true);
    ~Logging();

    template < typename T >
    std::ofstream& operator << ( T x );
};

#endif
