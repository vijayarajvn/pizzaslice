#include <iostream>
#include <sstream>
#include "CommandLine.h"

int main()
{
    std::stringstream menu;
    menu << "Select one of the options:" << std::endl
         << "1. Change mess manager" << std::endl
         << "2. Expenses" << std::endl
         << "3. Daily Records" << std::endl;

    PizzaSlice::CommandLine::out(menu);    
    unsigned option = PizzaSlice::CommandLine::in<unsigned>("Choice: ");

    return 0;
}
