#ifndef USERDATABASE_H
#define USERDATABASE_H
#include<bits/stdc++.h>
#include"database.h"
#include"userdata.h"
#include "logging.h"

class UserDataBase : public DataBase
{
	std :: vector <UserData*> userdatas;
public:
	UserDataBase();
	~UserDataBase();
	virtual void insert(UserData*);
	virtual bool empty();
	bool findUser(std::string str);
	void save();
	int userNumber();
        std::vector<UserData*>::iterator begin();
        std::vector<UserData*>::iterator end();

};


#endif
