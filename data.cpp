#include "data.h"

Data :: Data(const std::string& name)
    :name(name),type(0)
{

}

Data :: Data(const std::string& name, const int type)
    :name(name),type(type)
{
    
}

Data :: ~Data()
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

void Data :: setContentFile(const std::string& toFile)
{
    contentFile = toFile;
}

const std::string& Data :: ContentFile()const
{
    return contentFile;
}
