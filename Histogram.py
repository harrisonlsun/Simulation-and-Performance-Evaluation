# Harrison Sun (sun.har@northeastern.edu)
# EECE 5643 - Simulation and Performance Evaluation

# This python script generates a bar chart taking in csv inputs. The first column is the x axis value and the second column is the y axis value.

import numpy as np
import matplotlib.pyplot as plt
import sys

# Read in the csv file
data = np.genfromtxt(sys.argv[1], delimiter=',')

# Plot the bar chart
plt.bar(data[:,0], data[:,1], align='center', alpha=0.5)
plt.xlabel('x')
plt.ylabel('f(x)')
plt.xticks(data[:,0])

# Save the bar chart
plt.savefig(sys.argv[2])
