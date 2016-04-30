#include <bits/stdc++.h>
#include "logging.h"
#include "database.h"
#include "data.h"
#include "datacontroller.h"

DataControlller :: DataController(const DataBase* base)
    :dataBase(base)
{
    Logging log("DataController :: DataController",false);
}



