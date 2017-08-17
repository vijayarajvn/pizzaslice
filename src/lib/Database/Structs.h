#ifndef DATABASE_STRUCTS
#define DATABASE_STRUCTS

#include <string>

#include <boost/date_time/posix_time/ptime.hpp>
#include <boost/property_tree/ptree.hpp>

namespace PizzaSlice { namespace Database 
{
    struct PizzaDailyRecords
    {
        enum class Session
        {
            BREAKFAST,
            LUNCH,
            DINNER
        };

        enum class Category
        {
            VEG,
            NONVEG
        };

        int                             _id;
        boost::posix_time::ptime        _date;
        int                             _memberId;
        Session                         _session;
        Category                        _category;
    };
    
    struct PizzaExpense
    {
        int                             _id;
        PizzaDailyRecords::Category     _type;
        boost::posix_time::ptime        _date;
        double                          _expense;
        std::string                     _description;
        
    };
                      
    struct PizzaMemeber
    {
        int                             _id;
        std::string                     _name;
    };

} //namespace Databse
} //namespace PizzaSlice

#endif