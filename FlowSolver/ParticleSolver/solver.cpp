#include "solver.h"
#include <iostream>

void hello_world()
{
	std::cout << "Hello world\n";
}

double poly6Kernel(double r)
{
	if(r >= 0 && r <= h)
	{
		double coeff = 315.0 / (64.0 * pi * std::pow(h, 9));
		return coeff * std::pow(h * h - r * r, 3);
	}
	else
	{
		return 0.0;
	}
}

double wendlandKernel(double q) //q = x/h
{
	if(q >= 0 && q <= 2)
	{
		double coeff = 21.0 / (16.0 * pi * std::pow(h, 3));
		return coeff * std::pow(1.0 - 0.5 * q, 4) * (1 + 2 * 0.5 * q);
	}
	else
	{
		return 0.0;
	}
}

double spikyGradient(double r)
{
	if(r >= 0 && r <= h)
	{
		double coeff = -45.0 / (pi * std::pow(h, 6));
		return coeff * std::pow(h - r, 2);
	}
	else
	{
		return 0.0;
	}
}

double distance(const Particle& p1, const Particle& p2)
{
	return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

void runStep(std::vector<Particle>& particles)
{
	for(auto& p : particles)
	{
		// Update velocity
		p.vx += dt * p.fx / p.density;
		p.vy += dt * (p.fy / p.density - g);

		// Update position
		p.x += dt * p.vx;
		p.y += dt * p.vy;

		// Reset forces for the next iteration
		p.fx = 0.0;
		p.fy = 0.0;
        
		p.mass = 0.001 / 2000;
	}

	// Calculate density and pressure forces
	for(auto& p : particles)
	{
		p.density = calculateDensity(particles, p);
	}

	calculatePressureForce(particles);
}

double calculateDensity(const std::vector<Particle>& particles, const Particle& p)
{
	double density = 0.0;
	for(const auto& other : particles)
	{
		double r = distance(p, other);
		density += other.mass * wendlandKernel(r);
	}
	return density;
}

void calculatePressureForce(std::vector<Particle>& particles)
{
	for(auto& p : particles)
	{
		double pressureForceX = 0.0, pressureForceY = 0.0;
		for(const auto& other : particles)
		{
			if(&p != &other)
			{
				double r = distance(p, other);
				double pressure = k * (p.density - rho0);
				pressureForceX += -pressure * spikyGradient(r) * (p.x - other.x) / r;
				pressureForceY += -pressure * spikyGradient(r) * (p.y - other.y) / r;
			}
		}
		p.fx += pressureForceX;
		p.fy += pressureForceY;
	}
}