#include "wordcontroller.h"

WordController :: WordController(std::string ContentFile)
    :contentFile(ContentFile)
{
    Logging log("WordController :: WordController",true);
    std::ifstream input(contentFile);
    if(input)
    {
        input.close();
        log << "INFO find file" << std::endl;
        dataBase = new WordDataBase(contentFile);
    }
    else
    {
        input.close();
        dataBase = new WordDataBase();
        dataBase->reWrite(contentFile);
    }
    dataBase->select(0,100);
    log << "INFO " << dataBase->size() << std::endl;
}

WordController :: ~WordController()
{
    Logging log("WordController :: ~WordController",false);
    dataBase->reWrite(contentFile);
    delete dataBase;

}
std::vector<WordData*> WordController :: randomWordCollect(int num)
{
    Logging log("WordController :: wordCollect",true);
    int noLearned = (int)(num * __newPart);
    int Learned = num -noLearned;

    std::vector<WordData*> toReturn;

    dataBase->select(10,19);
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

    dataBase->select(20,29);
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
        item->setType(30 + item->Type()%10);
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
    item ->setType(20 + item->Type()%10);
    log << "INFO now word " << item->Name() << " will appear again." << std::endl;
}

std::vector<WordData*> WordController :: getWord(int typel,int typer)
{
    Logging log("WordController :: getWord",true);
    dataBase->select(typel,typer);
    std::vector<WordData*> toReturn = dataBase->getAll();
    log << "INFO get " << toReturn.size() << " words." << std::endl;
    return toReturn;
}

std::vector<WordData*> WordController :: getWord(int type)
{
    return getWord(type,type);
}

std::vector<WordData*> WordController :: getMasteredWord()
{
    return getWord(30,39);
}

std::vector<WordData*> WordController :: getLearningWord()
{
    return getWord(20,29);
}

WordData* WordController :: findWord(std::string prefix)
{
    Logging log("WordController :: findWord",true);
    log << "INFO looking for word " << prefix << std::endl;
    dataBase->select(0,100);
    for(auto i = dataBase->begin(); i != dataBase->end(); i++)
    if ((*i)->Name() == prefix)
    {
        log << "INFO find word " << (*i)->Name() << std::endl;
        return *i;
    }
    return nullptr;
}

int WordController :: getMasteredWordCount()
{
    dataBase->select(30,39);
    return dataBase->size();
}

int WordController :: getLearningWordCount()
{
    dataBase->select(20,29);
    return dataBase->size();
}

void WordController :: modifyLearningDifficulty(const int dif)
{
    Logging log("WordController :: modifyLearningDifficulty",true);
    log << "INFO change difficulty to " << dif << std::endl;
    dataBase->select(10,19);
    for(auto i = dataBase->begin();i!=dataBase->end();++i)
        (*i)->setType((*i)->Type()%10);
    dataBase->select(dif);
    for(auto i = dataBase->begin();i!=dataBase->end();++i)
        (*i)->setType(dif+10);
    log << "INFO now " << dataBase->size() << " words waiting." << std::endl;
}
