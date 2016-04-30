#include <bits/stdc++.h>
#include "logging.h"
#include "database.h"
#include "data.h"
#include "wordcontroller.h"
#include "consts.h"

WordController :: WordController(const DataBase* base)
    :DataController(base)
{
    Logging log("WordController :: WordController",false);
}

WordController :: ~WordController()
{
    Logging log("WordController :: ~WordController",false);

}
std::vector<WordData*> WordController :: wordCollect(int num)
{
    Logging log("WordController :: wordCollect",true);
    int noLearned = (int)(num * __newPart);
    int Learned = num -noLearned;

    vector<WordData*> toReturn;

    dataBase.select(0);
    for(int i = 1 ; i <= noLearned ; i++)
    {
        if(dataBase.empty())
        {
            log << "INFO database empty for new words." << std::endl;
            break;
        }
        WordData* now = dataBase.getRandom();
        toReturn.pushback( now );
        log << "INFO added word " << now->Name() << "." <<std::endl;
    }

    dataBase.select(1);
    for(int i = 1 ; i <= Learned ; i++)
    {
        if(dataBase.empty())
        {
            log << "INFO database empty for learned words." << std::endl;
        }
        WordData* now = dataBase.getRandom();
        toReturn.pushback( now );
        log << "INFO added word " << now->Name() <<" , have answered correctly " 
            << now->Times() << " times continiously." << std::endl;
    }

    return toReturn;
}

void WordController :: answerAccepted (WordData* item)
{
    Logging log("WordController :: answerAccepted",true);
    item->setTimes( item->Times() + 1 );
    log << "INFO word " << item->Name() << "answered correctly, for "
        << item->Times() << " times now.";
    if( item->Times() >= __timesContiniouslyLimit)
    {
        item->setType(2);
        log << " now it will never appear ( unless reset ).";
    }
    log << std::endl;
}

void WordController :: answerWrong (WordData* item)
{
    Logging log("WordController :: answerWrong",true);
    item->setTimes( 0 );
    log << "INFO word " << item->Name() << "answered wrong." << std::endl;
}

void WordController :: reLearn (WordData* item)
{
    Logging log("WordController :: reLearn",true);
    item ->setTimes(0);
    item ->setType(1);
    log << "INFO now word " << item->Name() << " will appear again." << std::endl;
}

std::vector<WordData*> WordController :: getWord(int type)
{
    dataBase.select(type);

}
