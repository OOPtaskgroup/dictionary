//database.h
#ifndef DATABASE_H
#define DATABASE_H
#include <bits/stdc++.h>
#include "data.h" 

class DataBase
{
	public:
		~DataBase();
		virtual void insert()=0;
		virtual bool empty()=0;
};

#endif
