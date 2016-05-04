#include <bits/stdc++.h>
#include "controller.h"
#include "consts.h"
#include "logging.h"
#include "worddata.h"
#include "userdata.h"

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
    if(config) delete config;
}

void Controller :: Login (std::string ID, std::string passwd)
{
    Logging log("Controller :: Login",true);
    UserData* toLogin = userController->checkIn(ID,passwd);
    userController->userLogin(toLogin);
    DataBase* words = new DataBase("userdatas/"+ID+"/words.txt");
    wordController = new WordController(words);
    config = new Configuration("userdatas/"+ID+"/config");
}

void Controller :: Logout()
{
    if(!userController->getActiveUser())throw ItemNotFoundException((std::string)"no user now.");
    if(config)delete config;
    if(wordController)delete wordController;
    userController->userLogout();
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
    auto gotWords = wordController->findWord(word,config->Difficulty());
    if(gotWords.size() != 0)return gotWords[0];
    else return NULL;
}

std::vector< std::pair<WordData*,int> >& getRecitingWords()
{
    if(nowRecitingWords.size() == 0)getTodayWords();
    if(nowRecitingWords.size() == 0)
    {
        auto gotWords = wordController->randomWordCollect(config->DailyNumber(),config->Difficulty());
        for(auto i : gotWords)
        {
            nowRecitingWords.push_back( std::make_pair( *i, 0 ) );
            i->setType(i->Type()%10 + 10);
        }
    }
    reWriteRecitingWords();
    return nowRecitingWords;
}

void Controller :: answerAccepted( std::pair<WordData*,int> &item)
{
    item->second ++;
    if(item.second == 1)
        wordController->answerAccepted(item->first);
    reWriteRecitingWords();
}

void Controller :: answerWrong( std::pair<WordData*,int> &item)
{
    item->second = -1;
    wordController->answerWrong(item->first);
    reWriteRecitingWords();
}

void Controller :: reLearn(WordData* item)
{
    wordController->reLearn(item);
}

std::vector<WordData*>& Controller :: getMasteredWord()
{
    return wordController->getMasteredWord(config->Difficulty());
}

std::vector<WordData*>& Controller :: getLearingWord()
{
    return wordController->getLearningWord(config->Difficulty());
}

int Controller :: getMasteredWordCount()
{
    return wordController->getMasteredWordCount(config->Difficulty());
}

int Controller :: getLearningWordCount()
{
    return wordController->getLearningWordCount(config->Difficulty());
}

const Configuration& Controller :: getConfig() const
{
    if(!config) throw ItemNotFoundException((std::string)"config does not exist");
    return *config;
}

void Controller :: modifyConfig(const int& dif, const int& num)
{
    if(!config) throw ItemNotFoundException((std::string)"config does not exist.");
    config->modify(dif,num);
}

void Controller :: modifyConfig(const Configuration& newConfig)
{
    modifyConfig(newConfig.Difficulty(), newConfig.DailyNumber());
}

void reWriteRecitingWords()
{
    std::string fileName("userdata/" + userController->getActiveUser()->Name() + "/today.txt");
    std::ofstream output(fileName, std::ios_base::trunc);
    std::tm* now = std::localtime(std::time(0));
    output << (1900 + now->tm_year) << " " << (1 + now->tm_mon) << " " << (now->tm_mday) << std::endl;
    for(auto i : nowRecitingWords)
        output << ((*i).first->Name()) << (*i).second << std::endl;
}

void reWriteUserConfig()
{
    std::string fileName("userdata/" + userController->getActiveUser()->Name() + "/config");
    std::ofstream output(fileName, std::ios_base::trunc);
    output << config->Difficulty() << " " << config->DailyNumber() << std::endl;
}
void getTodayWords()
{
    std::tm* now = std::localtime(std::time(0));
    std::string fileName("userdata/" + userController->getActiveUser()->Name() + "/today.txt");
    std::ifstream input(fileName);
    if(!input)return;
    int year,month,day;
    input >> year >> month >> day;
    if(year != now->tm_year+1900 || month != now->tm_mon+1 || day != now->tm_mday)return;
    std::string name;
    int type;
    while(input >> name >> type)
        nowRecitingWords.push_back( std::make_pair(findWord(name), type));
}
