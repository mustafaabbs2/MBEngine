#pragma once

#include "Hitter.hpp"
#include <memory>
#include <vector>

//List of hitter objects
class HitterList : public Hitter
{

public:
	HitterList();
	HitterList(std::shared_ptr<Hitter> object);

	void add(std::shared_ptr<Hitter> object);
	void clear();
	bool hit(const Ray& ray, double tmin, double tmax, Hit::hit_record& rec) const override;

private:
	std::vector<std::shared_ptr<Hitter>> objects;
};
