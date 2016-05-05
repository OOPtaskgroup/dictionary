#ifndef DATABASE_H
#define DATABASE_H
#include <bits/stdc++.h>
#include "data.h" 

class DataBase
{
public:
	virtual ~DataBase()=0;
	virtual void insert()=0;	
	virtual void throwout()=0;
	virtual bool empty()=0;
	virtual void select (int type)=0;
}

#endif 
