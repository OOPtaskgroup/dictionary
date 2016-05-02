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
    DataBase* words = new DataBase("userdatas/"+ID+"/words.txt");
    wordController = new WordController(words);
    config = new Configuration("userdatas/"+ID+"/config");
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
    if(gotWords.size() != 0)return gotWords[0];
    else return NULL;
}

std::vector< std::pair<WordData*,int> >& getRecitingWords()
{
    if(nowRecitingWords.size() == 0)
    {
        auto gotWords = wordController->randomWordCollect(config->NumberPerDay());
        for(auto i : gotWords)
            nowRecitingWords.push_back( std::make_pair( *i, 0 ) );
    }
    return nowRecitingWords;
}

void Controller :: answerAccepted( std::pair<WordData*,int> &item)
{
    item->second ++;
    if(item.second == 1)
        wordController->answerAccepted(item->first);
}

void Controller :: answerWrong( std::pair<WordData*,int> &item)
{
    item->second = -1;
    wordController->answerWrong(item->first);
}

void Controller :: reLearn(WordData* item)
{
    wordController->reLearn(item);
}

std::vector<WordData*>& Controller :: getMasteredWord()
{
    return wordController->getMasteredWord();
}

std::vector<WordData*>& Controller :: getLearingWord()
{
    return wordController->getLearningWord();
}

int Controller :: getMasteredWordCount()
{
    return wordController->getMasteredWordCount();
}

int Controller :: getLearningWordCount()
{
    return wordController->getLearningWordCount();
}

const Configuration& Controller :: getConfig() const
{
    if(!config) throw (std::string)("302 Error : no config while getConfig().");
    return *config;
}

void Controller :: modifyConfig(const Congiguration& newConfig)
{
    if(!config) throw (std::string)("302 Error : no config while getConfig()");
    *config = newConfig;
}


