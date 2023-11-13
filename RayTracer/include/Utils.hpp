#pragma once
#include "Color.hpp"
#include "Constants.hpp"
#include "HitterList.hpp"
#include "Ray.hpp"
#include "Camera.hpp" 
#include "Vec3.hpp"

// Utility function to clamp a value between a minimum and maximum
double clamp(double value, double min, double max);

// Utility function to compute the dot product of two vectors
double dot(const Vec3& v, const Vec3& n);

// Utility function to compute the cross product of two vectors
Vec3 cross(const Vec3& a, const Vec3& b);

// Utility function to compute the reflect direction of a vector given a surface normal
Vec3 reflect(const Vec3& v, const Vec3& n);

Color rayColor(const Ray& ray, const HitterList& world, int depth);

void addRayColor(double x,
				 double y,
				 Color& cumulativeColor,
				 Camera cam,
				 const HitterList& world,
				 const int maxDepth);