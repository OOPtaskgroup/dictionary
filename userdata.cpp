#include <bits/stdc++.h>
#include "userdata.h"

UserData :: UserData(const std::string& name, const std::string& password)
    :Data(name),passwd(password)
{
    setContentFile("userdata/"+name+"/config");
}

UserData :: ~UserData()
{

}

const std::string& UserData :: Password()
{
    return passwd;
}

void UserData :: setPassword(const std::string& newPassword)
{
    passwd = newPassword;
}
