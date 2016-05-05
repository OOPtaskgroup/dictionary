#ifndef USERDATABASE_H
#define USERDATABASE_H
#include<bits/stdc++.h>
#include"database.h"
#include"userdata.h"

class UserDataBase : public DataBase
{
	std :: vector <UserData*> userdatas;
public:
	UserDataBase();
	~UserDataBase();
	virtual void insert(UserData*);
	virtual bool empty();
	bool findUser(std::string str);
	//virtual void throwout();
	int userNumber();
};


#endif
