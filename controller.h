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
    void Login(UserData* user);
    void Logout();
    UserData* userRegister(std::string ID, std::string passwd);
    UserData* getActiveUser();
    void userModifyPassword(UserData* user, std::string passwd, std::string newPasswd);
private:
    WordController* wordController;
    std::vector< std::pair<WordData*,int> > nowRecitingWords;
public:
    WordData* findWord(std::string word);
    std::vector< std::pair<WordData*,int> >& getRecitingWords();
    std::vector< WordData* > getTestWords(int num);
    void answerAccepted( std::pair<WordData*,int> &item);
    void answerWrong( std::pair<WordData*,int> &item);
    void setLearn(WordData* item);
    std::vector<WordData*> getMasteredWord();
    std::vector<WordData*> getLearningWord();
    int getMasteredWordCount();
    int getLearningWordCount();
    std::vector<std::string> getDetail(WordData* item);
    bool isLearning(WordData* item);
    bool isMastered(WordData* item);
    void addExample(WordData* word, std::string item);
    void delExample(WordData* word, std::string item);
    std::vector<std::string> getExample(WordData* word);
private:
    Configuration* config;
public:
    const Configuration& getConfig()const;
    void modifyConfig(const Configuration& newConfig);
    void modifyConfig(const int& dif, const int&num);
    std::vector<std::string> getSearchHistory(UserData* user);

public:
    Controller (const std::string defaultUserFile="EMPTY");
    ~Controller ();

private:
    void reWriteTodayWords();
    void getTodayWords();
};

#endif
