#include "Vec3.hpp"
#include "Ray.hpp"
#include "Utils.hpp"
#include "Hitter.hpp"
#include "MaterialInterface.hpp"

#include "Sphere.hpp"


Sphere::Sphere() {}
Sphere::Sphere(const Vec3& center, double radius, std::shared_ptr<MaterialInterface> matptr) : _sphereCenter(center), _sphereRadius(radius), _matptr(matptr) {}


//calculate the "t" for which A + tB hits the sphere
bool Sphere::hit(const Ray& ray, double tmin, double tmax, Hit::hit_record& rec) const {
    Vec3 oc = ray.getOrigin() - _sphereCenter;
    auto a = dot(ray.getDirection(), ray.getDirection());
    auto b = 2 * dot(oc, ray.getDirection());
    auto c = dot(oc, oc) - _sphereRadius * _sphereRadius;
    auto discriminant = b * b - 4 * a * c;

    if (discriminant < 0)  //no real solutions
        return false;

    auto sqrtd = std::sqrt(discriminant);
    auto root = (-b - sqrtd) / (2 * a);

    if (root < tmin || root > tmax)
    {
        root = (-b + sqrtd) / (2 * a);
        if (root < tmin || root > tmax)
            return false;
    }

    //if not returned yet, calculate t, p, normal for the hit
    rec.t = root;
    rec.p = ray.pointAt(rec.t);
    rec.normal = (rec.p - _sphereCenter) / _sphereRadius; //note: here, normals always
    //point outward from the surface. You need a face side later

    rec.matptr = _matptr;

    return true;
  }

