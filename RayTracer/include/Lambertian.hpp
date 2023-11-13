#pragma once

#include "MaterialInterface.hpp"

class Lambertian : public MaterialInterface
{
public:
	Lambertian(const Color& col);
	virtual bool scatter(const Ray& ray,
						 const Hit::hit_record& rec,
						 Color& attenuation,
						 Ray& scattered) const override;

private:
	Color _albedo; //diffuse reflectivity
};