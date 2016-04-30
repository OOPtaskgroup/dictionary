#include<bits/stdc++.h>
#include"logging.h"
void work()
{
    Logging log("work");
//    log<<"ah"<<5<<std::endl;
    log << "INFO value = 50" <<std::endl;
}
int main()
{
    Logging log("main");
    //log<<67;
    log << "INFO prepare to work." <<std::endl;
    work();
}
