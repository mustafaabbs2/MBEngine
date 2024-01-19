#include "solver.h"
#include <fstream>
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
		double coeff = 21.0 / (64.0 * pi * std::pow(h, 3));
		return coeff * std::pow(2.0 - q, 4) * (1 + 2 * q);
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
		p.vx += dt * p.fx / p.density;
		p.vy += dt * (p.fy / p.density - g);

		p.x += dt * p.vx;
		p.y += dt * p.vy;

		p.fx = 0.0;
		p.fy = 0.0;
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

double calculatePressure(const Particle& p)
{
	return c * c * rho0 * (std::pow(p.density / rho0, gamma) - 1.0) / gamma + p0;
}

void calculatePressureForce(std::vector<Particle>& particles)
{

	for(auto& p : particles)
	{
		double pressureForceX = 0.0, pressureForceY = 0.0;
		double pi = calculatePressure(p);
		double rhoi = p.density;

		for(const auto& other : particles)
		{
			if(&p != &other)
			{
				double r = distance(p, other);
				if(r > 0)
				{
					// double pressure = k * (p.density - rho0);
					// use tait equation of state
					double pj = calculatePressure(other);
					double rhoj = other.density;

					double w_press = wendlandKernel(r);

					pressureForceX += other.mass * (pi / (rhoi * rhoi) + pj / (rhoj * rhoj)) *
									  w_press * (p.x - other.x);

					pressureForceY += other.mass * (pi / (rhoi * rhoi) + pj / (rhoj * rhoj)) *
									  w_press * (p.y - other.y);
				}
			}
		}
		p.fx += pressureForceX;
		p.fy += pressureForceY;
	}
}

void writeParticleData(const std::vector<Particle>& particles, const std::string& filename)
{
	std::ofstream outfile(filename);

	if(outfile.is_open())
	{
		//header
		outfile << "X"
				<< " "
				<< "Y"
				<< " "
				<< "U"
				<< " "
				<< "V"
				<< " "
				<< "Fx"
				<< " "
				<< "Fy"
				<< " "
				<< "Rho"
				<< " "
				<< "Mass"
				<< "\n";
		for(const auto& particle : particles)
		{
			outfile << particle.x << " " << particle.y << " " << particle.vx << " " << particle.vy
					<< " " << particle.fx << " " << particle.fy << " " << particle.density << " "
					<< particle.mass << "\n";
		}
		outfile.close();
	}
	else
	{
		std::cerr << "Unable to open the file: " << filename << std::endl;
	}
}