#include "solver.h"
#include <iostream>
#include <random>

int main()
{
	const int numParticles = 10;

	std::vector<Particle> particles(numParticles);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> distribution(0.0, 0.5);

	for(auto& p : particles)
	{
		p.x = distribution(gen);
		p.y = distribution(gen);
		p.vx = 0.0;
		p.vy = 0.0;
		p.fx = 0.0;
		p.fy = 0.0;
		p.mass = 0.001 / 2000;
		p.density = rho0;
	}

	for(int step = 0; step < 2; ++step)
	{
		runStep(particles);
	}

	writeParticleData(particles, "particle_data.txt");

	return 0;
}