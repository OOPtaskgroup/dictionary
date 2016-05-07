#include"userdatabase.h"

UserDataBase::UserDataBase()
{
	std::ifstream fin("userdatas.txt");
        std::string str1,str2;
	while(fin>>str1>>str2)//>>userdatas.at(count)->password)
	{
		UserData* pt = new UserData(str1,str2);
		userdatas.push_back(pt);
		//pt->setPassword(str2); 
	}
	fin.close();
}

bool UserDataBase::findUser(std::string str)
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

bool UserDataBase::empty()
{
	return userdatas.empty();
}

int UserDataBase::userNumber()
{
	return userdatas.size();
}

void UserDataBase::insert(UserData* ud)
{
	userdatas.push_back(ud);
	std::ofstream fout("userdatas.txt");
	for(std::vector<UserData*>::iterator iter=userdatas.begin();iter!=userdatas.end();++iter)
	{
		fout<<(*iter)->Name()<<" "<<(*iter)->Password()<<"\n";//<<(*iter)->password;
	}
	fout.close();
}

UserDataBase :: ~UserDataBase()
{

}

std::vector<UserData*>::iterator UserDataBase::begin()
{
    return userdatas.begin();
}

std::vector<UserData*>::iterator UserDataBase::end()
{
    return userdatas.end();
}
