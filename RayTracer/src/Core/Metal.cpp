#include "Metal.hpp"
#include "Hitter.hpp"
#include "Utils.hpp"

Metal::Metal(const Color& col)
	: _albedo(col){};

bool Metal::scatter(const Ray& ray,
					const Hit::hit_record& rec,
					Color& attenuation,
					Ray& scattered) const
{
	auto reflectedDirection = reflect(ray.getDirection(), rec.normal);
	scattered = Ray(rec.p, reflectedDirection);
	attenuation = _albedo;

	return (dot(scattered.getDirection(), rec.normal));
}