#ifndef PIZZASLICE_COMMANDLINE_H
#define PIZZASLICE_COMMANDLINE_H

#include <iostream>
#include <string>

namespace PizzaSlice { namespace CommandLine 
{

    /* 
       This function displays message_ and read from command_line and
       return the value
    */

    void out(const std::stringstream& stringstream_)
    {
        std::cout << stringstream_.rdbuf();
    }

    void out(const std::string& message_)
    {
        std::cout << message_;
    }

    template<typename Type>
    Type in(const std::string& message_)
    {
        std::cout << message_;

        Type input;
        std::cin >> input;
        return input;
    }

}}
#endif
