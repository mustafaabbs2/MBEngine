#include "solver.h"
#include <fstream>
#include <iostream>

void hello_world()
{
	std::cout << "Hello world\n";
}

// From https://www.cs.cmu.edu/~scoros/cs15467-s16/lectures/11-fluids2.pdf
// 315/64 pi h^3 (h2 - r2) ^3
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

// From https://www.gpusph.org/documentation/gpusph-theory.pdf

double wendlandGradient(double q) //gradient assumed same in both dirs
{
	if(q >= 0 && q <= 2)
	{
		double coeff = -(5 * 21.0) / (16.0 * pi * std::pow(h, 5));
		double factor = std::pow(1.0 - q / 2.0, 3) * q;
		return coeff * factor;
	}
	else
	{
		return 0.0;
	}
}

//need a gradient for pressure

double distance(const Particle& p1, const Particle& p2)
{
	return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

void runStep(std::vector<Particle>& particles)
{
	for(auto& p : particles)
	{
		//not sure?
		p.vx += dt * p.fx / p.density;
		p.vy += dt * (p.fy / p.density - g); //add gravity here

		p.x += dt * p.vx;
		p.y += dt * p.vy;

		//recalculate forces in the next step
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

double calculatePressureTait(const Particle& p)
{
	return c * c * rho0 * (std::pow(p.density / rho0, gamma) - 1.0) / gamma + p0;
}

double calculatePressureDefault(const Particle& p)
{
	return k * (p.density - rho0);
}

void calculatePressureForce(std::vector<Particle>& particles)
{

	for(auto& p : particles)
	{
		double pressureForceX = 0.0, pressureForceY = 0.0;
		double pi = calculatePressureTait(p);
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
					double pj = calculatePressureTait(other);
					double rhoj = other.density;

					double w_press = wendlandGradient(r); //is this correct?

					pressureForceX += other.mass * (pi / (rhoi * rhoi) + pj / (rhoj * rhoj)) *
									  w_press;

					pressureForceY += other.mass * (pi / (rhoi * rhoi) + pj / (rhoj * rhoj)) *
									  w_press;
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