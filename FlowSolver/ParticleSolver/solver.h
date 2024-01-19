#pragma once

#include <cmath>
#include <vector>

struct Particle
{
	double x, y;
	double vx, vy, fx, fy;
	double density, mass;
};

const double dt = 0.001; // Time step
const double h = 0.05; // Smoothing length
const double rho0 = 1000.0; // Reference density
const double k = 0.1; // Bulk modulus
const double g = 9.81; // Gravity
const double pi = 3.14; // pi

void hello_world();
double poly6Kernel(double r);
double distance(const Particle& p1, const Particle& p2);
void runStep(std::vector<Particle>& particles);
double calculateDensity(const std::vector<Particle>& particles, const Particle& p);
void calculatePressureForce(std::vector<Particle>& particles);
