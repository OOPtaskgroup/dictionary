#ifndef WORDDATABASE_H
#define WORDDATABASE_H
#include<bits/stdc++.h>
#include"database.h"
#include"worddata.h"

class worddatabase : public DataBase
{
	std :: vector <WordData*> worddatas(10000),worddatal;
public:
	worddatabase();
	~worddatabase();
	std::vector<WordData*> getAll();
	bool findword(std::sttring str);
	bool isempty();
	//WordData* findword();
	void recitenow();
	WordData* begin();
	WordData* end();
	WordData* getrandom();
}

#endif
