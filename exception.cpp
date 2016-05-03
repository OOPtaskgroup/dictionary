#include "exception.h"
#include "logging.h"

Exception :: Exception(const std::string& inform)
    :information(inform)
{
    Logging log("Exception :: Exception",true);
    log << "INFO get Exception " << information <<std::endl;
}

std::string Exception :: getInformation()const
{
    return information;
}
