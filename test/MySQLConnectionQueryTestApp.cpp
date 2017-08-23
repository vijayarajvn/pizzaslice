/*
  @brief - MySQLConnectionQueryTestApp is a simple program to test
  whether querying the Database::MySQLConnection works or not. This
  app just creates a table <expense> and fill it with a record each
  time you run it.

  How to test this app?
  1. Fill the database details in config.json
  2. Run app as : ./MySQLConnectionQueryTestApp <path-to-config.json>
  3. Login to your mysql database using mariadb-client.
  4. Select the database you gave in config.json
  5. Run query -  SHOW TABLES;
  6. You should see a table by name of expense. 
  7. Now run query - select * from EXPENSES:
  8. You should see atleast one entry in the table. (Viola - moment of
  glory - your database connection works!).
  9. If you run the app multiple times you will probably see multiple
  entries in the table. (Lucky that we have id as primary key).
 */

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
    /*
      Test there are enough arguments or not. Remember argv[0] is the
      program name. argv[1] is the acutal first argument.
     */

    if(2 != argc)
    {
        std::cerr << "Please pass the config file as the only argument. " << std::endl;
        return -1;
    }

    boost::property_tree::ptree config;

    /*
      read_json will probably throw an exception if he finds any error
      parsing the json file. So enclose it in try-catch block.
     */
    try 
    {
        boost::property_tree::read_json(argv[1], config);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Please pass valid config file. The current config file returned error:" 
                  << e.what() << std::endl;
        return -1;
    }

    PizzaSlice::Database::PizzaExpense pizzaExpense;
    pizzaExpense._type = PizzaSlice::Database::PizzaDailyRecords::Category::VEG;
    pizzaExpense._date = boost::posix_time::microsec_clock::local_time();
    pizzaExpense._expense = 100;
    pizzaExpense._description = "test description";

    std::cout <<"Going to create mysql connection object." << std::endl;
    PizzaSlice::Database::MySQLConnection dbConn(config);
    //dbConn.connect();
    dbConn.addExpense(pizzaExpense);

    return 0;
}
