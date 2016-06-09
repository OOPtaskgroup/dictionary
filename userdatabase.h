#ifndef USERDATABASE_H
#define USERDATABASE_H
#include <bits/stdc++.h>
#include "database.h"
#include "userdata.h"
#include "logging.h"

class UserDataBase : public DataBase
{
    std :: vector <UserData*> userdatas;
public:
    UserDataBase();
    ~UserDataBase();
    void insert(UserData*);
    bool empty();
    UserData* findUser(std::string str);
    void save(const std::string fileName = "userdatas.txt");
    int size();
    std::vector<UserData*>::iterator begin();
    std::vector<UserData*>::iterator end();

};


#endif
