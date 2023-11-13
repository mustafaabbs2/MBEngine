#pragma once

#include <cmath>

double random_double();
double random_double(double min, double max);

// Define a 3D vector class
class Vec3
{
public:
	double x, y, z;

	Vec3();
	Vec3(double x, double y, double z);

	Vec3 operator+(const Vec3& v) const;
	Vec3 operator-(const Vec3& v) const;
	Vec3 operator/(double s) const;
	double dot(const Vec3& v) const;
	Vec3 cross(const Vec3& v) const;
	inline double length() const;
	double lengthSquared() const;
	Vec3 normalize() const;
	bool almostZero() const;
	//note: type qualifiers aren't allowed on static functions since they don't access the this pointer of a class
	//i.e. static functions cannot have a const or volatile type qualifier
	static Vec3 random();
	static Vec3 random(double min, double max);
};

//Utility functions for Vec3
//should be in a namespace
Vec3 operator*(double s, const Vec3& other);
Vec3 operator*(const Vec3& other, double s);
Vec3 randomInUnitSphere();
Vec3 randomInHemishphere(const Vec3& normal);
Vec3 randomUnitVector();
