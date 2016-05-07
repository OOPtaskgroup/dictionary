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
        WordDataBase(std::string fileName);
	~WordDataBase();
	std::vector<WordData*> getAll();
	WordData* FindWord(std::string str);
	bool isEmpty();
	//WordData* findword();
	void reWrite(const std::string& fileName);
	void insert(WordData* wd);
        std::vector<WordData*>::iterator begin();
        std::vector<WordData*>::iterator end();
	WordData* getrandom();
	void select(int type);
        void select(int typel,int typer);
        int size();
};

#endif
