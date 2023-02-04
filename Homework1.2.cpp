/**
 * Homework 1.2 
 * EECE 5643 - Simulation and Performance Evaluation
 * Author: Harrison Sun
 * Email: sun.har@northeastern.edu
 */

#include <iostream>
#include <vector>
#include <fstream>

/**
 * int main()
 * This is the main function. It reads in an ac.dat data file in tab separated format. The first column contains the arrival times and the second column
 * contains departure times. This function calculates the average service time, the server utilization, and the traffic intensity.  
 */

int main(int argc, char* argv[])
{
    /* Read in the ac.dat file and store the arrival times and departure times as two vectors. */
    std::vector<double> arrival_times {};
    std::vector<double> departure_times {};
    std::ifstream infile("ac.dat");
    double arrival_time {};
    double departure_time {};
    while (infile >> arrival_time >> departure_time)
    {
        arrival_times.push_back(arrival_time);
        departure_times.push_back(departure_time);
    }

    /* Calculate the service time as departure time minus the start time of the job. */
    double total_service_time {};
    for (int i = 0; i < arrival_times.size(); i++)
    {
        /* Check if the service node is free at arrival */
        if (arrival_times[i] > departure_times[i-1])
        {
            total_service_time += (departure_times[i] - arrival_times[i]);
        }
        /* If the job has to wait in a queue, the service starts after the previous job is finished */
        else
        {
            total_service_time += (departure_times[i] - departure_times[i-1]);
        }
    }

    /* Calculate the average service time */
    double average_service_time = total_service_time / arrival_times.size();

    /* Print the average service time */
    std::cout << "The average service time is: " << average_service_time << std::endl;

    /* Calculate the server utilization */
    /* Cycle through both vectors and use the lesser value as the next time point. */
    double server_utilization {};
    int i {0};
    int j {0};
    while (i < arrival_times.size() && j < departure_times.size())
    {
        if (arrival_times[i] < departure_times[j])
        {
            server_utilization += (departure_times[j] - arrival_times[i]);
            i++;
        }
        else
        {
            server_utilization += (departure_times[j] - departure_times[j-1]);
            j++;
        }
    }
    /* Divide the server utilization by the total amount of time the program is run. */
    server_utilization /= departure_times[departure_times.size()-1];
    /* Print the server utilization time. */
    std::cout << "The server utilization is: " << server_utilization << std::endl;
}