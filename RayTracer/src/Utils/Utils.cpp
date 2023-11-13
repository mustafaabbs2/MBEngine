
#include "Utils.hpp"
#include <random>

// Returns a random real in [0,1).
double random_double()
{
	static std::uniform_real_distribution<double> distribution(0.0, 1.0);
	static std::mt19937 generator;
	return distribution(generator);
}

// Returns a random real in [min,max).
double random_double(double min, double max)
{
	static std::uniform_real_distribution<double> distribution(min, max);
	static std::mt19937 generator;
	return distribution(generator);
}

// Utility function to clamp a value between a minimum and maximum
double clamp(double value, double min, double max)
{
	return std::fmax(min, std::fmin(value, max));
}

// Utility function to compute the dot product of two vectors
double dot(const Vec3& v, const Vec3& n)
{
	return v.x * n.x + v.y * n.y + v.z * n.z;
}

// Utility function to compute the cross product of two vectors
Vec3 cross(const Vec3& a, const Vec3& b)
{
	return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

// Utility function to compute the reflect direction of a vector given a surface normal
Vec3 reflect(const Vec3& v, const Vec3& n)
{
	return v - n * 2 * dot(v, n);
}

Color rayColor(const Ray& ray, const HitterList& world, int depth)
{

	Hit::hit_record rec;

	if(depth <= 0)
		return Color(0, 0, 0);

	if(world.hit(ray, 0.001, infinity, rec))
	{
		Ray scattered;
		Color attenuation;
		if(rec.matptr->scatter(ray, rec, attenuation, scattered))
			return attenuation * rayColor(scattered, world, depth - 1);

		Vec3 target = rec.p + rec.normal + randomUnitVector();
		return 0.5 * rayColor(Ray(rec.p, target - rec.p), world, depth - 1); //absorb half
	}
	//background
	{
		auto unitDirection = ray.getDirection().normalize();
		auto t = 0.5 * (unitDirection.y + 1.0);
		return (1.0 - t) * Color(1.0, 1.0, 1.0) +
			   t * Color(0.5, 0.7, 1.0); //gradient from white to blue
	}
}

void addRayColor(double x,
				 double y,
				 Color& cumulativeColor, //Should you do this?
				 Camera cam,
				 const HitterList& world,
				 const int maxDepth)
{
	//parallelize this call...
	cumulativeColor = cumulativeColor + rayColor(cam.getRay(x, y), world, maxDepth);
}