#include "KernelWrapper.h"
#include "Color.hpp"

__global__ void cuda_hello()
{
	printf("Hello World from a GPU \n");
}



__global__ void
add_ray_color(size_t width, size_t height, size_t samplesPerPixel, Color* cumulativeColors)
{
	// printf("Hello World from a GPU \n");
	//wriite the indexes

	size_t i = blockIdx.x * blockDim.x + threadIdx.x;
	size_t j = blockIdx.y * blockDim.y + threadIdx.y;
	size_t s = blockIdx.z * blockDim.z + threadIdx.z;

	//note: no loops, every thread gets one of these..

	if(i < width && j < height && s < samplesPerPixel)
	{
		//printf("Hello World from a GPU, thread %d\n", i + j + s);
		curandState state;
		curand_init(0, i + j + s, 0, &state);

		auto x = double(i + curand_uniform(&state)) / (width - 1);
		auto y = double(j + curand_uniform(&state)) / (height - 1);

		//do something with this..
	}
}



void deviceHelloWorld()
{
	cuda_hello<<<1, 10>>>();
}

void deviceRayKernel(size_t width, size_t height, size_t samplesPerPixel)
{

	dim3 blockDim(8, 8, 8);
	dim3 gridDim((width + blockDim.x - 1) / blockDim.x,
				 (height + blockDim.y - 1) / blockDim.y,
				 (samplesPerPixel + blockDim.z - 1) / blockDim.z); // Calculate grid dimensions

	size_t totalIterations = width * height * samplesPerPixel;

	// Allocate memory
	// Allocate and initialize device memory for randState and cumulativeColors
	Color* devCumulativeColors;

	size_t memorySize = width * height * samplesPerPixel * sizeof(curandState);
	
	cudaMalloc((void**)&devCumulativeColors, memorySize);
	cudaMemset(devCumulativeColors, 0, memorySize);

	add_ray_color<<<gridDim, blockDim>>>(width, height, samplesPerPixel, devCumulativeColors);

	cudaFree(devCumulativeColors);
}

