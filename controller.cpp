#include <bits/stdc++.h>
#include "controller.h"
#include "consts.h"
#include "logging.h"

Controller :: Controller (const std::string defaultUserFile)
{
    Logging log("Controller :: Controller",true);
    ifstream input(defaultUserFile);
    if(input.is_open())
    {
        std::string ID,passwd;
        input >> ID >> passwd;
        if(Login(ID,passwd))
            log << "INFO from file " << defaultUserFile << " find user " << ID << "." << std::endl;
    }
}

Controller :: ~Controller ()
{
    if(userController) delete userController;
    if(wordController) delete wordController;
}

bool Controller :: Login (std::string ID, std::string passwd)
{
    Logging log("Controller :: Login",true);
    UserData* toLogin = userController.checkIn(ID,passwd);
    if(!toLogin) return false;
    DataBase* words = new DataBase("userdatas/"+ID+".words");
    wordController = new WordController(words);
    config = new Configuration("userdatas/"+ID+".config");
    return true;
}

bool Controller :: Logout()
{
    if(!userController->getActiveUser())return false;
    delete config;
    if(wordController)delete wordController;
    userController->userLogout();
    return true;
}

UserData* Controller :: userRegister(std::string ID, std::string passwd)
{
    return userController->userRegister(ID,passwd);
}

UserData* Controller :: getActiveUser()
{
    return userController->getActiveUser();
}

WordData* Controller :: findWord(std::string word)
{
    auto gotWords = wordController->findWord(word);
    if(gotWords.size()!=0)return gotWords[0];
    else return NULL;
}

std::vector<WordData*> getRecitingWords()
{
    if(nowRecitingWords.size()==0)
    {
        auto gotWords = wordController->randomWordCollect(config->NumberPerDay());
        for(i : gotWords)
            nowRecitingWords.push_back( std::make_pair( *i, 0 ) );
    }
    return nowRecitingWords;
}





