/**
* bool checkArg()
*
* @param char* input - the input string literal from the console
* @return bool - true if the input is a number, false otherwise
*
* This function determines whether the argument is a number.
*/

#include <cstdlib>
#include <cstring>
#include <exception>
#include <iostream>
#include <string>
#include <stdexcept>
#include "checkarg.h"

bool checkArg(char* input)
{
    try
    {
        if (strlen(input) > 9)
        {
            throw std::logic_error("Number is too large.");
        }

        for (int i = 0; i < (int) strlen(input); ++i)
        {

            if (std::isdigit(input[i]) || (input[i] == '.')) continue;
            else
            {
                std::string errorMessage;
                errorMessage.append((std::string)input);
                errorMessage.append(" is not a number.");
                throw std::logic_error(errorMessage);
            }
        }
        return 1;
    }

    catch (const std::logic_error& error)
    {
        std::cerr << error.what() << std::endl;
        return 0;
    }
}