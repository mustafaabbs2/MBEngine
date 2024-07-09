#include <optix.h>

#include "optixTriangle.h"

extern "C"
{
	__constant__ Params params;
}

static __forceinline__ __device__ void setPayload(float3 p)
{
	optixSetPayload_0(__float_as_uint(p.x));
	optixSetPayload_1(__float_as_uint(p.y));
	optixSetPayload_2(__float_as_uint(p.z));
}

__host__ __device__ float3 make_float3(const float2& a)
{
	return make_float3(a.x, a.y, 0.0f);
}

__host__ __device__ float3 make_float3(const float2& v0, const float v1)
{
	return make_float3(v0.x, v0.y, v1);
}

__host__ __device__ inline float2 operator*(const float2& a, const float2& b)
{
	return make_float2(a.x * b.x, a.y * b.y);
}

__host__ __device__ inline float2 operator*(const float2& a, const float s)
{
	return make_float2(a.x * s, a.y * s);
}

__host__ __device__ inline float2 operator*(const float s, const float2& a)
{
	return make_float2(a.x * s, a.y * s);
}

__host__ __device__ inline void operator*=(float2& a, const float2& s)
{
	a.x *= s.x;
	a.y *= s.y;
}

__host__ __device__ inline void operator*=(float2& a, const float s)
{
	a.x *= s;
	a.y *= s;
}

/** divide 
* @{
*/
__host__ __device__ inline float2 operator/(const float2& a, const float2& b)
{
	return make_float2(a.x / b.x, a.y / b.y);
}

__host__ __device__ inline float2 operator/(const float2& a, const float s)
{
	float inv = 1.0f / s;
	return a * inv;
}

__host__ __device__ inline float2 operator/(const float s, const float2& a)
{
	return make_float2(s / a.x, s / a.y);
}

__host__ __device__ inline void operator/=(float2& a, const float s)
{
	float inv = 1.0f / s;
	a *= inv;
}

/** add 
* @{
*/
__host__ __device__ inline float3 operator+(const float3& a, const float3& b)
{
	return make_float3(a.x + b.x, a.y + b.y, a.z + b.z);
}

__host__ __device__ inline float3 operator+(const float3& a, const float b)
{
	return make_float3(a.x + b, a.y + b, a.z + b);
}

__host__ __device__ inline float3 operator+(const float a, const float3& b)
{
	return make_float3(a + b.x, a + b.y, a + b.z);
}

__host__ __device__ inline void operator+=(float3& a, const float3& b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
}
/** @} */

/** subtract 
* @{
*/
__host__ __device__ inline float3 operator-(const float3& a, const float3& b)
{
	return make_float3(a.x - b.x, a.y - b.y, a.z - b.z);
}

__host__ __device__ inline float3 operator-(const float3& a, const float b)
{
	return make_float3(a.x - b, a.y - b, a.z - b);
}

__host__ __device__ inline float3 operator-(const float a, const float3& b)
{
	return make_float3(a - b.x, a - b.y, a - b.z);
}

__host__ __device__ inline void operator-=(float3& a, const float3& b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
}
/** @} */

/** multiply 
* @{
*/
__host__ __device__ inline float3 operator*(const float3& a, const float3& b)
{
	return make_float3(a.x * b.x, a.y * b.y, a.z * b.z);
}

__host__ __device__ inline float3 operator*(const float3& a, const float s)
{
	return make_float3(a.x * s, a.y * s, a.z * s);
}

__host__ __device__ inline float3 operator*(const float s, const float3& a)
{
	return make_float3(a.x * s, a.y * s, a.z * s);
}

__host__ __device__ inline void operator*=(float3& a, const float3& s)
{
	a.x *= s.x;
	a.y *= s.y;
	a.z *= s.z;
}

__host__ __device__ inline void operator*=(float3& a, const float s)
{
	a.x *= s;
	a.y *= s;
	a.z *= s;
}
/** @} */

/** divide 
* @{
*/
__host__ __device__ inline float3 operator/(const float3& a, const float3& b)
{
	return make_float3(a.x / b.x, a.y / b.y, a.z / b.z);
}

__host__ __device__ inline float3 operator/(const float3& a, const float s)
{
	float inv = 1.0f / s;
	return a * inv;
}

__host__ __device__ inline float3 operator/(const float s, const float3& a)
{
	return make_float3(s / a.x, s / a.y, s / a.z);
}

__host__ __device__ inline void operator/=(float3& a, const float s)
{
	float inv = 1.0f / s;
	a *= inv;
}

//vector operations
__host__ __device__ float dot(const float3& a, const float3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

__host__ __device__ float3 normalize(const float3& v)
{
	float invLen = 1.0f / sqrtf(dot(v, v));
	return v * invLen;
}

//color helpers
__forceinline__ __device__ float3 toSRGB(const float3& c)
{
	float invGamma = 1.0f / 2.4f;
	float3 powed = make_float3(powf(c.x, invGamma), powf(c.y, invGamma), powf(c.z, invGamma));
	return make_float3(c.x < 0.0031308f ? 12.92f * c.x : 1.055f * powed.x - 0.055f,
					   c.y < 0.0031308f ? 12.92f * c.y : 1.055f * powed.y - 0.055f,
					   c.z < 0.0031308f ? 12.92f * c.z : 1.055f * powed.z - 0.055f);
}

__forceinline__ __device__ float clamp(const float f, const float a, const float b)
{
	return fmaxf(a, fminf(f, b));
}

__forceinline__ __device__ float3 clamp(const float3& v, const float a, const float b)
{
	return make_float3(clamp(v.x, a, b), clamp(v.y, a, b), clamp(v.z, a, b));
}

__forceinline__ __device__ unsigned char quantizeUnsigned8Bits(float x)
{
	x = clamp(x, 0.0f, 1.0f);
	enum
	{
		N = (1 << 8) - 1,
		Np1 = (1 << 8)
	};
	return (unsigned char)min((unsigned int)(x * (float)Np1), (unsigned int)N);
}

__forceinline__ __device__ uchar4 make_color(const float3& c)
{
	// first apply gamma, then convert to unsigned char
	float3 srgb = toSRGB(clamp(c, 0.0f, 1.0f));
	return make_uchar4(quantizeUnsigned8Bits(srgb.x),
					   quantizeUnsigned8Bits(srgb.y),
					   quantizeUnsigned8Bits(srgb.z),
					   255u);
}

__forceinline__ __device__ uchar4 make_color(const float4& c)
{
	return make_color(make_float3(c.x, c.y, c.z));
}

static __forceinline__ __device__ void
computeRay(uint3 idx, uint3 dim, float3& origin, float3& direction)
{
	const float3 U = params.cam_u;
	const float3 V = params.cam_v;
	const float3 W = params.cam_w;
	const float2 d = make_float2(static_cast<float>(idx.x) / static_cast<float>(dim.x),
								 static_cast<float>(idx.y) / static_cast<float>(dim.y));

	origin = params.cam_eye;
	direction = normalize(d.x * U + d.y * V + W);
}

extern "C" __global__ void __raygen__rg()
{
	// Lookup our location within the launch grid
	const uint3 idx = optixGetLaunchIndex();
	const uint3 dim = optixGetLaunchDimensions();

	// Map our launch idx to a screen location and create a ray from the camera
	// location through the screen
	float3 ray_origin, ray_direction;
	computeRay(idx, dim, ray_origin, ray_direction);

	// Trace the ray against our scene hierarchy
	unsigned int p0, p1, p2;
	optixTrace(params.handle,
			   ray_origin,
			   ray_direction,
			   0.0f, // Min intersection distance
			   1e16f, // Max intersection distance
			   0.0f, // rayTime -- used for motion blur
			   OptixVisibilityMask(255), // Specify always visible
			   OPTIX_RAY_FLAG_NONE,
			   0, // SBT offset   -- See SBT discussion
			   1, // SBT stride   -- See SBT discussion
			   0, // missSBTIndex -- See SBT discussion
			   p0,
			   p1,
			   p2);
	float3 result;
	result.x = __uint_as_float(p0);
	result.y = __uint_as_float(p1);
	result.z = __uint_as_float(p2);

	// Record results in our output raster
	params.image[idx.y * params.image_width + idx.x] = make_color(result);
}

extern "C" __global__ void __miss__ms()
{
	MissData* miss_data = reinterpret_cast<MissData*>(optixGetSbtDataPointer());
	setPayload(miss_data->bg_color);
}

extern "C" __global__ void __closesthit__ch()
{
	// When built-in triangle intersection is used, a number of fundamental
	// attributes are provided by the OptiX API, indlucing barycentric coordinates.
	const float2 barycentrics = optixGetTriangleBarycentrics();

	setPayload(make_float3(barycentrics, 1.0f));
}
