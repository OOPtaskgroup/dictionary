#include "wordcontroller.h"

WordController :: WordController(std::string ContentFile)
    :contentFile(ContentFile)
{
    std::ifstream input(contentFile);
    if(input)
    {
        input.close();
        dataBase = new WordDataBase(contentFile);
    }
    else
    {
        dataBase = new WordDataBase();
        dataBase->reWrite(contentFile);
    }
    Logging log("WordController :: WordController",false);
}

WordController :: ~WordController()
{
    Logging log("WordController :: ~WordController",false);
    dataBase->reWrite(contentFile);
    delete dataBase;

}
std::vector<WordData*> WordController :: randomWordCollect(int num, int difficulty)
{
    Logging log("WordController :: wordCollect",true);
    int noLearned = (int)(num * __newPart);
    int Learned = num -noLearned;

    std::vector<WordData*> toReturn;

    dataBase->select(difficulty);
    for(int i = 1 ; i <= noLearned ; i++)
    {
        if(dataBase->isEmpty())
        {
            log << "INFO database empty for new words." << std::endl;
            break;
        }
        WordData* now = dataBase->getrandom();
        toReturn.push_back( now );
        log << "INFO added word " << now->Name() << "." <<std::endl;
    }

    dataBase->select(difficulty+10);
    for(int i = 1 ; i <= Learned ; i++)
    {
        if(dataBase->isEmpty())
        {
            log << "INFO database empty for learned words." << std::endl;
            break;
        }
        WordData* now = dataBase->getrandom();
        toReturn.push_back( now );
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
        item->setType(20 + item->Type()%10);
        log << " now it will never appear ( unless reset ).";
    }
    log << "" << std::endl;
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
    item ->setType(10 + item->Type()%10);
    log << "INFO now word " << item->Name() << " will appear again." << std::endl;
}

std::vector<WordData*> WordController :: getWord(int type)
{
    Logging log("WordController :: getWord",true);
    dataBase->select(type);
    std::vector<WordData*> toReturn = dataBase->getAll();
    log << "INFO get " << toReturn.size() << " words." << std::endl;
    return toReturn;
}

std::vector<WordData*> WordController :: getMasteredWord(const int difficulty)
{
    return getWord(20 + difficulty);
}

std::vector<WordData*> WordController :: getLearningWord(const int difficulty)
{
    return getWord(10 + difficulty);
}

WordData* WordController :: findWord(std::string prefix)
{
    Logging log("WordController :: findWord",true);
    dataBase->select(0,100);
    for(auto i = dataBase->begin(); i != dataBase->end(); i++)
    if ((*i)->Name() == prefix)
    {
        log << "INFO find word " << (*i)->Name() << std::endl;
        return *i;
    }
    return nullptr;
}

int WordController :: getMasteredWordCount(const int difficulty)
{
    dataBase->select(20 + difficulty);
    return dataBase->size();
}
int WordController :: getLearningWordCount(const int difficulty)
{
    dataBase->select(10 + difficulty);
    return dataBase->size();
}
