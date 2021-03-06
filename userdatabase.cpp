#include "userdatabase.h"

UserDataBase::UserDataBase()
{
    Logging log("UserDataBase :: UserDataBase",true);
    std::ifstream fin("userdatas.txt");
    std::string str1,str2;
    while(fin>>str1>>str2)
    {
        UserData* pt = new UserData(str1,str2);
        userdatas.push_back(pt);
        log << "INFO " << pt->Name() << std::endl;
    }
    fin.close();
}

UserData* UserDataBase::findUser(std::string str)
{
    for (auto iter : userdatas)
        if(iter->Name()==str)
        {
            return iter;
        }
    return nullptr;
}

bool UserDataBase::empty()
{
    return userdatas.empty();
}

int UserDataBase::size()
{
    return userdatas.size();
}

void UserDataBase::save(const std::string fileName)
{
    Logging log("UserDataBase :: save",true);
    std::ofstream fout(fileName);
    log << "INFO " << userdatas.size() << std::endl;
    for(auto iter : userdatas)
    {
        fout<<iter->Name()<<" "<<iter->Password()<< std::endl;
        log<<"INFO "<<iter->Name() << std::endl;
    }
    fout.close();
}

void UserDataBase::insert(UserData* ud)
{
    userdatas.push_back(ud);
    save();
}

UserDataBase :: ~UserDataBase()
{

}

std::vector<UserData*>::iterator UserDataBase::begin()
{
    return userdatas.begin();
}

std::vector<UserData*>::iterator UserDataBase::end()
{
    return userdatas.end();
}
