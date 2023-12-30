#pragma once
#include <utility>

class Grid
{
public:
	int nx_, ny_;
	double xlen_, ylen_;

	Grid(int nx, int ny, double xlen, double ylen)
		: nx_(nx)
		, ny_(ny)
		, xlen_(xlen)
		, ylen_(ylen)
	{}

	std::pair<double, double> getGridSize()
	{
		return std::make_pair(xlen_ / (nx_ - 1), ylen_ / (ny_ - 1));
	}
};