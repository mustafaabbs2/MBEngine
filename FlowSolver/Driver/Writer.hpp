#pragma once

#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
//File format

/*
Time 0.5

x y z <fieldname>
0 0 0  0.0
0 0.1 0.1 0.021
.
.


*/
class Writer
{
public:
	Writer() {}
	void writeBinary(std::vector<double> data)
	{
		std::ofstream outputFile("data.bin", std::ios::binary); // Open the file in binary mode

		if(!outputFile.is_open())
		{
			return;
		}

		// Write the data to the file
		outputFile.write(reinterpret_cast<char*>(&data), sizeof(data));
		outputFile.close(); // Close the file
	}

	void writeASCII(const std::vector<double>& data, size_t timestep)
	{
		std::string baseFile = "field";
		std::ofstream outputFile(baseFile + std::to_string(timestep) + ".txt"); // Open the file for writing

		if(!outputFile.is_open())
		{
			return;
		}
		// Write the header line
		outputFile << "Time = " << timestep << std::endl;

		// Write the column names
		outputFile << "x y z vel" << std::endl;

		// Write the coordinate data and values
		outputFile << std::fixed
				   << std::setprecision(6); // Set the precision of floating-point values

		for(auto& val : data)
			outputFile << "0.0 0.0 0.0 " << val << std::endl;

		outputFile.close(); // Close the file
	}
};