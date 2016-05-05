#ifndef USERDATABASE_H
#define USERDATABASE_H
#include<bits/stdc++.h>
#include"database.h"
#include"userdata.h"

class userdatabase : public DataBase
{
	std :: vector <UserData*> userdatas;
public:
	userdatabase();
	~userdatabase();
	virtual void insert(UserData*);
	virtual bool empty();
	bool finduser(std::string str);
	//virtual void throwout();
	int usernumber();
}


#endif
