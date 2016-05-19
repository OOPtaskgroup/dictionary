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
//	void select(int type);
//        void select(int typel,int typer);
        
        template <typename T>
        void select(T chooser);
        int size();
};


class _RANGE
{
    int l,r;
    public:
    _RANGE(int l,int r):l(l),r(r){}
    bool operator () (int x)
    {
        if(x>=l && x<=r)
            return true;
        return false;
    }
};

class _MOD
{
    int dif;
    public:
    _MOD(int dif):dif(dif){}
    bool operator () (int x)
    {
        if(x%10 == dif)
            return true;
        return false;
    }
};
#endif
