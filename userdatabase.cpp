#include<bits/stdc++.h>
#include"userdatabase.h"

userdatabase::userdatabase()
{
	std::ifstream fin("userdatas.txt");
	char str1[15],str2[20];
	while(fin>>str1>>str2)//>>userdatas.at(count)->password)
	{
		UserData* pt = new UserData(str1);
		userdatas.push_back(pt);
		//pt->setPassword(str2); 
	}
	fin.close();
}

bool userdatabase::finduser(std::string str)
{
	for (std::vector<UserData*>::iterator iter=userdatas.begin();iter!=userdatas.end();++iter)
	{
		if((*iter)->Name()==str)
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
	for(std::vector<UserData*>::iterator iter=userdatas.begin();iter!=userdatas.end();++iter)
	{
		fout<<(*iter)->Name()<<"\n";//<<(*iter)->password;
	}
	fout.close();
}

