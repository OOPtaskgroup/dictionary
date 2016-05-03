#ifndef WORDCONTROLLER_H
#define WORDCONTROLLER_H

#include <bits/stdc++.h>
#include "logging.h"
#include "database.h"
#include "data.h"

class WordController : public DataController
{

public:
    WordController(const DataBase* base);
    ~WordController();

    std::vector<WordData*>& randomWordCollect(int num);
    void answerAccepted(WordData* item);
    void answerWrong(WordData* item);
    void reLearn(WordData* item);
    std::vector<WordData*>& findWord(std::string prefix);

    std::vector<WordData*>& getMasteredWord();
    std::vector<WordData*>& getLearningWord();
    int getMasteredWordCount();
    int getLearningWordCount();
private:
    std::vector<WordData*>& getWord(int type);
}
#endif
