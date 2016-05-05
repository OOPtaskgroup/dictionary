#include<bits/stdc++.h>
#include"worddatabase.h"
#define random(x) (rand()%x)

worddatabase::worddatabase()
{
	std::ifstream fin[5];
	fin[0].open("Easy.txt");fin[1].open("Normal.txt");fin[2].open("Hard.txt");fin[3].open("Lunatic.txt");fin[4].open("Extra.txt");
	for(int i=0;i<5;i++)
	{
		char str[30];
		while (fin[i].getline(str,25))
		{
			WordData *pt = new WordData(str);
			worddatas.push_back(pt);
		}
	}
}

std::vector <WordData*> worddatabase::getAll()
{
	std::vector <WordData*> wd(worddatas);
	return wd;
}

bool worddatabase::findword(std::string str)
{
	for(std::vector<WordData*>::iterator iter=worddatas.begin();iter!=worddatas.end();++iter)
	{
		if ((*iter)->Name()==str)
		{
			return true;
		}
	}
	return false;
}

bool worddatabase::isempty()
{
	return worddatas.empty();
}

WordData* worddatabase::begin()
{
	return *(worddatas.begin());
}

WordData* worddatabase::end() 
{
	return *(worddatas.end());
}

void worddatabase::recitenow()
{
	std::ofstream fout("words.txt");
	for(std::vector<WordData*>::iterator iter=worddatas.begin();iter!=worddatas.end();++iter)
	{
		fout<<(*iter)->Name()<<" "<<(*iter)->Type()<<std::endl;
	}
	fout.close();
}

void worddatabase::insert(WordData* ud)
{
	worddatas.push_back(ud);
	std::ofstream fout("worddatas.txt");
	for(std::vector<WordData*>::iterator iter=worddatas.begin();iter!=worddatas.end();++iter)
	{
		fout<<(*iter)->Name()<<"\n";
	}
	fout.close();
}

WordData* worddatabase::getrandom()
{
	srand((int)time(0));
	return worddatas.at(random(worddatas.size()));
}

void worddatabase::select(int type)
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
