#include<bits/stdc++.h>
#include"worddatabase.h"
#define random(x) (rand()%x)

worddatabase::worddatabase()
{
	std::ifstream fin[5];
	fin[1].open("Easy.txt");fin[2].open("Normal.txt");fin[3].open("Hard.txt");fin[4].open("Lunatic.txt");fin[5].open("Extra.txt");
	for(int i=0;i<5;i++)
	{
		char str[30];
		while (fin.getline(str,25))
		{
			WordData *pt = new WordData;
			worddatas.push_back(pt);
			pt->Data(str); 
		}
	}
}

std::vector <WordData*> worddatabase::getAll()
{
	std::vector <WordData> wd(this->worddatas);
	return wd;
}

bool findword(std::string str)
{
	for(vector<WordData*>::iterator iter=worddatas.begin();iter!=worddatas.end();++iter)
	{
		if (worddatas.at(iter)->name==str)
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
	return worddatas.begin();
}

WordData* worddatabase::end() 
{
	return worddatas.end();
}

void worddatabase::recitenow()
{
	std::ofstream fout("words.txt")
	for(vector<WordData*>::iterator iter=worddatas.begin();iter!=worddatas.end();++iter)
	{
		fout<<(*iter)->Name()<<" "<<(*iter)->Type<<std::endl;
	}
	fout.close;
}

WordData* worddatabase::getrandom()
{
	srand((int)time(0))
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
	for(vector<WordData*>::iterator iter=worddatal.begin();iter!=worddatal.end();++iter)
	{
		if((*iter)->Type==type)
		{
			worddatas.push_back(worddatal);
		}
	}
}
