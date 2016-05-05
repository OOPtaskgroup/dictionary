#include<bits/stdc++.h>
#include"logging.h"
#include"controller.h"
int main()
{
    Controller* controller = new Controller;
    controller->Login((std::string)"keavil",(std::string)"123456");
    controller->Logout();
    controller->Login((std::string)"zhang",(std::string)"123456");
    controller->Login((std::string)"keavil",(std::string)"234567");
}
