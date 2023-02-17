/**
 * Homework 3.3
 * EECE 5643 - Simulation and Performance Evaluation
 * Author: Harrison Sun
 * Email: sun.har@northeastern.edu
 */

#define DEFAULT_BETA 0.9	    // default value for beta
#define DEFAULT_RUNS 100000L    // default value for number of runs

#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <exception>
#include <iostream>
#include <math.h> 
#include <string>
#include <vector>
#include "c_lib/rng.h"

/**
 * bool checkArg()
 *
 * @param char* input - the input string literal from the console
 * @return bool - true if the input is a number, false otherwise
 *
 * This function determines whether the argument is a number.
 */

bool checkArg(char* input)
{
    try
    {
        if (strlen(input) > 9)
        {
            throw std::logic_error("Number is too large.");
        }

        for (int i = 0; i < strlen(input); ++i)
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

/**
 * int main()
 * 
 * @param int argc - the number of arguments
 * @param char* argv[] - the arguments
 * 
 * @return int - returns 0 if the program runs successfully
 */

int main(int argc, char* argv[])
{
    long numRuns{};
    long Beta{};
	std::vector<int> feedback;
    
    // Set the seed
    for (int i = 0; i < argc; ++i)
    {
        if (*argv[i] == 's' && checkArg(argv[i + 1]))
        {
            PutSeed(std::stol(argv[i + 1]));
            break;
        }
        else
        {
            PutSeed(123456789);
        }
    }

    // Set the number of runs
    for (int i = 0; i < argc; ++i)
    {
        if (*argv[i] == 'r' && checkArg(argv[i + 1]))
        {
            numRuns = std::stol(argv[i + 1]);
            break;
        }
        else
        {
            numRuns = DEFAULT_RUNS;
        }
    }

    // Set the probability of feedback
    for (int i = 0; i < argc; ++i)
    {
        if (*argv[i] == 'B' && checkArg(argv[i + 1]))
        {
            Beta = std::stol(argv[i + 1]);
            break;
        }
        else
        {
            Beta = DEFAULT_BETA;
        }
    }
    
    for (int i = 0; i < numRuns; ++i)
    {
        int numFeedback{ 0 };
        double random = Random();
        /* Test if feedback */
        while (random > Beta)
        {
            numFeedback++;
            random = Random();
        }
		if (numFeedback < feedback.size())
            feedback[numFeedback]++;
        else
        {
			feedback.resize(numFeedback + 1);
			feedback[numFeedback]++;
        }
    }
    std::cout << feedback.size() << std::endl;
    for (int i = 0; i < feedback.size(); ++i)
    {
		feedback[i] /= numRuns;
		std::cout << "Probability of " << i << " feedbacks: " << feedback[i] << std::endl;
    }
      
	return 0;
}