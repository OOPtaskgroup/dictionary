#include <bits/stdc++.h>
#include "logging.h"
#include "database.h"
#include "data.h"

UserController :: UserController (const DataBase* base, const UserData* defaultUser)
    : dataBase(base),nowActiveUser(defaultUser)
{

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
        log << "INFO already loged in." << std::endl;
    else
    {
        nowActiveUser = toLogin;
        log << "INFO login " << nowActiveUser->Name() << " ok." <<std::endl;
    }
}

UserData* UserController :: checkIn(std::string ID, std::string passwd)
{
    Logging log("UserController :: checkIn",true);
    for(auto i = dataBase.begin(); i != dataBase.end(); ++i)
        if( i->content()->Name() == ID)
        {
            log << "INFO catch user " << ID << "." <<std::endl;
            if( i->content()->Passwd() == passwd)
                return i->content();
        }
    return NULL;
}

UserData* iUserController :: userRegister(std::string ID, std::string passwd)
{
    Logging log("UserController :: userRegister",true);
    for(auto i = dataBase.begin(); i != dataBase.end(); ++i)
        if( i->content->Name() == ID)
        {
            log << "INFO find user with same ID." << std::endl;
            return NULL;
        }
    UserData* toReturn = new UserData (ID,passwd);
    dataBase.insert(toReturn);
    return toReturn;
}
