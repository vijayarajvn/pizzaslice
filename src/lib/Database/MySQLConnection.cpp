#include <sstream>

#include "Utils/UtilityFunctions.h"
#include "MySQLConnection.h"

namespace PizzaSlice { namespace Database 
{
    MySQLConnection::MySQLConnection(const boost::property_tree::ptree& config_)
    : _config(config_)
    {
        connect();
    }

    MySQLConnection::~MySQLConnection()
    {
        disconnect();
    }

    void MySQLConnection::connect()
    {
        _mysql = mysql_init(NULL);

        //mysql_options(_mysql, MYSQL_OPT_RECONNECT, (void *)"1");
        
        std::string host = _config.get<std::string>("PizzaSlice.Database.host");
        std::string user = _config.get<std::string>("PizzaSlice.Database.user");
        std::string password = _config.get<std::string>("PizzaSlice.Database.password");
        std::string db = _config.get<std::string>("PizzaSlice.Database.db");
        unsigned port = _config.get<unsigned>("PizzaSlice.Database.port");
        
        if (mysql_real_connect(_mysql, host.c_str(), user.c_str(), password.c_str(), 
              db.c_str(), 3306, nullptr, CLIENT_MULTI_STATEMENTS) == nullptr) 
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

    std::pair<bool, MySQLConnection::QueryResults> MySQLConnection::executeQuery(const std::string& query_)
    {
        int status;
        if (mysql_real_query(_mysql, query_.c_str(), query_.size()))
        {
            return std::make_pair(false, QueryResults());
        }

        QueryResults queryResults;
        do
        {
            MYSQL_RES *result = mysql_store_result(_mysql);
            if(!result && 0 != mysql_field_count(_mysql))
            {
                mysql_free_result(result);
                return std::make_pair(false, QueryResults());
            }

            while (1)
            {
                if(result == nullptr) break;
                MYSQL_ROW row = mysql_fetch_row(result);
                unsigned long *lengths = mysql_fetch_lengths(result);

                if(row == nullptr) break;
                unsigned num_fields = mysql_num_fields(result);
                SingleQueryResult singleQueryRes;
                for(unsigned i = 0; i < num_fields; ++i)
                {
                    if(nullptr == row[i])
                        singleQueryRes.push_back(boost::none);
                    else
                        singleQueryRes.push_back(std::string(row[i], lengths[i]));
                }
                queryResults.push_back(singleQueryRes);
            }
            mysql_free_result(result);

            status = mysql_next_result(_mysql);
            if(status > 0)
            {
                return std::make_pair(false, QueryResults());
            }
        }
        while(status == 0);

        return std::make_pair(true, queryResults);
    }

    std::pair<bool, MySQLConnection::QueryResults> MySQLConnection::executeMultipleQueriesWithSingleResult(const std::string& query_)
    {
        int status;
        bool isSecondTime = false;

        if (mysql_real_query(_mysql, query_.c_str(), query_.size()))
        {
            return std::make_pair(false, QueryResults());
        }

        QueryResults queryResults;
        do
        {
            MYSQL_RES *result = mysql_store_result(_mysql);
            if(!result && 0 != mysql_field_count(_mysql))
            {
                mysql_free_result(result);
                return std::make_pair(false, QueryResults());
            }
            while (1)
            {
                if(result == nullptr)
                {
                    queryResults.push_back(SingleQueryResult());
                    break;
                }

                MYSQL_ROW row = mysql_fetch_row(result);
                unsigned long *lengths = mysql_fetch_lengths(result);

                if(row == nullptr) 
                {
                    if(isSecondTime)
                    {
                        queryResults.push_back(SingleQueryResult());
                        isSecondTime = false;
                    }

                    isSecondTime = true;
                    break;
                }
                isSecondTime = false; 
                unsigned num_fields = mysql_num_fields(result);

                SingleQueryResult singleQueryRes;
                for(unsigned i = 0; i < num_fields; ++i)
                {
                    if(nullptr == row[i])
                        singleQueryRes.push_back(boost::none);
                    else
                        singleQueryRes.push_back(std::string(row[i], lengths[i]));
                }
                queryResults.push_back(singleQueryRes);
            }
            mysql_free_result(result);

            status = mysql_next_result(_mysql);
            if(status > 0)
            {
                return std::make_pair(false, QueryResults());
            }
        }
        while(status == 0);

        return std::make_pair(true, queryResults);
    }
    
    std::pair<bool, std::string> MySQLConnection::addEscapeCharacters(const std::string& query_)
    {
        try
        {
            int len = query_.size();
            char chunk[2*len];
            int newLen = mysql_real_escape_string(_mysql, chunk, query_.c_str(), len);
            std::string newQuery = std::string(chunk, newLen);

            return std::make_pair(true, newQuery);
        }
        catch(std::exception& e)
        {
            //Better log here
            return std::make_pair(false, "");
        }

    }

    bool MySQLConnection::addExpense(PizzaExpense& pizzaExpense_)
    {
        
        std::stringstream queryStream;
        std::string type = (PizzaDailyRecords::Category::VEG == pizzaExpense_._type) ? "veg" : "non_veg";

        queryStream << "INSERT INTO `expense` (`type`,`date`,`expense`,`description`) VALUES ('"
                    << type 
                    << "', '"
                    << Utils::convertPtimeToString(pizzaExpense_._date)
                    << "',"
                    << pizzaExpense_._expense
                    << ", '"
                    << pizzaExpense_._description
                    << "');";
        
        std::string query = queryStream.str();
        std::pair<bool, QueryResults> res = executeQuery(query);
        
        if (!res.first) 
        {     
            //Error log
            std::cout << "Error found !!!" << std::endl;
            return false;
        }
    }

} //namespace Databse
} //namespace PizzaSlice

