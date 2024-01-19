#include "solver.h"
#include <iostream>
#include <random>

int main()
{
	const int numParticles = 1000;

	std::vector<Particle> particles(numParticles);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> distribution(0.0, 0.5);

	double offset = 0;

	size_t id = 0;

	for(auto& p : particles)
	{
		p.id = id;
		p.x = offset;
		p.y = distribution(gen);
		p.vx = 0.0;
		p.vy = 0.0;
		p.fx = 0.0;
		p.fy = 0.0;
		p.mass = 0.001 / 2000;
		p.density = rho0;

		offset += 0.01;
		id += 1;
	}

	for(int step = 0; step < 5; ++step)
	{
		runStep(particles);
		writeParticleData(particles, "particle_data_step_" + std::to_string(step) + ".txt");
	}

	return 0;
}