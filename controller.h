#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <bits/stdc++.h>
#include "logging.h"
#include "wordcontroller.h"
#include "usercontroller.h"
#include "configuration.h"
#include "consts.h"
#include "exceptions.h"

class Controller
{
private:
    UserController* userController;
public:
    void Login(std::string ID, std::string passwd);
    void Logout();
    UserData* userRegister(std::string ID, std::string passwd);
    UserData* getActiveUser();
private:
    WordController* wordController;
    std::vector< std::pair<WordData*,int> > nowRecitingWords;
public:
    WordData* findWord(std::string word);
    std::vector< std::pair<WordData*,int> >& getRecitingWords();
    void answerAccepted( std::pair<WordData*,int> &item);
    void answerWrong( std::pair<WordData*,int> &item);
    void reLearn(WordData* item);
    std::vector<WordData*> getMasteredWord();
    std::vector<WordData*> getLearningWord();
    int getMasteredWordCount();
    int getLearningWordCount();

private:
    Configuration* config;
public:
    const Configuration& getConfig()const;
    void modifyConfig(const Configuration& newConfig);
    void modifyConfig(const int& dif, const int&num);


public:
    Controller (const std::string defaultUserFile="EMPTY");
    ~Controller ();

private:
    void reWriteRecitingWords();
    void reWriteUserConfig();
    void getTodayWords();
};

#endif
