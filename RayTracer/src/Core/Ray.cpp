#include "Ray.hpp"
#include "Vec3.hpp"

Ray::Ray() {}
Ray::Ray(const Vec3& origin, const Vec3& direction)
	: origin(origin)
	, direction(direction)
{}

const Vec3& Ray::getOrigin() const
{
	return origin;
}

const Vec3& Ray::getDirection() const
{
	return direction;
}

Vec3 Ray::pointAt(double t) const
{
	return origin + direction * t;
}
