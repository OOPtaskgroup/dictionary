#include<bits/stdc++.h>
#include"userdatabase.h"

userdatabase::userdatabase()
{
	std::ifstream fin("userdatas.txt")
	int count=0;
	while(fin>>userdatas.at(count)->name>>userdatas.at(count)->password)
	{
		count++;
	}
	fin.close();
}

bool userdatabase::finduser(std::string str)
{
	for (vector<UserData*>::iterator iter=userdatas.begin();iter!=userdatas.end();++iter)
	{
		if(userdatas.at(iter)->name==str)
		{
			return true;
		}
	}
	return false;
}

bool userdatabase::empty()
{
	return userdatas.empty();
}

int userdatabase::usernumber()
{
	return userdatas.size();
}

void userdatabase::insert(UserData* ud)
{
	userdatas.push_back(ud);
	std::ofstream fout("userdatas.txt");
	for(vector<UserData*>::iterator iter=userdatas.begin();iter!=userdatas.end();++iter)
	{
		fout<<(*iter)->name<<"\n"<<userdatas.at(iter)->password;
	}
	fout.close();
}
