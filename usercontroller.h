#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <bits/stdc++.h>
#include "logging.h"
#include "userdatabase.h"
#include "userdata.h"

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
};

#endif
