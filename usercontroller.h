#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#ifdef __linux__
#define _SLASH (std::string)"/"
#elif _WIN32
#define _SLASH (std::string)"\\"
#elif __APPLE__
#define _SLASH (std::string)"/"
#endif


#include <bits/stdc++.h>
#include "logging.h"
#include "userdatabase.h"
#include "userdata.h"
#include "datacontroller.h"
#include "exceptions.h"

class UserController : public DataController
{
    UserData* nowActiveUser;
    UserDataBase* dataBase;
public:

    UserController();
    ~UserController();

    void userLogout();
    void userLogin(UserData* toLogin);
    UserData* checkIn(std::string ID, std::string passwd);
    UserData* userRegister(std::string ID, std::string passwd);
    UserData* getActiveUser();
    void userModifyPassword(UserData* user, std::string passwd, std::string newPasswd);
};

#endif
