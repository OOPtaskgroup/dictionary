#include <bits/stdc++.h>
#include "worddata.h"
#include "bits/stdc++.h"

WordData :: WordData(const std::string name)
    :Data(name)
{
    setContentFile("worddata/"+name+".information");
}

WordData :: ~WordData()
{

}
