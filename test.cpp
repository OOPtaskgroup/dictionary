#include<bits/stdc++.h>
#include"logging.h"
#include"controller.h"
int main()
{
    Controller* controller = new Controller;
    controller->userRegister("keavil","123456");
    controller->Login("keavil","123456");
    controller->Logout();
    controller->userRegister("victorywys","233333");
    controller->Login("victorywys","233333");
    controller->Logout();
}
