#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <bits/stdc++.h>
#include <QFile>
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
    void Login(UserData* user, bool remPasswd = false);
    void Login(std::string ID, std::string passwd, bool remPasswd = false);
    void Logout();
    UserData* userRegister(std::string ID, std::string passwd);
    UserData* getActiveUser();
    void userModifyPassword(UserData* user, std::string passwd, std::string newPasswd);
    std::pair<std::string,std::string> getDefaultUser();
private:
    WordController* wordController;
    std::vector< std::pair<WordData*,int> > nowRecitingWords;
public:
    WordData* findWord(std::string word, bool toAddHistory = false);
    std::vector< std::pair<WordData*,int> >& getRecitingWords();
    void setAdditionWords(int num = 20);
    std::vector< WordData* > getTestWords(int num = 50);
    int getVocabulary(std::vector<std::pair<WordData*,bool>> list);
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
    std::vector<WordData*> getTextNewWords(std::string text);
private:
    Configuration* config;
public:
    const Configuration& getConfig()const;
    void modifyConfig(const Configuration& newConfig);
    void modifyConfig(const int& dif, const int&num);
    std::vector<std::string> getSearchHistory(UserData* user);
    void setHistoryLog(WordData* word);
    std::string getNowTheme();
    void modifyTheme(std::string nowTheme);
    QString setTheme(std::string name);

public:
    Controller ();
    ~Controller ();

private:
    void reWriteTodayWords();
    void getTodayWords();
};

#endif
