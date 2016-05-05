#ifndef WORDDATABASE_H
#define WORDDATABASE_H
#include<bits/stdc++.h>
#include"database.h"
#include"worddata.h"

class WordDataBase : public DataBase
{
	std :: vector <WordData*> worddatas,worddatal;
public:
	WordDataBase();
	~WordDataBase();
	std::vector<WordData*> getAll();
	bool FindWord(std::string str);
	bool isEmpty();
	//WordData* findword();
	void reciteNow();
	void insert(WordData* wd);
	WordData* begin();
	WordData* end();
	WordData* getrandom();
	void select(int type);
};

#endif
