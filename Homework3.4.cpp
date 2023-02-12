#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <exception>
#include <iostream>
#include <math.h> 
#include <string>
#include "c_lib/rvgs.h"
#include "c_lib/rngs.h"

#define START         0.0              /* initial time                   */
#define STOP      20000.0              /* terminal (close the door) time */
//#define INFINITY   (10000.0 * STOP)    /* must be much larger than endtime  */
#define MAXQUEUE     6                 /* max. # of jobs in queue        */


double Min(double a, double c)
/* ------------------------------
 * return the smaller of a, b
 * ------------------------------
 */
{
    if (a < c)
        return (a);
    else
        return (c);
}

double GetArrival()
/* ---------------------------------------------
 * generate the next arrival time, with rate 1/2
 * ---------------------------------------------
 */
{
    static double arrival = START;

    SelectStream(0);
    arrival += Exponential(2.0);
    return (arrival);
}


double GetService(double lb, double ub)
/* --------------------------------------------
 * generate the next service time with rate 2/3
 * --------------------------------------------
 */
{
    SelectStream(1);
    return (Uniform(lb, ub));
}

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
                errorMessage.append(" is not a digit.");
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

int main(int argc, char* argv[])
{
    struct {
        double arrival;                 /* next arrival time                   */
        double completion;              /* next completion time                */
        double current;                 /* current time                        */
        double next;                    /* next (most imminent) event time     */
        double last;                    /* last arrival time                   */
    } t;
    struct {
        double node;                    /* time integrated number in the node  */
        double queue;                   /* time integrated number in the queue */
        double service;                 /* time integrated number in service   */
    } area = { 0.0, 0.0, 0.0 };
    long index = 0;                     /* used to count departed jobs         */
	long reject{};                      /* number of jobs rejected because of full queue */
    long number = 0;                    /* number in the node                  */
    double endtime{};
    int queuesize{};
    double lowerBound{};
    double upperBound{};
    // Set the seed
    for (int i = 0; i < argc; ++i)
    {
        if (*argv[i] == 's' && checkArg(argv[i + 1]))
        {
            PlantSeeds(std::stol(argv[i + 1]));
            break;
        }
        else
        {
            PlantSeeds(123456789);
        }
    }

    // Set the number of runs
    for (int i = 0; i < argc; ++i)
    {
        if (*argv[i] == 'r' && checkArg(argv[i + 1]))
        {
            endtime = std::stol(argv[i + 1]);
            break;
        }
        else
        {
            endtime = STOP;
        }
    }

    // Set the queue size
    for (int i = 0; i < argc; ++i)
    {
        if (*argv[i] == 'q' && checkArg(argv[i + 1]))
        {
            queuesize = std::stol(argv[i + 1]);
            break;
        }
        else
        {
            queuesize = MAXQUEUE;
        }
    }

    // Set the bounds for uniform distribution (service time)
    for (int i = 0; i < argc; ++i)
    {
        if (*argv[i] == 'u' && checkArg(argv[i + 1]) && checkArg(argv[i + 1]))
        {
			lowerBound = std::stol(argv[i + 1]);
			upperBound = std::stol(argv[i + 2]);
            break;
        }
        else
        {
			lowerBound = 1.0;
			upperBound = 2.0;
        }
    }
    t.current = START;           /* set the clock                         */
    t.arrival = GetArrival();    /* schedule the first arrival            */
    t.completion = INFINITY;        /* the first event can't be a completion */

    while ((t.arrival < endtime) || (number > 0)) {
        t.next = Min(t.arrival, t.completion);          /* next event time   */
        if (number > 0) {                               /* update integrals  */
            area.node += (t.next - t.current) * number;
            area.queue += (t.next - t.current) * (number - 1);
            area.service += (t.next - t.current);
        }
        t.current = t.next;                         /* advance the clock */

        if (t.current == t.arrival) {               /* process an arrival */
            if (number < queuesize)
            {
                number++;
                t.arrival = GetArrival();
                if (t.arrival > endtime) {
                    t.last = t.current;
                    t.arrival = INFINITY;
                }
                if (number == 1)
                    t.completion = t.current + GetService(lowerBound, upperBound);
            }
            else
            {
				reject++;
                t.arrival = GetArrival();
                if (t.arrival > endtime) {
                    t.last = t.current;
                    t.arrival = INFINITY;
                }
                if (number == 1)
                    t.completion = t.current + GetService(lowerBound, upperBound);
            }
        }

        else {                                        /* process a completion */
            index++;
            number--;
            if (number > 0)
                t.completion = t.current + GetService(lowerBound, upperBound);
            else
                t.completion = INFINITY;
        }
    }

    printf("\nfor %ld jobs\n", index);
    printf("   average interarrival time = %6.2f\n", t.last / index);
    printf("   average wait ............ = %6.2f\n", area.node / index);
    printf("   average delay ........... = %6.2f\n", area.queue / index);
    printf("   average service time .... = %6.2f\n", area.service / index);
    printf("   average # in the node ... = %6.2f\n", area.node / t.current);
    printf("   average # in the queue .. = %6.2f\n", area.queue / t.current);
	printf("   number of rejections..... = %6.2ld\n", reject);
	printf("   percent of rejections.... = %6.2f\n", ((double)reject / (index+reject)) * 100);
    printf("   utilization ............. = %6.2f\n", area.service / t.current);

    return (0);
}
