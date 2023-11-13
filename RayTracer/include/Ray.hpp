#pragma once
#include "Vec3.hpp"

class Ray {
public:
    Ray();
    Ray(const Vec3& origin, const Vec3& direction);
    const Vec3& getOrigin() const;
    const Vec3& getDirection() const;
    Vec3 pointAt(double t) const;
private:
    Vec3 origin, direction;

};