#ifndef DATACONTROLLER_H
#define DATACONTROLLER_H

#include <bits/stdc++.h>
#include "logging.h"
#include "database.h"
#include "data.h"

class DataController
{
    DataBase* dataBase;
public:
    DataController(const DataBase* base);
    virtual ~DataController()=0;
    
};

#endif
