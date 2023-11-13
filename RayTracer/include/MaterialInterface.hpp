#pragma once

#include "Ray.hpp"
#include "Color.hpp"


namespace Hit
{
	struct hit_record;
} // namespace Hit


//Abstract
class MaterialInterface {
public:
	virtual bool scatter(const Ray& ray, const Hit::hit_record& rec, Color& attenuation, Ray& scattered) const = 0;
};
