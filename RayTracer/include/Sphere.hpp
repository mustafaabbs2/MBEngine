#pragma once

//Have a Sphere derived


#include "Vec3.hpp"
#include "Ray.hpp"
#include "Utils.hpp"
#include "Hitter.hpp"
#include "MaterialInterface.hpp"


class Sphere : public Hitter {

public:
    Vec3 _sphereCenter;
    double _sphereRadius;
    std::shared_ptr<MaterialInterface> _matptr;

    Sphere();
    Sphere(const Vec3& center, double radius, std::shared_ptr<MaterialInterface> matptr);
    virtual bool hit(const Ray& ray, double tmin, double tmax, Hit::hit_record& rec) const override;
};


