#include "optixTriangle.h"
#include <GLFW/glfw3.h>
#include <array>
#include <cuda_runtime.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <optix.h>
#include <optix_function_table_definition.h>
#include <optix_stubs.h>
#include <sstream>
#include <stdexcept>
#include <vector>

#define TRIANGLE 1
#define CUBE 0
#define ISO 0

#define CUDA_CHECK(call) cudaCheck(call, #call, __FILE__, __LINE__)
#define OPTIX_CHECK(call) optixCheck(call, #call, __FILE__, __LINE__)

void errorCallback(int error, const char* description)
{
	std::cerr << "GLFW Error: " << description << std::endl;
}

void writePPM(const char* filename, const uchar4* h_output_buffer, int width, int height)
{
	// Open file for writing
	std::ofstream file(filename, std::ios::out | std::ios::binary);
	if(!file)
	{
		std::cerr << "Error opening file: " << filename << std::endl;
		return;
	}

	// Write PPM header
	file << "P6\n" << width << " " << height << "\n255\n";

	// Write pixel data
	for(int i = 0; i < width * height; ++i)
	{
		file << h_output_buffer[i].x << h_output_buffer[i].y << h_output_buffer[i].z;
	}

	// Close file
	file.close();

	std::cout << "PPM file saved: " << filename << std::endl;
}

inline void cudaCheck(cudaError_t error, const char* call, const char* file, unsigned int line)
{
	if(error != cudaSuccess)
	{
		std::stringstream ss;
		ss << "CUDA call (" << call << " ) failed with error: '" << cudaGetErrorString(error)
		   << "' (" << file << ":" << line << ")\n";
		throw std::runtime_error(ss.str().c_str());
	}
}

inline void optixCheck(OptixResult res, const char* call, const char* file, unsigned int line)
{
	if(res != OPTIX_SUCCESS)
	{
		std::stringstream ss;
		ss << "Optix call '" << call << "' failed: " << file << ':' << line << ")\n";
		throw std::runtime_error(ss.str().c_str());
	}
}

template <typename T>
struct SbtRecord
{
	__align__(OPTIX_SBT_RECORD_ALIGNMENT) char header[OPTIX_SBT_RECORD_HEADER_SIZE];
	T data;
};

typedef SbtRecord<RayGenData> RayGenSbtRecord;
typedef SbtRecord<MissData> MissSbtRecord;
typedef SbtRecord<HitGroupData> HitGroupSbtRecord;

int main()
{

	int width = 1024;
	int height = 768;

	// Initialize CUDA
	CUcontext cuCtx = 0; // zero means take the current context

	// Applications wishing to leverage multiple GPUs in a system may create multiple device contexts and use them to invoke independent launches per device.

	CUDA_CHECK(cudaFree(0)); // Initialize CUDA

	//A good practice is to zero-initialize all OptiX input structs to mark all fields as default, then to selectively override the fields to be used.

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

	OPTIX_CHECK(optixInit());

	OptixResult optixRes = optixDeviceContextCreate(cuCtx, &options, &context);
	if(optixRes != OPTIX_SUCCESS)
	{
		std::cerr << "Error creating OptiX device context" << std::endl;
		return 1;
	}

	std::cout << "Hello, OptiX!" << std::endl;

	// Initialize GLFW
	if(!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	glfwSetErrorCallback(errorCallback);

	GLFWwindow* window = glfwCreateWindow(width, height, "Optix GLFW Example", NULL, NULL);
	if(!window)
	{
		glfwTerminate();
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);

	//now do your thing:

	//Define geometry and create GAS
	OptixTraversableHandle gas_handle;
	CUdeviceptr d_gas_output_buffer;
	{
		// Use default options for simplicity.  In a real use case we would want to
		// enable compaction, etc
		OptixAccelBuildOptions accel_options = {};
		accel_options.buildFlags = OPTIX_BUILD_FLAG_NONE;
		accel_options.operation = OPTIX_BUILD_OPERATION_BUILD;

#if TRIANGLE
		// Triangle build input: simple list of three vertices
		const std::array<float3, 3> vertices = {
			{{-0.5f, -0.5f, 0.0f}, {0.5f, -0.5f, 0.0f}, {0.0f, 0.5f, 0.0f}}};
#elif CUBE
		const std::vector<float3> vertices = {
			{-0.5f, -0.5f, -0.5f},
			{0.5f, -0.5f, -0.5f},
			{0.5f, 0.5f, -0.5f},
			{-0.5f, 0.5f, -0.5f}, // back face
			{-0.5f, -0.5f, 0.5f},
			{0.5f, -0.5f, 0.5f},
			{0.5f, 0.5f, 0.5f},
			{-0.5f, 0.5f, 0.5f} // front face
		};
#elif ISO
		const std::vector<float3> vertices = {{0.0f, 1.0f, 1.61803398875f},
											  {0.0f, 1.0f, -1.61803398875f},
											  {0.0f, -1.0f, 1.61803398875f},
											  {0.0f, -1.0f, -1.61803398875f},
											  {1.0f, 1.61803398875f, 0.0f},
											  {1.0f, -1.61803398875f, 0.0f},
											  {-1.0f, 1.61803398875f, 0.0f},
											  {-1.0f, -1.61803398875f, 0.0f},
											  {1.61803398875f, 0.0f, 1.0f},
											  {1.61803398875f, 0.0f, -1.0f},
											  {-1.61803398875f, 0.0f, 1.0f},
											  {-1.61803398875f, 0.0f, -1.0f}};
#endif
		const size_t vertices_size = sizeof(float3) * vertices.size();
		CUdeviceptr d_vertices = 0;
		CUDA_CHECK(cudaMalloc(reinterpret_cast<void**>(&d_vertices), vertices_size));
		CUDA_CHECK(cudaMemcpy(reinterpret_cast<void*>(d_vertices),
							  vertices.data(),
							  vertices_size,
							  cudaMemcpyHostToDevice));

		const uint32_t triangle_input_flags[1] = {OPTIX_GEOMETRY_FLAG_NONE};
		OptixBuildInput triangle_input = {};
		triangle_input.type = OPTIX_BUILD_INPUT_TYPE_TRIANGLES;
		triangle_input.triangleArray.vertexFormat = OPTIX_VERTEX_FORMAT_FLOAT3;
		triangle_input.triangleArray.numVertices = static_cast<uint32_t>(vertices.size());
		triangle_input.triangleArray.vertexBuffers = &d_vertices;
		triangle_input.triangleArray.flags = triangle_input_flags;
		triangle_input.triangleArray.numSbtRecords = 1;

		OptixAccelBufferSizes gas_buffer_sizes;
		OPTIX_CHECK(optixAccelComputeMemoryUsage(context,
												 &accel_options,
												 &triangle_input,
												 1, // Number of build inputs
												 &gas_buffer_sizes));
		CUdeviceptr d_temp_buffer_gas;
		CUDA_CHECK(cudaMalloc(reinterpret_cast<void**>(&d_temp_buffer_gas),
							  gas_buffer_sizes.tempSizeInBytes));
		CUDA_CHECK(cudaMalloc(reinterpret_cast<void**>(&d_gas_output_buffer),
							  gas_buffer_sizes.outputSizeInBytes));

		OPTIX_CHECK(optixAccelBuild(context,
									0, // CUDA stream
									&accel_options,
									&triangle_input,
									1, // num build inputs
									d_temp_buffer_gas,
									gas_buffer_sizes.tempSizeInBytes,
									d_gas_output_buffer,
									gas_buffer_sizes.outputSizeInBytes,
									&gas_handle,
									nullptr, // emitted property list
									0 // num emitted properties
									));

		// We can now free the scratch space buffer used during build and the vertex
		// inputs, since they are not needed by our trivial shading method
		CUDA_CHECK(cudaFree(reinterpret_cast<void*>(d_temp_buffer_gas)));
		CUDA_CHECK(cudaFree(reinterpret_cast<void*>(d_vertices)));
	}

	//
	// Create module
	//

	// Now that we have created our geometry, we need to specify the OptiX programs we want to use to render it.
	// The CUDA code for our programs first needs to be converted to NVIDIA’s intermediate code representation, PTX, usually via the CUDA nvcc compiler.
	// The programs in PTX form are then compiled into OptixModules.

	OptixModule module = nullptr;
	OptixPipelineCompileOptions pipeline_compile_options = {};
	{
		OptixModuleCompileOptions module_compile_options = {};
		module_compile_options.optLevel = OPTIX_COMPILE_OPTIMIZATION_LEVEL_0;
		module_compile_options.debugLevel = OPTIX_COMPILE_DEBUG_LEVEL_FULL;
		pipeline_compile_options.usesMotionBlur = false;
		pipeline_compile_options.traversableGraphFlags =
			OPTIX_TRAVERSABLE_GRAPH_FLAG_ALLOW_SINGLE_GAS;
		pipeline_compile_options.numPayloadValues = 3;
		pipeline_compile_options.numAttributeValues = 3;
		pipeline_compile_options.exceptionFlags = OPTIX_EXCEPTION_FLAG_NONE;
		pipeline_compile_options.pipelineLaunchParamsVariableName = "params";
		pipeline_compile_options.usesPrimitiveTypeFlags = OPTIX_PRIMITIVE_TYPE_FLAGS_TRIANGLE;

		//at this point, you'll need to compile a .cu file into .ptx
		// read file into string
		std::string filename =
			"optixTriangleKernel.ptx"; // make sure it is in the working directory
		std::ifstream file(filename.c_str(), std::ios::binary);
		std::string file_contents;
		if(file.good())
		{
			// Found usable source file
			std::vector<unsigned char> buffer =
				std::vector<unsigned char>(std::istreambuf_iterator<char>(file), {});
			file_contents.assign(buffer.begin(), buffer.end());
		}
		char log[2048];
		size_t sizeof_log = sizeof(log);

		optixModuleCreate(context,
						  &module_compile_options,
						  &pipeline_compile_options,
						  file_contents.c_str(),
						  file_contents.size(),
						  log,
						  &sizeof_log,
						  &module);
	}

	//
	// Create program groups
	//
	//  One or more modules are used to create an OptixProgramGroup.
	// Those program groups are then linked into an OptixPipeline, enabling them to work together on the GPU.
	OptixProgramGroup raygen_prog_group = nullptr;
	OptixProgramGroup miss_prog_group = nullptr;
	OptixProgramGroup hitgroup_prog_group = nullptr;
	{
		OptixProgramGroupOptions program_group_options = {}; // Initialize to zeros

		OptixProgramGroupDesc raygen_prog_group_desc = {}; //
		raygen_prog_group_desc.kind = OPTIX_PROGRAM_GROUP_KIND_RAYGEN;
		raygen_prog_group_desc.raygen.module = module;
		raygen_prog_group_desc.raygen.entryFunctionName = "__raygen__rg";

		char log[2048];
		size_t sizeof_log = sizeof(log);

		optixProgramGroupCreate(context,
								&raygen_prog_group_desc,
								1, // num program groups
								&program_group_options,
								log,
								&sizeof_log,
								&raygen_prog_group);

		OptixProgramGroupDesc miss_prog_group_desc = {};
		miss_prog_group_desc.kind = OPTIX_PROGRAM_GROUP_KIND_MISS;
		miss_prog_group_desc.miss.module = module;
		miss_prog_group_desc.miss.entryFunctionName = "__miss__ms";
		optixProgramGroupCreate(context,
								&miss_prog_group_desc,
								1, // num program groups
								&program_group_options,
								log,
								&sizeof_log,
								&miss_prog_group);

		OptixProgramGroupDesc hitgroup_prog_group_desc = {};
		hitgroup_prog_group_desc.kind = OPTIX_PROGRAM_GROUP_KIND_HITGROUP;
		hitgroup_prog_group_desc.hitgroup.moduleCH = module;
		hitgroup_prog_group_desc.hitgroup.entryFunctionNameCH = "__closesthit__ch";
		optixProgramGroupCreate(context,
								&hitgroup_prog_group_desc,
								1, // num program groups
								&program_group_options,
								log,
								&sizeof_log,
								&hitgroup_prog_group);
	}

	//
	// Link pipeline
	//
	OptixPipeline pipeline = nullptr;
	{
		const uint32_t max_trace_depth = 1;
		OptixProgramGroup program_groups[] = {
			raygen_prog_group, miss_prog_group, hitgroup_prog_group};

		char log[2048];
		size_t sizeof_log = sizeof(log);

		OptixPipelineLinkOptions pipeline_link_options = {};
		pipeline_link_options.maxTraceDepth = max_trace_depth;
		optixPipelineCreate(context,
							&pipeline_compile_options,
							&pipeline_link_options,
							program_groups,
							sizeof(program_groups) / sizeof(program_groups[0]),
							log,
							&sizeof_log,
							&pipeline);
	}

	//
	// Set up shader binding table
	//
	OptixShaderBindingTable sbt = {};
	{
		CUdeviceptr raygen_record;
		const size_t raygen_record_size = sizeof(RayGenSbtRecord);
		CUDA_CHECK(cudaMalloc(reinterpret_cast<void**>(&raygen_record), raygen_record_size));
		RayGenSbtRecord rg_sbt;
		OPTIX_CHECK(optixSbtRecordPackHeader(raygen_prog_group, &rg_sbt));
		CUDA_CHECK(cudaMemcpy(reinterpret_cast<void*>(raygen_record),
							  &rg_sbt,
							  raygen_record_size,
							  cudaMemcpyHostToDevice));

		CUdeviceptr miss_record;
		size_t miss_record_size = sizeof(MissSbtRecord);
		CUDA_CHECK(cudaMalloc(reinterpret_cast<void**>(&miss_record), miss_record_size));
		MissSbtRecord ms_sbt;
		ms_sbt.data = {0.3f, 0.1f, 0.2f};
		OPTIX_CHECK(optixSbtRecordPackHeader(miss_prog_group, &ms_sbt));
		CUDA_CHECK(cudaMemcpy(reinterpret_cast<void*>(miss_record),
							  &ms_sbt,
							  miss_record_size,
							  cudaMemcpyHostToDevice));

		CUdeviceptr hitgroup_record;
		size_t hitgroup_record_size = sizeof(HitGroupSbtRecord);
		CUDA_CHECK(cudaMalloc(reinterpret_cast<void**>(&hitgroup_record), hitgroup_record_size));
		HitGroupSbtRecord hg_sbt;
		OPTIX_CHECK(optixSbtRecordPackHeader(hitgroup_prog_group, &hg_sbt));
		CUDA_CHECK(cudaMemcpy(reinterpret_cast<void*>(hitgroup_record),
							  &hg_sbt,
							  hitgroup_record_size,
							  cudaMemcpyHostToDevice));

		sbt.raygenRecord = raygen_record;
		sbt.missRecordBase = miss_record;
		// SBT stride and SBT offset are used to implement multiple ray types where a different set of programs are used for each type.
		// The stride indicates the total number of ray types in use (eg, many rendering applications use a radiance and shadow ray type and would set this to two).
		// The offset is used to select the correct program for a given ray type.
		sbt.missRecordStrideInBytes = sizeof(MissSbtRecord);
		sbt.missRecordCount = 1;
		sbt.hitgroupRecordBase = hitgroup_record;
		sbt.hitgroupRecordStrideInBytes = sizeof(HitGroupSbtRecord);
		sbt.hitgroupRecordCount = 1;
	}

	uchar4* d_output_buffer;
	size_t buffer_size = width * height * sizeof(uchar4);

	// Allocate device memory for output buffer
	CUDA_CHECK(cudaMalloc(reinterpret_cast<void**>(&d_output_buffer), buffer_size));

	// launch and get back results

	CUstream stream;
	CUDA_CHECK(cudaStreamCreate(&stream));

	Params params;
	params.image = d_output_buffer;
	params.image_width = width;
	params.image_height = height;
	params.handle = gas_handle;
	//pulled the values from the SDK example
	params.cam_u = make_float3(1.10456955f, 0.0f, 0.0f); // Example: X axis
	params.cam_v = make_float3(0.0f, 0.828427136f, 0.0f); // Example: Y axis
	params.cam_w =
		make_float3(0.0f, 0.0f, -2.00000000f); // Example: -Z axis (assuming camera looks along -Z)
	params.cam_eye = make_float3(0.0f, 0.0f, 2.00000000f); // Example: Camera position at (0, 0, 1)

	CUdeviceptr d_param;
	CUDA_CHECK(cudaMalloc(reinterpret_cast<void**>(&d_param), sizeof(Params)));
	CUDA_CHECK(cudaMemcpy(
		reinterpret_cast<void*>(d_param), &params, sizeof(params), cudaMemcpyHostToDevice));

	OPTIX_CHECK(
		optixLaunch(pipeline, stream, d_param, sizeof(Params), &sbt, width, height, /*depth=*/1));

	CUDA_CHECK(cudaFree(reinterpret_cast<void*>(d_param)));

	// Copy results back from device to host if needed
	uchar4* h_output_buffer = new uchar4[width * height];
	CUDA_CHECK(cudaMemcpy(h_output_buffer, d_output_buffer, buffer_size, cudaMemcpyDeviceToHost));

	// Process or save the output as needed

	// Free device memory for output buffer
	CUDA_CHECK(cudaFree(d_output_buffer));

	//display buffer in glfw/image

	writePPM("accumulatedFrame_optix.ppm", h_output_buffer, width, height);

	while(!glfwWindowShouldClose(window))
	{
		// Clear the framebuffer
		glClear(GL_COLOR_BUFFER_BIT);

		// Access framebuffer and update GLFW window
		glDrawPixels(width, height, GL_RGBA, GL_UNSIGNED_BYTE, h_output_buffer);

		// Swap buffers and poll for events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//delete
	delete[] h_output_buffer;

	// Destroy CUDA stream
	CUDA_CHECK(cudaStreamDestroy(stream));

	optixDeviceContextDestroy(context);

	glfwTerminate();

	return 0;
}
