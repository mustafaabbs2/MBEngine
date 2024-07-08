#include <cuda_runtime.h>
#include <iostream>
#include <optix.h>
#include <optix_function_table_definition.h>
#include <optix_stubs.h>

int main()
{
	// Initialize CUDA
	CUcontext cuCtx = 0; // zero means take the current context
	cudaFree(0); // Initialize CUDA

	// Create an OptiX device context
	OptixDeviceContext context = nullptr;
	OptixDeviceContextOptions options = {};
	options.logCallbackFunction = nullptr;
	options.logCallbackLevel = 4;

	CUresult cuRes = cuCtxGetCurrent(&cuCtx);
	if(cuRes != CUDA_SUCCESS)
	{
		std::cerr << "Error getting current CUDA context" << std::endl;
		return 1;
	}

	OptixResult optixRes = optixDeviceContextCreate(cuCtx, &options, &context);
	if(optixRes != OPTIX_SUCCESS)
	{
		std::cerr << "Error creating OptiX device context" << std::endl;
		return 1;
	}

	std::cout << "Hello, OptiX!" << std::endl;

	optixDeviceContextDestroy(context);

	return 0;
}

