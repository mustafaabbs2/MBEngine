#pragma once

#include "Color.hpp"
#include <vector>

class WriterInterface
{
public:
	WriterInterface() { }
	virtual void WritePixelsToBuffer(const Color& pixel, const int samplesPerPixel) const = 0;
	virtual void WriteToFile() const = 0;
};