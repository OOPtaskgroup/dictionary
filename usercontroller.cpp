#include "usercontroller.h"
UserController :: UserController ()
{
    dataBase = new UserDataBase();
    nowActiveUser = nullptr;
}
UserController :: ~UserController()
{

}

void UserController :: userLogout()
{
    Logging log("UserController :: userLogout",true);
    if (nowActiveUser)
    {
        log << "INFO user " << nowActiveUser->Name() << " loged out." <<std::endl;
        nowActiveUser = nullptr;
    }
    else log << "INFO no active user now. cannot logout." << std::endl;
}

void UserController :: userLogin(UserData* toLogin)
{
    Logging log("UserController :: userLogin",true);
    if (nowActiveUser)
    {
        log << "INFO already loged in." << std::endl;
        throw ItemAlreadyExistException((std::string)"already loged in.");
    }
    else
    {
        nowActiveUser = toLogin;
        log << "INFO login " << nowActiveUser->Name() << " ok." <<std::endl;
    }
}

UserData* UserController :: findUser(std::string ID)
{
    Logging log("UserController :: findUser",true);
    for(auto i = dataBase->begin(); i != dataBase->end(); ++i)
        if( (*i)->Name() == ID)
            return *i;
    return nullptr;
}

UserData* UserController :: checkIn(std::string ID, std::string passwd)
{
    Logging log("UserController :: checkIn",true);
    UserData* toReturn = findUser(ID);
    if(toReturn)
    {
        if(toReturn->Password() == passwd)
            return toReturn;
        else
            throw PasswordNotCorrectException((std::string)"password wrong!");
    }
    else throw ItemNotFoundException((std::string)"user not exist!");
}

UserData* UserController :: userRegister(std::string ID, std::string passwd)
{
    Logging log("UserController :: userRegister",true);
    for(auto i = dataBase->begin(); i != dataBase->end(); ++i)
        if( (*i)->Name() == ID)
        {
            log << "INFO find user with same ID." << std::endl;
            throw ItemAlreadyExistException((std::string)"user already exist!");
        }
    UserData* toReturn = new UserData (ID,passwd);
    std::system(((std::string)"mkdir userdatas" + _SLASH + ID + "").c_str());
    dataBase->insert(toReturn);
    return toReturn;
}

UserData* UserController :: getActiveUser()
{
    return nowActiveUser;
}

void UserController :: userModifyPassword(UserData* user, std::string passwd, std::string newPasswd)
{
    Logging log("UserController :: userModifyPassword",true);
    if(user->Password() != passwd)
        throw PasswordNotCorrectException((std::string)"password wrong!");
    user->setPassword(newPasswd);
    log << "INFO " <<passwd << " -> " << newPasswd <<std::endl;
    dataBase->save();
}
