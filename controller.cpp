#include "controller.h"

Controller :: Controller (const std::string defaultUserFile)
{
    Logging log("Controller :: Controller",true);
    srand(time(NULL));
    userController = new UserController();
    std::ifstream input(defaultUserFile);
    if(input.is_open())
    {
        std::string ID,passwd;
        input >> ID >> passwd;
        Login(ID,passwd);
        log << "INFO from file " << defaultUserFile << " find user " << ID << "." << std::endl;
    }
}

Controller :: ~Controller ()
{
    if(getActiveUser())Logout();
    if(userController) delete userController;
}

void Controller :: Login (std::string ID, std::string passwd)
{
    Logging log("Controller :: Login",true);
    UserData* toLogin = userController->checkIn(ID,passwd);
    userController->userLogin(toLogin);
    wordController = new WordController("userdatas/"+ID+"/words");
    config = new Configuration("userdatas/"+ID+"/config");
}

void Controller :: Logout()
{
    if(!getActiveUser())throw ItemNotFoundException((std::string)"no user now.");
    if(config)delete config;
    if(wordController)delete wordController;
    userController->userLogout();
}

UserData* Controller :: userRegister(std::string ID, std::string passwd)
{
    return userController->userRegister(ID,passwd);
}

UserData* Controller :: getActiveUser()
{
    return userController->getActiveUser();
}

void Controller :: userModifyPassword(UserData* user, std::string passwd, std::string newPasswd)
{
    userController->userModifyPassword(user,passwd,newPasswd);
}

WordData* Controller :: findWord(std::string word)
{
    return wordController->findWord(word);
}

std::vector< std::pair<WordData*,int> >& Controller :: getRecitingWords()
{
    if(nowRecitingWords.size() == 0)getTodayWords();
    if(nowRecitingWords.size() == 0)
    {
        auto gotWords = wordController->randomWordCollect(config->DailyNumber());
        for(auto i : gotWords)
        {
            nowRecitingWords.push_back( std::make_pair( i, 0 ) );
            i->setType(i->Type()%10 + 20);
        }
    }
    reWriteTodayWords();
    return nowRecitingWords;
}

void Controller :: answerAccepted( std::pair<WordData*,int> &item)
{
    item.second ++;
    if(item.second == 1)
        wordController->answerAccepted(item.first);
    reWriteTodayWords();
}

void Controller :: answerWrong( std::pair<WordData*,int> &item)
{
    item.second = -1;
    wordController->answerWrong(item.first);
    reWriteTodayWords();
}

void Controller :: reLearn(WordData* item)
{
    wordController->reLearn(item);
}

std::vector<WordData*> Controller :: getMasteredWord()
{
    return wordController->getMasteredWord();
}

std::vector<WordData*> Controller :: getLearningWord()
{
    return wordController->getLearningWord();
}

int Controller :: getMasteredWordCount()
{
    return wordController->getMasteredWordCount();
}

int Controller :: getLearningWordCount()
{
    return wordController->getLearningWordCount();
}

const Configuration& Controller :: getConfig() const
{
    if(!config) throw ItemNotFoundException((std::string)"config does not exist");
    return *config;
}

void Controller :: modifyConfig(const int& dif, const int& num)
{
    if(!config) throw ItemNotFoundException((std::string)"config does not exist.");
    config->modify(dif,num);
    wordController->modifyLearningDifficulty(dif);
}

void Controller :: modifyConfig(const Configuration& newConfig)
{
    modifyConfig(newConfig.Difficulty(), newConfig.DailyNumber());
}

void Controller :: reWriteTodayWords()
{
    Logging log("Controller :: reWriteTodayWords",true);
    std::string fileName("userdatas/" + userController->getActiveUser()->Name() + "/today");
    std::ofstream output(fileName, std::ios_base::trunc);
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    output << (1900 + now->tm_year) << " " << (1 + now->tm_mon) << " " << (now->tm_mday) << std::endl;
    log << "INFO print today words to " << fileName << std::endl;
    for(auto i : nowRecitingWords)
        output << (i.first->Name()) << std::endl << i.second << std::endl;
}

void Controller :: getTodayWords()
{
    Logging log("Controller :: getTodayWords",true);
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);
    std::string fileName("userdatas/" + userController->getActiveUser()->Name() + "/today");
    std::ifstream input(fileName);
    if(!input)return;
    int year,month,day;
    input >> year >> month >> day;
    log << "INFO file was written on " << year << "/" << month << "/" << day << std::endl;
    if(year != now->tm_year+1900 || month != now->tm_mon+1 || day != now->tm_mday)return;
    std::string name;
    int type;
    std::getline(input,name);
    while(std::getline(input,name))
    {
        input>>type;
        nowRecitingWords.push_back( std::make_pair(findWord(name), type));
        std::getline(input,name);
    }
}
