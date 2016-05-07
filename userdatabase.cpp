#include"userdatabase.h"

UserDataBase::UserDataBase()
{
        Logging log("UserDataBase :: UserDataBase",true);
	std::ifstream fin("userdatas.txt");
        std::string str1,str2;
	while(fin>>str1>>str2)
	{
		UserData* pt = new UserData(str1,str2);
		userdatas.push_back(pt);
                log << "INFO " << pt->Name() << std::endl;
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

void UserDataBase::save()
{
        Logging log("UserDataBase :: save",true);
	std::ofstream fout("userdatas.txt");
        log << "INFO " << userdatas.size() << std::endl;
        std::cout << userdatas[0]<<std::endl;
	for(std::vector<UserData*>::iterator iter=userdatas.begin();iter!=userdatas.end();++iter)
	{
                std::cout << (*iter)->Name() <<std::endl;
		fout<<(*iter)->Name()<<" "<<(*iter)->Password()<< std::endl;
                log<<"INFO "<<(*iter)->Name() << std::endl;
                std::cout << (*iter)->Name() <<std::endl;
	}
	fout.close();
}

void UserDataBase::insert(UserData* ud)
{
    userdatas.push_back(ud);
    save();
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
