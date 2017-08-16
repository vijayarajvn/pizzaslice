#include <iostream>
#include <sstream>
#include "CommandLine.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "Database/MySQLConnection.h"
#include "Database/Structs.h"
#include "Utils/UtilityFunctions.h"

int main(int argc, char* argv[])
{
    if(2 != argc)
    {
        std::cerr << "Please pass the config file as the only argument. " << std::endl;
        return -1;
    }

    // Reading config file
    boost::property_tree::ptree config;
    try 
    {
        boost::property_tree::read_json(argv[1], config);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Please pass valid config file. The current config file returned error:" << e.what() << std::endl;
        return -1;
    }

    std::stringstream menu;
    menu << "Select one of the options:" << std::endl
         << "1. Change mess manager" << std::endl
         << "2. Expenses" << std::endl
         << "3. Daily Records" << std::endl;

    PizzaSlice::CommandLine::out(menu);    
    unsigned option = PizzaSlice::CommandLine::in<unsigned>("Choice: ");

    //testing details
    if(3 == option)
    {
        PizzaSlice::Database::PizzaExpense pizzaExpense;
        pizzaExpense._type = PizzaSlice::Database::PizzaDailyRecords::Category::VEG;
        pizzaExpense._date = boost::posix_time::microsec_clock::local_time();
        pizzaExpense._expense = 100;
        pizzaExpense._description = "test description";

        std::cout <<"going to create mysql connection object.";
        PizzaSlice::Database::MySQLConnection dbConn(config);
        //dbConn.connect();
        dbConn.addExpense(pizzaExpense);
    }

    return 0;
}
