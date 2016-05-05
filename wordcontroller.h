#ifndef WORDCONTROLLER_H
#define WORDCONTROLLER_H

#include <bits/stdc++.h>
#include "logging.h"
#include "worddatabase.h"
#include "worddata.h"
#include "datacontroller.h"

class WordController : public DataController
{
    WordDataBase* dataBase;
public:
    WordController();
    ~WordController();

    std::vector<WordData*> randomWordCollect(int num,int difficulty);
    void answerAccepted(WordData* item);
    void answerWrong(WordData* item);
    void reLearn(WordData* item);
    std::vector<WordData*> findWord(std::string prefix);

    std::vector<WordData*> getMasteredWord(const int difficulty);
    std::vector<WordData*> getLearningWord(const int difficulty);
    int getMasteredWordCount(const int difficulty);
    int getLearningWordCount(const int difficulty);
private:
    std::vector<WordData*> getWord(int type);
};
#endif
