#include "Hitter.hpp"
#include "HitterList.hpp"
#include <memory>
#include <vector>

HitterList::HitterList() {}
HitterList::HitterList(std::shared_ptr<Hitter> object)
{
	add(object);
}

void HitterList::add(std::shared_ptr<Hitter> object)
{
	objects.push_back(object);
}

void HitterList::clear()
{
	objects.clear();
}

bool HitterList::hit(const Ray& ray, double tmin, double tmax, Hit::hit_record& rec) const
{

	bool hitAnything = false;
	auto closestT = tmax;
	Hit::hit_record temp_rec;

	for(const auto& object : objects)
	{

		if(object->hit(
			   ray,
			   tmin,
			   closestT,
			   temp_rec)) //need temp_rec since this may not need to be filled to our final rec unless filled
		{
			hitAnything = true;
			closestT = temp_rec.t;
			rec = temp_rec;
		}
	}

	return hitAnything;
}