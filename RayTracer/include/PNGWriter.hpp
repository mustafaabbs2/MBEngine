#pragma once

#include "Utils.hpp"
#include "WriterInterface.hpp"
#include <fstream>
#include <memory>
#include <sstream>
#include <vector>
class PNGWriter : public WriterInterface

{
public:
	PNGWriter(std::string filename, const int width, const int height);
	void WritePixelsToBuffer(const Color& pixel, const int samplesPerPixel) const override;
	void WriteToFile() const override;

private:
	int _width, _height;
	std::string _filename;
	mutable std::ofstream _outfile;
	mutable std::vector<int> _buffer;
};
