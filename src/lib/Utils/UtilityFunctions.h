#ifndef PIZZASLICE_UTILS_UTILITY_FUNCTIONS_H
#define PIZZASLICE_UTILS_UTILITY_FUNCTIONS_H

#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace PizzaSlice { namespace Utils 
{
    boost::posix_time::ptime convertStringToPtime(const std::string& timeStr_);
    std::string convertPtimeToString(const boost::posix_time::ptime& ptime_);

} //namespace Databse
} //namespace PizzaSlice

#endif