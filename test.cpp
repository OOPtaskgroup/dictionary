#include<bits/stdc++.h>
#include"controller.h"
int main()
{
    Logging log("main",true);
    Controller* controller = new Controller;
    controller->userRegister("keavil","123456");
    controller->userRegister("victorywys","233333");
    controller->Login("keavil","123456");
    controller->Logout();
    controller->Login("victorywys","233333");
    auto x=controller->findWord("exist");
    x = controller -> findWord("include");
    auto h = controller->getActiveUser();
    controller->Logout();
    controller->userModifyPassword(h,"233333","000000");

}
