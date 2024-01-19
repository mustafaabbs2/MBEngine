#include "solver.h"
#include <iostream>

int main()
{
	// Number of particles
	const int numParticles = 1000;

	// Initialize particles
	std::vector<Particle> particles(numParticles);
	for(auto& p : particles)
	{
		p.x = 0.0;
		p.y = 0.0;
		p.vx = 0.0;
		p.vy = 0.0;
		p.fx = 0.0;
		p.fy = 0.0;
		p.mass = 0.01;
		p.density = rho0;
	}

	// Main simulation loop
	for(int step = 0; step < 10; ++step)
	{
		runStep(particles);
	}

	return 0;
}