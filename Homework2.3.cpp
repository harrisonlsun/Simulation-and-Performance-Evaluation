/**
 * Homework 2.3
 * EECE 5643 - Simulation and Performance Evaluation
 * Author: Harrison Sun
 * Email: sun.har@northeastern.edu
 */

#define ONEFACEWEIGHT	1
#define OTHERWEIGHT		2
#define SIXFACEWEIGHT	4
#define DEFAULTSEED		0L
#define NUMRUNS			1000000L

#include <iostream>
#include <stdlib.h>
#include "c_lib/rng.h"

/**
 * int main()
 * 
 ************* Terminal Arguments *************
 * @param int argc - number of arguments      *
 * @param char* argv[] - array of arguments   *
 **********************************************
 * 
 * @return int - 0 if successful
 * 
 * This is the main function. It uses a Monte Carlo Simulation to estimate the probability that, if weighted dice are rolled, the sum of the two up-faces will be 7.
 */

int main(int argc, char* argv[])
{
	/* Seed definition */
	long seed = (argc > 1) ? atol(argv[1]) : DEFAULTSEED;

	/* Number of runs */
	long num_runs = (argc > 2) ? atol(argv[2]) : NUMRUNS;
	
	/* Random Number Generator */
	PutSeed(seed);
	
	/* Dice Weights */
	double oneFaceWeight	{ ONEFACEWEIGHT		};
	double otherFaceWeight	{ OTHERWEIGHT		};
	double sixFaceWeight	{ SIXFACEWEIGHT		};
	
	/* TOTAL WEIGHT */
	double totalWeight		{ oneFaceWeight + sixFaceWeight + 4 * otherFaceWeight };

	/* Dice Probabilities */
	double p1 = oneFaceWeight / totalWeight;
	double pOther = otherFaceWeight / totalWeight;
	double p6 = sixFaceWeight / totalWeight;

	/* Define the thresholds */
	double threshold1		= p1;
	double threshold2		= threshold1 + pOther;
	double threshold3		= threshold2 + pOther;
	double threshold4		= threshold3 + pOther;
	double threshold5		= threshold4 + pOther;
	double threshold6		= threshold5 + p6;		/* threshold6 should be equal to 1 */
	
	/* Number of times the sum of the two up-faces is 7 */
	long num_7{ 0 };
	for (int i = 0; i < num_runs; ++i)
	{
		/* Roll the first die */
		double r = Random();
		int first_die{};
		if (r < threshold1)
		{
			first_die = 1;
		}
		else if (r < threshold2)
		{
			first_die = 2;
		}
		else if (r < threshold3)
		{
			first_die = 3;
		}
		else if (r < threshold4)
		{
			first_die = 4;
		}
		else if (r < threshold5)
		{
			first_die = 5;
		}
		else if (r < threshold6)
		{
			first_die = 6;
		}
		else
		{
			std::cout << "Error: Random number is greater than 1." << std::endl;
			return 1;
		}

		/* Roll the second die */
		r = Random();
		int second_die{};
		if (r < threshold1)
		{
			second_die = 1;
		}
		else if (r < threshold2)
		{
			second_die = 2;
		}
		else if (r < threshold3)
		{
			second_die = 3;
		}
		else if (r < threshold4)
		{
			second_die = 4;
		}
		else if (r < threshold5)
		{
			second_die = 5;
		}
		else if (r < threshold6)
		{
			second_die = 6;
		}
		else
		{
			std::cout << "Error: Random number is greater than 1." << std::endl;
			return 1;
		}

		/* Check if the sum of the two up-faces is 7 */
		if (first_die + second_die == 7)
		{
			++num_7;
		}
	}

	/* Print the results */
	std::cout << "The probability that the sum of the two up-faces is 7 is " << (double)num_7 / num_runs << std::endl;

	return 0;
}