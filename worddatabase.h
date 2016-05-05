#ifndef WORDDATABASE_H
#define WORDDATABASE_H
#include<bits/stdc++.h>
#include"database.h"
#include"worddata.h"

class worddatabase : public DataBase
{
	std :: vector <WordData*> worddatas,worddatal;
public:
	worddatabase();
	~worddatabase();
	std::vector<WordData*> getAll();
	bool findword(std::string str);
	bool isempty();
	//WordData* findword();
	void recitenow();
	void insert(WordData* wd);
	WordData* begin();
	WordData* end();
	WordData* getrandom();
	void select(int type);
};

#endif
