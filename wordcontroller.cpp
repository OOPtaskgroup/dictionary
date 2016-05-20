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
    dataBase->select(_RANGE(0,100));
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

    dataBase->select(_RANGE(10,19));
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

    dataBase->select(_RANGE(20,29));
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

void WordController :: setLearn (WordData* item)
{
    Logging log("WordController :: reLearn",true);
    item ->setTimes(0);
    item ->setType(20 + item->Type()%10);
    log << "INFO now word " << item->Name() << " will appear" << std::endl;
}

bool WordController :: isLearning (WordData* item)
{
    return (item->Type()/10 == 2);
}

bool WordController :: isMastered (WordData* item)
{
    return (item->Type()/10 == 3);
}

std::vector<WordData*> WordController :: getWord(int typel,int typer)
{
    Logging log("WordController :: getWord",true);
    dataBase->select(_RANGE(typel,typer));
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
    dataBase->select(_RANGE(0,100));
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
    dataBase->select(_RANGE(30,39));
    return dataBase->size();
}

int WordController :: getLearningWordCount()
{
    dataBase->select(_RANGE(20,29));
    return dataBase->size();
}

void WordController :: modifyLearningDifficulty(const int dif)
{
    Logging log("WordController :: modifyLearningDifficulty",true);
    log << "INFO change difficulty to " << dif << std::endl;
    dataBase->select(_RANGE(10,19));
    for(auto i = dataBase->begin();i!=dataBase->end();++i)
        (*i)->setType((*i)->Type()%10);
    dataBase->select(_RANGE(dif,dif));
    for(auto i = dataBase->begin();i!=dataBase->end();++i)
        (*i)->setType(dif+10);
    log << "INFO now " << dataBase->size() << " words waiting." << std::endl;
}

std::vector<std::string> WordController :: readDetail(std::string fileName)
{
    Logging log("WordController :: readDetail",true);
    std::ifstream input(fileName);
    std::vector<std::string> toReturn;
    std::string tmp;
    while(std::getline(input,tmp))
        toReturn.push_back(tmp);
    while(toReturn.size()<4)
        toReturn.insert(toReturn.begin(),"\n");
    return toReturn;
}

std::vector<std::string> WordController :: getDetail(WordData* item)
{
    Logging log("WordController :: getDetail",true);
    log << "INFO getting word " << item->Name() << " detail" << std::endl;
    std::vector<std::string> toReturn = readDetail(item->ContentFile());
    log << "INFO get " << toReturn.size() << " lines of Detail." << std::endl;
    if(toReturn.size()>4)
    {
        std::random_shuffle(toReturn.begin(),toReturn.begin()+toReturn.size()-2);
        std::vector<std::string> Return(toReturn.rbegin(),toReturn.rbegin()+4);
        std::reverse(Return.begin(),Return.end());
    }
    return toReturn;
}

void WordController::addExample(WordData *word, std::string item)
{
    Logging log("WordController :: addExample",true);
    log << "INFO inserting \"" << item << "\" to word " << word->Name() << std::endl;
    auto detail = readDetail(word->ContentFile());
    detail.insert(detail.begin(),item);
    std::ofstream output(word->ContentFile());
    for(auto i:detail)
        output << i << std::endl;
}

void WordController :: delExample(WordData *word, std::string item)
{
    Logging log("WordController :: delExample",true);
    log << "INFO deleting \"" << item << "\" in word " << word->Name() << std::endl;
    auto detail = readDetail(word->ContentFile());
    for(auto i = detail.begin(); i != detail.end(); ++i)
        if(*i == item)
        {
            detail.erase(i);
            break;
        }
    std::ofstream output(word->ContentFile());
    for(auto i:detail)
        output << i << std::endl;
}

std::vector<std::string> WordController :: getExample(WordData *word)
{
    auto toReturn = readDetail(word->ContentFile());
    return std::vector<std::string>(toReturn.begin(),toReturn.begin()+toReturn.size()-2);
}

std::vector<WordData*> WordController :: getTestWords(int num)
{
    Logging log("WordController :: getTestWords",true);
    std::vector<WordData*> toReturn;
    for(int i=1;i<=5;i++)
    {
        dataBase->select(_MOD(i));
        for(int j=1;j<=num/5;j++)
        {
            toReturn.push_back(dataBase->getrandom());
            log <<"INFO test word " << (*toReturn.rbegin())->Name() << std::endl;
        }
    }
}
