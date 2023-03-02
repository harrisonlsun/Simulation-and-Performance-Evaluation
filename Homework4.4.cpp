/**
 * Harrison Sun (sun.har@northeastern.edu)
 * EECE 5643 - Simulation and Performance Evaluation
 * Homework 4.4
 */

#define DEFAULT_IFILE		"ac.dat"
#define DEFAULT_OFILE		"output.txt"

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <exception>
#include <iostream>
#include <list>
#include <math.h> 
#include <string>
#include <vector>
#include "c_lib/rvgs.h"
#include "c_lib/rngs.h"
#include "checkarg/checkarg.h"

/**
 * int main() - The main function
 *
 * @param int argc - the number of arguments
 * @param char* argv[] - the arguments
 *
 * @return 0 if the program runs successfully
 * 
 * This is the main function. It reads in a data file in tab separated format. The first column contains the arrival times and the second column
 * contains departure times.
 * 
 */

int main(int argc, char* argv[])
{
	// Create two vectors to store the data
	std::vector<double> arrival_times{};
	std::vector<double> departure_times{};
	std::vector<double> service_times{};

	// Histogram Parameters
	int nHistogram { 500 }; // The number of jobs in the data file
	// The number of bins in the histogram. Ideally, k ~ [ln(n), sqrt(n)] => Choosing from k ~ [6, 22]
	
	/*****************************************************************************************************************************************************************

		The number of bins is chosen to be 15. This is significantly larger than the minimum k = 6. The reason for this choice is that the service times are empirical 
		data and may have significant outliers that would not fit well with other data when given too few bins. However, 22 bins would be too many, as the data has
		high variance and would thus have a lot of empty bins. 15 bins is a good compromise between the two.
		
	*****************************************************************************************************************************************************************/
	
	int nBins{15};
	
	// File names
	std::string inputFileName{};
	std::string outputFileName{};

	// Set the input file stream
	for (int i = 0; i < argc; ++i)
	{
		if (*argv[i] == 'i')
		{
			inputFileName = argv[i + 1];
			break;
		}
		else
		{
			inputFileName = DEFAULT_IFILE;
		}
	}
	
	// Set the output file stream
	for (int i = 0; i < argc; ++i)
	{
		if (*argv[i] == 'o')
		{
			outputFileName = argv[i + 1];
			break;
		}
		else
		{
			outputFileName = DEFAULT_OFILE;
		}
	}
	
	double arrival_time{};
	double departure_time{};
	
	std::ifstream infile;
	infile.open(inputFileName.c_str());
	
	// Read in the data from the tsv to the vectors
	while (infile >> arrival_time >> departure_time)
	{
		arrival_times.push_back(arrival_time);
		departure_times.push_back(departure_time);
	}
	infile.close();
	
	// Calculate the service times and store them in the service_times vector
	for (int i = 0; i < arrival_times.size(); ++i)
	{
		// Check if the service node is free at arrival
		if (arrival_times[i] > departure_times[i - 1])
		{
			service_times.push_back(departure_times[i] - arrival_times[i]);
		}
		// If the job has to wait in a queue, the service starts after the previous job is finished
		else
		{
			service_times.push_back(departure_times[i] - departure_times[i - 1]);
		}
	}

	// Calculate the total service time
	double total_service_time{};
	for (std::vector<double>::iterator i = service_times.begin(); i != service_times.end(); ++i)
	{
		total_service_time += *i;
	}
	
	// Calculate the sample mean and standard deviation
	double sample_mean{ total_service_time / service_times.size() };
	double sample_std{};
	
	// Standard Deviation
	for (std::vector<double>::iterator i = service_times.begin(); i != service_times.end(); ++i)
	{
		sample_std += pow(*i - sample_mean, 2);
	}
	sample_std = sqrt(sample_std / (service_times.size() - 1));

	// Bin the data into nBins bins
	double max_service_time = *std::max_element(service_times.begin(), service_times.end());
	double min_service_time = *std::min_element(service_times.begin(), service_times.end());
	
	// Calculate the bin width
	double bin_width = (max_service_time - min_service_time) / nBins;

	// Put the data in the bins
	for (std::vector<double>::iterator i = service_times.begin(); i != service_times.end(); ++i)
	{
		// Find the bin that the data point belongs to
		for (int j = 0; j < nBins; ++j)
		{
			if (*i >= (double) j * bin_width && *i < (double) (j + 1) * bin_width)
			{
				*i = j;
				break;
			}
		}
	}
	
	// Output the binned histogram data to a file
	std::ofstream outfile;
	outfile.open(outputFileName.c_str());
	
	// Output the data as a histogram
	for (std::vector<double>::iterator i = service_times.begin(); i != service_times.end() + 1; ++i)
	{
		outfile << *i << ", " << (double) std::count(service_times.begin(), service_times.end(), *i) / service_times.size() << std::endl;
	}
	outfile.close();
	
	// Calculate the histogram mean and standard deviation
	double histogram_mean{};
	double histogram_std{};
	
	for (int i = 0; i < nBins; ++i)
	{
		histogram_mean += i * std::count(service_times.begin(), service_times.end(), i);
	}
	histogram_mean = histogram_mean / service_times.size();

	for (int i = 0; i < nBins; ++i)
	{
		histogram_std += pow(i - histogram_mean, 2) * std::count(service_times.begin(), service_times.end(), i);
	}
	histogram_std = sqrt(histogram_std / (service_times.size() - 1));
	
	// Output the means and standard deviations
	std::cout << "The sample mean: " << sample_mean << " and sample standard deviation: " << sample_std << std::endl;
	std::cout << "The histogram mean: " << histogram_mean << " and histogram standard deviation: " << histogram_std << std::endl;
	return 0;
}