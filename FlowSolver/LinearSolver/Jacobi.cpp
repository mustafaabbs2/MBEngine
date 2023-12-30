#include <cmath>
#include <iostream>
#include <omp.h>
#include <vector>

// Function to perform Jacobi iteration
void jacobiIteration(const std::vector<double>& A,
					 const std::vector<double>& b,
					 std::vector<double>& x,
					 std::vector<double>& result,
					 int numRows,
					 int numCols)
{
#pragma omp parallel for
	for(int i = 0; i < numRows; ++i)
	{
		double sum = 0.0;
		for(int j = 0; j < numCols; ++j)
		{
			if(i != j)
			{
				sum += A[i * numCols + j] * x[j];
			}
		}
		result[i] = (b[i] - sum) / A[i * numCols + i];
	}
}

int main()
{
	// Define matrix and vector dimensions
	const int numRows = 4;
	const int numCols = 4;

	// Initialize matrix A and vector b (for simplicity, assume a diagonally dominant matrix)
	std::vector<double> A = {4, -1, 0, 0, -1, 4, -1, 0, 0, -1, 4, -1, 0, 0, -1, 4};
	std::vector<double> b = {15, 10, 10, 10};
	std::vector<double> x(numRows, 0.0);
	std::vector<double> result(numRows, 0.0);

	// Perform Jacobi iterations
	const int maxIterations = 100;
	for(int iteration = 0; iteration < maxIterations; ++iteration)
	{
		jacobiIteration(A, b, x, result, numRows, numCols);

		// Update x for the next iteration
		x = result;
	}

	// Print the final solution
	std::cout << "Final solution x: ";
	for(const auto& value : result)
	{
		std::cout << value << " ";
	}
	std::cout << std::endl;

	return 0;
}
