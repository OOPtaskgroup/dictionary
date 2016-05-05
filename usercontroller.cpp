#include <bits/stdc++.h>
#include "exceptions.h"
#include "usercontroller.h"
UserController :: UserController ()
{
    dataBase = new UserDataBase();
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
        nowActiveUser = NULL;
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

UserData* UserController :: checkIn(std::string ID, std::string passwd)
{
    Logging log("UserController :: checkIn",true);
    for(auto i = dataBase->begin(); i != dataBase->end(); ++i)
        if( (*i)->Name() == ID)
        {
            log << "INFO catch user " << ID << "." <<std::endl;
            if( (*i)->Password() == passwd)
                return *i;
            else
                throw PasswordNotCorrectException((std::string)"password wrong!");
        }
    throw ItemNotFoundException((std::string)"user not exist!");
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
    dataBase->insert(toReturn);
    return toReturn;
}

UserData* UserController :: getActiveUser()
{
    return nowActiveUser;
}
