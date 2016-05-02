#include <bits/stdc++.h>
#include "data.h"

Data :: Data(const std::string& name)
    :name(name),type(0)
{

}

const std::string& Data :: Name()const
{
    return name;
}

const int& Data :: Type()const
{
    return type;
}

void Data :: setName(const std::string& toName)
{
    name = toName;
}

void Data :: setType(const int& toType)
{
    type = toType;
}
