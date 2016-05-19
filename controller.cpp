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

void Controller :: Login (std::string ID, std::string passwd, bool remPasswd)
{
    Logging log("Controller :: Login",true);
    UserData* toLogin = userController->checkIn(ID,passwd);
    Login(toLogin,remPasswd);
}

void Controller :: Login (UserData* user, bool remPasswd)
{
    userController->userLogin(user);
    wordController = new WordController("userdatas" + _SLASH+user->Name()+_SLASH+"words");
    config = new Configuration("userdatas"+_SLASH+user->Name()+_SLASH+"config");
    reWriteDefault(user,remPasswd);
}

void Controller :: Logout()
{
    if(!getActiveUser())throw ItemNotFoundException((std::string)"no user now.");
    if(config)delete config;
    if(wordController)delete wordController;
    userController->userLogout();
    nowRecitingWords.clear();
}

UserData* Controller :: userRegister(std::string ID, std::string passwd)
{
    return userController->userRegister(ID,passwd);
}

UserData* Controller :: getActiveUser()
{
    return userController->getActiveUser();
}

std::pair<std::string,std::string> Controller :: getDefaultUser()
{
    std::ifstream input("default.txt");
    std::string ID,passwd;
    if(input)
    {
        input>>ID;
        int rem;
        input>>rem;
        if(rem)
        {
            UserData* defaultUser = userController->findUser(ID);
            if(defaultUser)
                passwd = defaultUser->Password();
            else ID="";
        }
    }
    return std::make_pair(ID,passwd);
}

void Controller :: userModifyPassword(UserData* user, std::string passwd, std::string newPasswd)
{
    userController->userModifyPassword(user,passwd,newPasswd);
}

WordData* Controller :: findWord(std::string word)
{
    std::ofstream output("userdatas" + _SLASH + getActiveUser()->Name() + _SLASH + "history.lis",std::ios::app);
    output<<word<<std::endl;
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

std::vector<WordData*> Controller :: getTestWords(int num)
{
    return wordController->getTestWords(num);
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

void Controller :: setLearn(WordData* item)
{
    wordController->setLearn(item);
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

bool Controller :: isLearning (WordData* item)
{
    return wordController->isLearning(item);
}

bool Controller :: isMastered (WordData* item)
{
    return wordController->isMastered(item);
}

void Controller::addExample(WordData* word, std::string item)
{
    wordController->addExample(word,item);
}

void Controller::delExample(WordData *word, std::string item)
{
    wordController->delExample(word,item);
}

std::vector<std::string> Controller::getExample(WordData *word)
{
    return wordController->getExample(word);
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

void Controller :: reWriteDefault(UserData* user, bool remPasswd)
{
    std::ofstream output("default.txt");
    output << user->Name() << std::endl << (remPasswd?1:0);
}

void Controller :: reWriteTodayWords()
{
    Logging log("Controller :: reWriteTodayWords",true);
    std::string fileName("userdatas" + _SLASH+userController->getActiveUser()->Name() +_SLASH+ "today");
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
    std::string fileName("userdatas" +_SLASH+ userController->getActiveUser()->Name() +_SLASH +"today");
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

std::vector<std::string> Controller :: getDetail(WordData* item)
{
    return wordController->getDetail(item);
}

std::vector<std::string> Controller :: getSearchHistory(UserData* user)
{
    std::vector<std::string> toReturn;
    std::ifstream input("userdatas" + _SLASH + user->Name() + _SLASH + "history.lis");
    std::string line;
    while(std::getline(input,line))
        toReturn.push_back(line);
    return toReturn;
}

void Controller :: modifyTheme(std::string nowTheme)
{
    config->modifyTheme(nowTheme);
}

void Controller :: setTheme()
{
    auto theme = config->getTheme();
}
