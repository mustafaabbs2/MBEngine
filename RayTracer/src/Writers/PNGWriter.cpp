#include "PNGWriter.hpp"
#include <png.h>

PNGWriter::PNGWriter(std::string filename, const int width, const int height)
	: _filename(filename)
	, _width(width)
	, _height(height)
{ }

// Output the image in PPM format
void PNGWriter::WritePixelsToBuffer(const Color& pixel, const int samplesPerPixel) const
{
	auto r = pixel.r;
	auto g = pixel.g;
	auto b = pixel.b;

	auto scale = 1.0 / samplesPerPixel;
	r = std::sqrt(scale * r);
	g = std::sqrt(scale * g);
	b = std::sqrt(scale * b);
	////https://en.wikipedia.org/wiki/Gamma_correction

	auto r_p = static_cast<int>(256 * clamp(r, 0.0, 0.999));
	auto g_p = static_cast<int>(256 * clamp(g, 0.0, 0.999));
	auto b_p = static_cast<int>(256 * clamp(b, 0.0, 0.999));

	_buffer.push_back(r_p);
	_buffer.push_back(g_p);
	_buffer.push_back(b_p);

	//buffer is 250 250 250    230 230 230  230 230 220
}

static void write_png_file(const char* filename, int width, int height, int* buffer)
{
	FILE* fp;
	png_structp png_ptr = NULL;
	png_infop info_ptr = NULL;
	png_bytep row = NULL;

	// Open the file for writing
	fp = fopen(filename, "wb");
	if(!fp)
	{
		printf("Could not open file %s for writing", filename);
		return;
	}

	// Initialize the PNG structures
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if(!png_ptr)
	{
		printf("Could not create PNG write structure");
		fclose(fp);
		return;
	}

	info_ptr = png_create_info_struct(png_ptr);
	if(!info_ptr)
	{
		printf("Could not create PNG info structure");
		png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
		fclose(fp);
		return;
	}

	// Set up the PNG image dimensions
	png_set_IHDR(png_ptr,
				 info_ptr,
				 width,
				 height,
				 8,
				 PNG_COLOR_TYPE_RGB,
				 PNG_INTERLACE_NONE,
				 PNG_COMPRESSION_TYPE_BASE,
				 PNG_FILTER_TYPE_BASE);

	// Write the PNG header information
	png_init_io(png_ptr, fp);
	png_write_info(png_ptr, info_ptr);

	// Allocate memory for the image rows
	row = (png_bytep)malloc(3 * width * sizeof(png_byte));

	// Write the PNG image rows
	for(int y = 0; y < height; y++)
	{
		for(int x = 0; x < width; x++)
		{
			int index = (y * width + x) * 3; // calculate index of current pixel in the vector
			row[3 * x + 0] = buffer[index]; // Red
			row[3 * x + 1] = buffer[index + 1]; // Green
			row[3 * x + 2] = buffer[index + 2]; // Blue
		}
		png_write_row(png_ptr, row);
	}

	// Free the allocated memory and clean up
	png_write_end(png_ptr, NULL);
	png_destroy_write_struct(&png_ptr, &info_ptr);
	free(row);
	fclose(fp);
}

void PNGWriter::WriteToFile() const
{
	write_png_file(_filename.c_str(), _width, _height, _buffer.data());
}
