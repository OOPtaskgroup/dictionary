#include<bits/stdc++.h>
#include"controller.h"
int main()
{
    Logging log("main",true);
    Controller* controller = new Controller;
    controller->Login("keavil","123456");
    controller->Logout();
    controller->Login("victorywys","233333");
    WordData* x=controller->findWord("exist");
    std::cout<<x->Name()<<" "<<x->Type()<< " " << x->ContentFile() <<std::endl;
    x = controller -> findWord("include");
    std::cout<<x->Name()<<" "<<x->Type()<< " " << x->ContentFile() << std::endl;
    controller->Logout();
}
