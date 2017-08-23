#include "UtilityFunctions.h"

namespace PizzaSlice { namespace Utils 
{  
    boost::posix_time::ptime convertStringToPtime(const std::string& timeStr_)
    {
        return boost::posix_time::time_from_string(timeStr_);
    }

    std::string convertPtimeToString(const boost::posix_time::ptime& ptime_)
    {
        std::string timeStr = boost::gregorian::to_iso_extended_string(ptime_.date()) + ' ' +
            boost::posix_time::to_simple_string(ptime_.time_of_day());
        return timeStr;
    }

} //namespace Databse
} //namespace PizzaSlice