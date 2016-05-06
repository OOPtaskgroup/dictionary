#include"worddatabase.h"
#define random(x) (rand()%x)

WordDataBase::WordDataBase()
{
	std::ifstream fin[5];
	fin[0].open("Easy.txt");fin[1].open("Normal.txt");fin[2].open("Hard.txt");fin[3].open("Lunatic.txt");fin[4].open("Extra.txt");
	for(int i=0;i<5;i++)
	{
		char str[30];
		while (fin[i].getline(str,25))
		{
			WordData *pt = new WordData(str,i+1);
			worddatas.push_back(pt);
		}
	}
}

WordDataBase :: WordDataBase(std::string fileName)
{
    std::ifstream fin(fileName);
    std::string str;int tp;
    while(fin>>str>>tp)
    {
        WordData *pt = new WordData(str,tp);
        worddatas.push_back(pt);
    }
}

WordDataBase :: ~WordDataBase()
{

}

std::vector <WordData*> WordDataBase::getAll()
{
	std::vector <WordData*> wd(worddatas);
	return wd;
}

WordData* WordDataBase::FindWord(std::string str)
{
	for(std::vector<WordData*>::iterator iter=worddatas.begin();iter!=worddatas.end();++iter)
	{
		if ((*iter)->Name()==str)
		{
			return *iter;
		}
	}
	return nullptr;
}

bool WordDataBase::isEmpty()
{
	return worddatas.empty();
}

std::vector<WordData*>::iterator WordDataBase::begin()
{
	return worddatas.begin();
}

std::vector<WordData*>::iterator WordDataBase::end() 
{
	return worddatas.end();
}

void WordDataBase::reWrite(const std::string& fileName)
{
	std::ofstream fout(fileName);
	for(std::vector<WordData*>::iterator iter=worddatas.begin();iter!=worddatas.end();++iter)
	{
		fout<<(*iter)->Name()<<" "<<(*iter)->Type()<<std::endl;
	}
	fout.close();
}

void WordDataBase::insert(WordData* ud)
{
	worddatas.push_back(ud);
}

WordData* WordDataBase::getrandom()
{
	srand((int)time(0));
	return worddatas.at(random(worddatas.size()));
}

void WordDataBase::select(int type)
{
	if(!worddatal.empty())
	{
		swap(worddatas,worddatal);
		worddatal.clear();
	}
	swap(worddatas,worddatal);
	for(std::vector<WordData*>::iterator iter=worddatal.begin();iter!=worddatal.end();++iter)
	{
		if((*iter)->Type()==type)
		{
			worddatas.push_back(*iter);
		}
	}
}

int WordDataBase :: size()
{
    return worddatas.size();
}
