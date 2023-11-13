#include "Color.hpp"
#include <iostream>

Color::Color() { }
Color::Color(double r, double g, double b)
	: r(r)
	, g(g)
	, b(b)
{ }

Color operator*(double x, const Color& other)
{
	return Color(x * other.r, x * other.g, x * other.b);
}

Color operator*(const Color& other, double x)
{
	return Color(x * other.r, x * other.g, x * other.b);
}
