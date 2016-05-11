#include<bits/stdc++.h>
#include"controller.h"
int main()
{
    Logging log("main",true);
    Controller* controller = new Controller;
//    controller->userRegister("keavil","123456");
//    controller->userRegister("victorywys","233333");
    controller->Login("keavil","123456");
    controller->Logout();
    controller->Login("victorywys","233333");
//    int dif = 3,num=50;
//    controller->modifyConfig(dif,num);
/*    auto& x = controller->getRecitingWords();
    for(auto i:x)std::cout<<i.first->Name()<<std::endl;
    for(auto& i:x)
    {
        if(rand()&1)
        controller->answerWrong(i);
        else controller->answerAccepted(i);
    }*/
    if(controller->isLearning(controller->findWord("transition")))
        std::cout<<"ok"<<std::endl;
    else std::cout<<"fail"<<std::endl;
    if(controller->isLearning(controller->findWord("across")))
        std::cout<<"fail"<<std::endl;
    else std::cout<<"ok"<<std::endl;
    if(controller->isMastered(controller->findWord("transition")))
        std::cout<<"ok"<<std::endl;
    else std::cout<<"fail"<<std::endl;
    controller->Logout();
}
