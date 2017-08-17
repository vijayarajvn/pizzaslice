#ifndef PIZZASLICE_DATABASE_MYSQLCONNECTION_H
#define PIZZASLICE_DATABASE_MYSQLCONNECTION_H

#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <mysql.h>

#include "Connection.h"
#include "Structs.h"
namespace PizzaSlice { namespace Database 
{

    class MySQLConnection: public Connection
    {
      public:
        typedef std::vector<boost::optional<std::string> >  SingleQueryResult;
        typedef std::vector<SingleQueryResult>  QueryResults;

        MySQLConnection(const boost::property_tree::ptree& config_);
        ~MySQLConnection();

        void connect();
        void disconnect();

        bool addExpense(PizzaExpense& pizzaExpense_);
      private:
        std::pair<bool, QueryResults> executeQuery(const std::string& query_);
        std::pair<bool, QueryResults> executeMultipleQueriesWithSingleResult(const std::string& query_);
        std::pair<bool, std::string> addEscapeCharacters(const std::string& query_);

        boost::property_tree::ptree   _config;
        MYSQL *_mysql;
    };
    
} //namespace Databse
} //namespace PizzaSlice

#endif
