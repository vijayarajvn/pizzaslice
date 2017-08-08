#ifndef PIZZASLICE_DATABASE_MYSQLCONNECTION_H
#define PIZZASLICE_DATABASE_MYSQLCONNECTION_H

#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <mysql.h>

#include "Connection.h"

namespace PizzaSlice { namespace Database 
{

class MySQLConnection: public Connection
{
public:
    MySQLConnection(const boost::property_tree::ptree& config_):
        _config(config_)
    {
        connect();
    }

    ~MySQLConnection()
    {
        disconnect();
    }

    void connect();
    void disconnect();

private:
    boost::property_tree::ptree   _config;
    MYSQL *_mysql;

};
    
}}
#endif
