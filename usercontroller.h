#ifndef USERCONTROLLER_H
#define USERCONTROLLER_H

#include <bits/stdc++.h>
#include "logging.h"
#include "database.h"
#include "data.h"

class UserController : public DataController
{
    UserData* nowActiveUser;
public:

    UserController(const DataBase* base, const UserData* defaultUser = NULL);
    ~UserController();

    void userLogout();
    void userLogin(UserData* toLogin);
    UserData* checkIn(std::string ID, std::string passwd);
    UserData* userRegister(std::string ID, std::string passwd);
}

#endif
