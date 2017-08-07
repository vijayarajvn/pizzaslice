#include "MySQLConnection.h"

namespace PizzaSlice { namespace Database 
{
    void MySQLConnection::connect()
    {
        _mysql = mysql_init(NULL);

        mysql_options(_mysql, MYSQL_OPT_RECONNECT, (void *)"1");
        
        std::string host = _config.get<std::string>("Pizzaslice.Database.host");
        std::string user = _config.get<std::string>("Pizzaslice.Database.user");
        std::string password = _config.get<std::string>("Pizzaslice.Database.password");
        std::string db = _config.get<std::string>("Pizzaslice.Database.db");

        if(mysql_real_connect(_mysql,
                              host.c_str(),
                              user.c_str(),
                              password.c_str(),
                              db.c_str(),
                              _config.get<unsigned>("Pizzaslice.Database.port"),
                              NULL,
                              0) == NULL)
        {
            std::cout << "MySQL connection failed.";
        }
        else
        {
            std::cout << "MySQL connection succeedded.";
        }
    }

    void MySQLConnection::disconnect()
    {
        std::cout << "Closing...";
        mysql_close(_mysql);
    }


}}
