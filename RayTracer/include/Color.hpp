#pragma once
#include <iostream>

// Define a color class with red, green, and blue components

class Color
{
public:
	double r, g, b;
	Color();
	Color(double r, double g, double b);

	inline Color operator*(double scalar)
	{
		return Color(r * scalar, g * scalar, b * scalar);
	}

	inline Color operator*(const Color& other) const
	{
		return Color(r * other.r, g * other.g, b * other.b);
	}

	inline Color operator+(const Color& other) const
	{
		return Color(r + other.r, g + other.g, b + other.b);
	}
};

Color operator*(double x, const Color& other);
Color operator*(const Color& other, double x);
