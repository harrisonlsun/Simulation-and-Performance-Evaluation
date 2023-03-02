import sys
import pandas as pd
import matplotlib.pyplot as plt

# Get the input and output file names from the command-line arguments
input_file = sys.argv[1]
output_file = sys.argv[2]

# Read the data from the CSV file
data = pd.read_csv(input_file, header=None)

# Filter out the rows with 0 values
data = data[data[0] != 0]

# Create the step histogram
plt.hist(data[0], bins=data[0].nunique(), weights=data[1], histtype='step')

# Set the x-axis label
plt.xlabel('Values')

# Set the y-axis label
plt.ylabel('Frequency')

# Set the x-axis tick labels
plt.xticks(data[0])

# Rotate x labels
plt.xticks(rotation=90)

# Save the plot to a PNG file
plt.savefig(output_file)

