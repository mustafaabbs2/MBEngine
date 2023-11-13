
#include "Vec3.hpp"

Vec3::Vec3() { }
Vec3::Vec3(double x, double y, double z)
	: x(x)
	, y(y)
	, z(z)
{ }

Vec3 Vec3::operator+(const Vec3& v) const
{
	return Vec3(x + v.x, y + v.y, z + v.z);
}

Vec3 Vec3::operator-(const Vec3& v) const
{
	return Vec3(x - v.x, y - v.y, z - v.z);
}

Vec3 Vec3::operator/(double s) const
{
	return Vec3(x / s, y / s, z / s);
}

double Vec3::dot(const Vec3& v) const
{
	return x * v.x + y * v.y + z * v.z;
}

Vec3 Vec3::cross(const Vec3& v) const
{
	return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

inline double Vec3::length() const
{
	return std::sqrt(x * x + y * y + z * z);
}

double Vec3::lengthSquared() const
{
	return (x * x + y * y + z * z);
}

Vec3 Vec3::normalize() const
{ //use it to make a unit vector
	double len = length();
	return Vec3(x / len, y / len, z / len);
}

bool Vec3::almostZero() const
{
	const auto tol = 1e-8;

	if((fabs(x) < tol) && (fabs(y) < tol) && (fabs(z) < tol))
		return true;
	
	return false; 
}

//note: type qualifiers aren't allowed on static functions since they don't access the this pointer of a class
//i.e. static functions cannot have a const or volatile type qualifier
Vec3 Vec3::random()
{
	return Vec3(random_double(), random_double(), random_double());
}

Vec3 Vec3::random(double min, double max)
{
	return Vec3(random_double(min, max), random_double(min, max), random_double(min, max));
}

//define binary operators outside to allow dual sided operations
Vec3 operator*(double s, const Vec3& other)
{
	return Vec3(other.x * s, other.y * s, other.z * s);
}

Vec3 operator*(const Vec3& other, double s)
{
	return Vec3(other.x * s, other.y * s, other.z * s);
}

Vec3 randomInUnitSphere()
{
	while(true)
	{
		auto p = Vec3::random(-1, 1);
		if(p.lengthSquared() >= 1)
			continue;
		return p;
	}
}

Vec3 randomInHemishphere(const Vec3& normal)
{
	Vec3 inUnitSphere = randomInUnitSphere();
	if(inUnitSphere.dot(normal) > 0.0)
		return inUnitSphere;
	else
		return -1 * inUnitSphere;
}

Vec3 randomUnitVector()
{
	return randomInUnitSphere().normalize();
}
