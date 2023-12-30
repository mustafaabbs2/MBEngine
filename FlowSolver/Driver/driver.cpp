#include "Grid.hpp"
#include "LinearConvection.hpp"

#include <fstream>
#include <iostream>
#include <vector>

int main()
{
	// Create the solver object
	std::vector<double> result;
	Grid mesh(41, 0, 2, 2);
	LinearConvection solver(0.025, 1, mesh);
	solver.solveDiff(25);

	result = solver.getVector();

	std::ofstream output("result-flowsolver.txt");
	if(output.is_open())
	{
		for(auto val : result)
			output << val << " , ";
	}
	output.close();

	return 0;
}