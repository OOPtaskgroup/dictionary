#ifndef WORDCONTROLLER_H
#define WORDCONTROLLER_H

#include <bits/stdc++.h>
#include "logging.h"
#include "worddatabase.h"
#include "worddata.h"
#include "datacontroller.h"
#include "consts.h"

class WordController : public DataController
{
    WordDataBase* dataBase;
    std::string contentFile;
public:
    WordController(std::string ContentFile);
    ~WordController();

    std::vector<WordData*> randomWordCollect(int num);
    void answerAccepted(WordData* item);
    void answerWrong(WordData* item);
    void setLearn(WordData* item);
    bool isLearning(WordData* item);
    bool isMastered(WordData* item);
    WordData* findWord(std::string prefix);

    std::vector<WordData*> getMasteredWord();
    std::vector<WordData*> getLearningWord();
    int getMasteredWordCount();
    int getLearningWordCount();
    void modifyLearningDifficulty(const int dif);
    std::vector<std::string> getDetail(WordData* item);
private:
    std::vector<WordData*> getWord(int type);
    std::vector<WordData*> getWord(int typel,int typer);
};
#endif
