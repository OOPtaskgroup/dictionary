#include <bits/stdc++.h>
#include "userdata.h"

UserData :: UserData(const std::string& name)
    :Data(name)
{
    setContentFile("userdata/"+name+"/config");
}

UserData :: ~UserData()
{

}
