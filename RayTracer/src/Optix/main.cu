#include <iostream>
#include <optix.h>

int main()
{
	// OptixDeviceContext context = nullptr;
	// CUcontext cuCtx = 0; // zero means take the current context
	// OptixDeviceContextOptions options = {};
	// options.logCallbackFunction = nullptr;
	// options.logCallbackLevel = 4;

	optixInit();
	// optixDeviceContextCreate(cuCtx, &options, &context);

	std::cout << "Hello, OptiX!" << std::endl;

	// optixDeviceContextDestroy(context);

	return 0;
}