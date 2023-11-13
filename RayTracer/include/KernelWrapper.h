#pragma once

#include <cuda_runtime.h>
#include <curand_kernel.h>
#include <stdio.h>

void deviceHelloWorld();
void deviceRayKernel(size_t width, size_t height, size_t samplesPerPixel);