#include "Lambertian.hpp"
#include "Hitter.hpp"

Lambertian::Lambertian(const Color& col)
	: _albedo(col){};

bool Lambertian::scatter(const Ray& ray,
						 const Hit::hit_record& rec,
						 Color& attenuation,
						 Ray& scattered) const
{
	auto scatterDirection = rec.normal + randomUnitVector();
	if(scatterDirection.almostZero())
		scatterDirection = rec.normal;

	scattered = Ray(rec.p, scatterDirection);

	attenuation = _albedo;
	return true;
}