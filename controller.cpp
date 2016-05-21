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
    Logging log("Controller :: getDefaultUser",true);
    std::ifstream input("default.txt");
    std::string ID,passwd;
    int rem;
    if(input)
    {
        input >> ID >> rem;
        UserData* defaultUser = userController->findUser(ID);
        if(defaultUser)
        {
            log << "INFO now default user " << defaultUser->Name() << std::endl;
            if(rem)
            {
                log << "INFO remember password." << std::endl;
                passwd = defaultUser->Password();
            }
        }
        else ID="";
    }
    return std::make_pair(ID,passwd);
}

void Controller :: userModifyPassword(UserData* user, std::string passwd, std::string newPasswd)
{
    userController->userModifyPassword(user,passwd,newPasswd);
}

WordData* Controller :: findWord(std::string word)
{
    WordData* toReturn = wordController->findWord(word);
    if(toReturn)
        setHistoryLog(toReturn);
    return toReturn;;
}

std::vector< std::pair<WordData*,int> >& Controller :: getRecitingWords()
{
    Logging log("Controller :: getRecitingWords",true);
    if(nowRecitingWords.size() == 0)getTodayWords();
    if(nowRecitingWords.size() == 0)
    {
        log << "INFO get new words..." << std::endl;
        auto newWordCount = config->DailyNumber() * __newPart;
        auto oldWordCount = config->DailyNumber() - newWordCount;
        auto gotWords = wordController->randomWordCollect(newWordCount,oldWordCount);
        for(auto i : gotWords)
        {
            nowRecitingWords.push_back( std::make_pair( i, 0 ) );
            i->setType(i->Type()%10 + 20);
            log << "INFO get word " << i->Name() << " for today." << std::endl;
        }
    }
    reWriteTodayWords();
    return nowRecitingWords;
}

void Controller :: setAdditionWords(int num)
{
    Logging log("Controller :: setAdditionWords",true);
    auto gotWords = wordController->randomWordCollect(num,0);
    if(gotWords.empty())throw ItemNotFoundException("no new words to be recited now");
    for(auto i:gotWords)
    {
        nowRecitingWords.push_back(std::make_pair(i,0));
        i->setType(i->Type()%10+20);
        log << "INFO get word " << i->Name() << " for today." << std::endl;
    }
    reWriteTodayWords();
}

std::vector<WordData*> Controller :: getTestWords(int num)
{
    return wordController->getTestWords(num);
}

int Controller :: getVocabulary( std::vector< std::pair<WordData*,bool> > list)
{
    double toReturn=0;
    Logging log("Controller :: getVocabulary",true);
    for(auto i : list)
    if(i.second)
        toReturn+=wordController->getDifficultyWords(i.first->Type()%10) 
                    / (double)(list.size()/5);
    return (int)toReturn;
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

std::vector<WordData*> Controller :: getTextNewWords(std::string text)
{
    Logging log("Controller :: getTextNewWords",true);
    for(auto& i : text)
    if(i >='A' && i <= 'Z')
    {
        i +='a' - 'A';
    }
    else if(i<'a' || i>'z')
        i = ' ';
    std::string now = "";
    std::vector <WordData*> toReturn;
    for(auto i : text)
    if(i >='a' && i <='z')
    now+=i;
    else if(now != "")
    {
        WordData* word = findWord(now);
        if(word)
        {
            log << "INFO get word " << now << " from text. " << std::endl;
            toReturn.push_back(word);
        }
        now = "";
    }
    return toReturn;
}

std::vector<std::string> Controller :: getDetail(WordData* item)
{
    return wordController->getDetail(item);
}

std::vector<std::string> Controller :: getSearchHistory(UserData* user)
{
    Logging log("Controller :: getSearchHistory",true);
    std::vector<std::string> toReturn;
    std::ifstream input("userdatas" + _SLASH + user->Name() + _SLASH + "history.lis");
    std::string line;
    while(std::getline(input,line))
        toReturn.push_back(line);
    return toReturn;
}

void Controller :: setHistoryLog(WordData* word)
{
    Logging log("Controller :: setHistoryLog",true);
    UserData* user = getActiveUser();
    auto history = getSearchHistory(user);
    for(auto i = history.begin(); i!=history.end(); ++i)
        if(*i == word->Name())
        {
            history.erase(i);
            log << "INFO word " << word->Name() << " already in search history." << std::endl;
            break;
        }
    history.push_back(word->Name());
    std::ofstream output("userdatas" + _SLASH + user->Name() +_SLASH +"history.lis");
    for(auto i:history)
        output << i << std::endl;
}

std::string Controller :: getNowTheme()
{
    return config->getTheme();
}

void Controller :: modifyTheme(std::string nowTheme)
{
    config->modifyTheme(nowTheme);
}

std::string Controller :: setTheme(std::string name)
{
    auto theme = config->getTheme();
    auto fileName = ":/theme/" + theme + "/" + name + ".qss";
    std::ifstream input(fileName);
    std::stringstream buffer;
    buffer << input.rdbuf();
    return std::string(buffer.str());
}
