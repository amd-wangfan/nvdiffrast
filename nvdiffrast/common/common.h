// Copyright (c) 2020, NVIDIA CORPORATION.  All rights reserved.
//
// NVIDIA CORPORATION and its licensors retain all intellectual property
// and proprietary rights in and to this software, related documentation
// and any modifications thereto.  Any use, reproduction, disclosure or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA CORPORATION is strictly prohibited.

#pragma once
#if (defined(USE_HIP) || defined(USE_ROCM))
#include <hip/hip_runtime.h>
#include <hip/hip_cooperative_groups.h>
#else
#include <cuda.h>
#endif
#include <stdint.h>

//------------------------------------------------------------------------
// C++ helper function prototypes.

dim3 getLaunchBlockSize(int maxWidth, int maxHeight, int width, int height);
dim3 getLaunchGridSize(dim3 blockSize, int width, int height, int depth);

//------------------------------------------------------------------------
// The rest is CUDA device code specific stuff.

#if (defined(__CUDACC__) || defined(USE_HIP))

//------------------------------------------------------------------------
// Helpers for CUDA vector types.

static __device__ __forceinline__ float2&   operator*=  (float2& a, const float2& b)       { a.x *= b.x; a.y *= b.y; return a; }
static __device__ __forceinline__ float2&   operator+=  (float2& a, const float2& b)       { a.x += b.x; a.y += b.y; return a; }
static __device__ __forceinline__ float2&   operator-=  (float2& a, const float2& b)       { a.x -= b.x; a.y -= b.y; return a; }
static __device__ __forceinline__ float2&   operator*=  (float2& a, float b)               { a.x *= b; a.y *= b; return a; }
static __device__ __forceinline__ float2&   operator+=  (float2& a, float b)               { a.x += b; a.y += b; return a; }
static __device__ __forceinline__ float2&   operator-=  (float2& a, float b)               { a.x -= b; a.y -= b; return a; }
static __device__ __forceinline__ float2    operator*   (const float2& a, const float2& b) { return make_float2(a.x * b.x, a.y * b.y); }
static __device__ __forceinline__ float2    operator+   (const float2& a, const float2& b) { return make_float2(a.x + b.x, a.y + b.y); }
static __device__ __forceinline__ float2    operator-   (const float2& a, const float2& b) { return make_float2(a.x - b.x, a.y - b.y); }
static __device__ __forceinline__ float2    operator*   (const float2& a, float b)         { return make_float2(a.x * b, a.y * b); }
static __device__ __forceinline__ float2    operator+   (const float2& a, float b)         { return make_float2(a.x + b, a.y + b); }
static __device__ __forceinline__ float2    operator-   (const float2& a, float b)         { return make_float2(a.x - b, a.y - b); }
static __device__ __forceinline__ float2    operator*   (float a, const float2& b)         { return make_float2(a * b.x, a * b.y); }
static __device__ __forceinline__ float2    operator+   (float a, const float2& b)         { return make_float2(a + b.x, a + b.y); }
static __device__ __forceinline__ float2    operator-   (float a, const float2& b)         { return make_float2(a - b.x, a - b.y); }
static __device__ __forceinline__ float2    operator-   (const float2& a)                  { return make_float2(-a.x, -a.y); }
static __device__ __forceinline__ float3&   operator*=  (float3& a, const float3& b)       { a.x *= b.x; a.y *= b.y; a.z *= b.z; return a; }
static __device__ __forceinline__ float3&   operator+=  (float3& a, const float3& b)       { a.x += b.x; a.y += b.y; a.z += b.z; return a; }
static __device__ __forceinline__ float3&   operator-=  (float3& a, const float3& b)       { a.x -= b.x; a.y -= b.y; a.z -= b.z; return a; }
static __device__ __forceinline__ float3&   operator*=  (float3& a, float b)               { a.x *= b; a.y *= b; a.z *= b; return a; }
static __device__ __forceinline__ float3&   operator+=  (float3& a, float b)               { a.x += b; a.y += b; a.z += b; return a; }
static __device__ __forceinline__ float3&   operator-=  (float3& a, float b)               { a.x -= b; a.y -= b; a.z -= b; return a; }
static __device__ __forceinline__ float3    operator*   (const float3& a, const float3& b) { return make_float3(a.x * b.x, a.y * b.y, a.z * b.z); }
static __device__ __forceinline__ float3    operator+   (const float3& a, const float3& b) { return make_float3(a.x + b.x, a.y + b.y, a.z + b.z); }
static __device__ __forceinline__ float3    operator-   (const float3& a, const float3& b) { return make_float3(a.x - b.x, a.y - b.y, a.z - b.z); }
static __device__ __forceinline__ float3    operator*   (const float3& a, float b)         { return make_float3(a.x * b, a.y * b, a.z * b); }
static __device__ __forceinline__ float3    operator+   (const float3& a, float b)         { return make_float3(a.x + b, a.y + b, a.z + b); }
static __device__ __forceinline__ float3    operator-   (const float3& a, float b)         { return make_float3(a.x - b, a.y - b, a.z - b); }
static __device__ __forceinline__ float3    operator*   (float a, const float3& b)         { return make_float3(a * b.x, a * b.y, a * b.z); }
static __device__ __forceinline__ float3    operator+   (float a, const float3& b)         { return make_float3(a + b.x, a + b.y, a + b.z); }
static __device__ __forceinline__ float3    operator-   (float a, const float3& b)         { return make_float3(a - b.x, a - b.y, a - b.z); }
static __device__ __forceinline__ float3    operator-   (const float3& a)                  { return make_float3(-a.x, -a.y, -a.z); }
static __device__ __forceinline__ float4&   operator*=  (float4& a, const float4& b)       { a.x *= b.x; a.y *= b.y; a.z *= b.z; a.w *= b.w; return a; }
static __device__ __forceinline__ float4&   operator+=  (float4& a, const float4& b)       { a.x += b.x; a.y += b.y; a.z += b.z; a.w += b.w; return a; }
static __device__ __forceinline__ float4&   operator-=  (float4& a, const float4& b)       { a.x -= b.x; a.y -= b.y; a.z -= b.z; a.w -= b.w; return a; }
static __device__ __forceinline__ float4&   operator*=  (float4& a, float b)               { a.x *= b; a.y *= b; a.z *= b; a.w *= b; return a; }
static __device__ __forceinline__ float4&   operator+=  (float4& a, float b)               { a.x += b; a.y += b; a.z += b; a.w += b; return a; }
static __device__ __forceinline__ float4&   operator-=  (float4& a, float b)               { a.x -= b; a.y -= b; a.z -= b; a.w -= b; return a; }
static __device__ __forceinline__ float4    operator*   (const float4& a, const float4& b) { return make_float4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }
static __device__ __forceinline__ float4    operator+   (const float4& a, const float4& b) { return make_float4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
static __device__ __forceinline__ float4    operator-   (const float4& a, const float4& b) { return make_float4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
static __device__ __forceinline__ float4    operator*   (const float4& a, float b)         { return make_float4(a.x * b, a.y * b, a.z * b, a.w * b); }
static __device__ __forceinline__ float4    operator+   (const float4& a, float b)         { return make_float4(a.x + b, a.y + b, a.z + b, a.w + b); }
static __device__ __forceinline__ float4    operator-   (const float4& a, float b)         { return make_float4(a.x - b, a.y - b, a.z - b, a.w - b); }
static __device__ __forceinline__ float4    operator*   (float a, const float4& b)         { return make_float4(a * b.x, a * b.y, a * b.z, a * b.w); }
static __device__ __forceinline__ float4    operator+   (float a, const float4& b)         { return make_float4(a + b.x, a + b.y, a + b.z, a + b.w); }
static __device__ __forceinline__ float4    operator-   (float a, const float4& b)         { return make_float4(a - b.x, a - b.y, a - b.z, a - b.w); }
static __device__ __forceinline__ float4    operator-   (const float4& a)                  { return make_float4(-a.x, -a.y, -a.z, -a.w); }
static __device__ __forceinline__ int2&     operator*=  (int2& a, const int2& b)           { a.x *= b.x; a.y *= b.y; return a; }
static __device__ __forceinline__ int2&     operator+=  (int2& a, const int2& b)           { a.x += b.x; a.y += b.y; return a; }
static __device__ __forceinline__ int2&     operator-=  (int2& a, const int2& b)           { a.x -= b.x; a.y -= b.y; return a; }
static __device__ __forceinline__ int2&     operator*=  (int2& a, int b)                   { a.x *= b; a.y *= b; return a; }
static __device__ __forceinline__ int2&     operator+=  (int2& a, int b)                   { a.x += b; a.y += b; return a; }
static __device__ __forceinline__ int2&     operator-=  (int2& a, int b)                   { a.x -= b; a.y -= b; return a; }
static __device__ __forceinline__ int2      operator*   (const int2& a, const int2& b)     { return make_int2(a.x * b.x, a.y * b.y); }
static __device__ __forceinline__ int2      operator+   (const int2& a, const int2& b)     { return make_int2(a.x + b.x, a.y + b.y); }
static __device__ __forceinline__ int2      operator-   (const int2& a, const int2& b)     { return make_int2(a.x - b.x, a.y - b.y); }
static __device__ __forceinline__ int2      operator*   (const int2& a, int b)             { return make_int2(a.x * b, a.y * b); }
static __device__ __forceinline__ int2      operator+   (const int2& a, int b)             { return make_int2(a.x + b, a.y + b); }
static __device__ __forceinline__ int2      operator-   (const int2& a, int b)             { return make_int2(a.x - b, a.y - b); }
static __device__ __forceinline__ int2      operator*   (int a, const int2& b)             { return make_int2(a * b.x, a * b.y); }
static __device__ __forceinline__ int2      operator+   (int a, const int2& b)             { return make_int2(a + b.x, a + b.y); }
static __device__ __forceinline__ int2      operator-   (int a, const int2& b)             { return make_int2(a - b.x, a - b.y); }
static __device__ __forceinline__ int2      operator-   (const int2& a)                    { return make_int2(-a.x, -a.y); }
static __device__ __forceinline__ int3&     operator*=  (int3& a, const int3& b)           { a.x *= b.x; a.y *= b.y; a.z *= b.z; return a; }
static __device__ __forceinline__ int3&     operator+=  (int3& a, const int3& b)           { a.x += b.x; a.y += b.y; a.z += b.z; return a; }
static __device__ __forceinline__ int3&     operator-=  (int3& a, const int3& b)           { a.x -= b.x; a.y -= b.y; a.z -= b.z; return a; }
static __device__ __forceinline__ int3&     operator*=  (int3& a, int b)                   { a.x *= b; a.y *= b; a.z *= b; return a; }
static __device__ __forceinline__ int3&     operator+=  (int3& a, int b)                   { a.x += b; a.y += b; a.z += b; return a; }
static __device__ __forceinline__ int3&     operator-=  (int3& a, int b)                   { a.x -= b; a.y -= b; a.z -= b; return a; }
static __device__ __forceinline__ int3      operator*   (const int3& a, const int3& b)     { return make_int3(a.x * b.x, a.y * b.y, a.z * b.z); }
static __device__ __forceinline__ int3      operator+   (const int3& a, const int3& b)     { return make_int3(a.x + b.x, a.y + b.y, a.z + b.z); }
static __device__ __forceinline__ int3      operator-   (const int3& a, const int3& b)     { return make_int3(a.x - b.x, a.y - b.y, a.z - b.z); }
static __device__ __forceinline__ int3      operator*   (const int3& a, int b)             { return make_int3(a.x * b, a.y * b, a.z * b); }
static __device__ __forceinline__ int3      operator+   (const int3& a, int b)             { return make_int3(a.x + b, a.y + b, a.z + b); }
static __device__ __forceinline__ int3      operator-   (const int3& a, int b)             { return make_int3(a.x - b, a.y - b, a.z - b); }
static __device__ __forceinline__ int3      operator*   (int a, const int3& b)             { return make_int3(a * b.x, a * b.y, a * b.z); }
static __device__ __forceinline__ int3      operator+   (int a, const int3& b)             { return make_int3(a + b.x, a + b.y, a + b.z); }
static __device__ __forceinline__ int3      operator-   (int a, const int3& b)             { return make_int3(a - b.x, a - b.y, a - b.z); }
static __device__ __forceinline__ int3      operator-   (const int3& a)                    { return make_int3(-a.x, -a.y, -a.z); }
static __device__ __forceinline__ int4&     operator*=  (int4& a, const int4& b)           { a.x *= b.x; a.y *= b.y; a.z *= b.z; a.w *= b.w; return a; }
static __device__ __forceinline__ int4&     operator+=  (int4& a, const int4& b)           { a.x += b.x; a.y += b.y; a.z += b.z; a.w += b.w; return a; }
static __device__ __forceinline__ int4&     operator-=  (int4& a, const int4& b)           { a.x -= b.x; a.y -= b.y; a.z -= b.z; a.w -= b.w; return a; }
static __device__ __forceinline__ int4&     operator*=  (int4& a, int b)                   { a.x *= b; a.y *= b; a.z *= b; a.w *= b; return a; }
static __device__ __forceinline__ int4&     operator+=  (int4& a, int b)                   { a.x += b; a.y += b; a.z += b; a.w += b; return a; }
static __device__ __forceinline__ int4&     operator-=  (int4& a, int b)                   { a.x -= b; a.y -= b; a.z -= b; a.w -= b; return a; }
static __device__ __forceinline__ int4      operator*   (const int4& a, const int4& b)     { return make_int4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }
static __device__ __forceinline__ int4      operator+   (const int4& a, const int4& b)     { return make_int4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
static __device__ __forceinline__ int4      operator-   (const int4& a, const int4& b)     { return make_int4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
static __device__ __forceinline__ int4      operator*   (const int4& a, int b)             { return make_int4(a.x * b, a.y * b, a.z * b, a.w * b); }
static __device__ __forceinline__ int4      operator+   (const int4& a, int b)             { return make_int4(a.x + b, a.y + b, a.z + b, a.w + b); }
static __device__ __forceinline__ int4      operator-   (const int4& a, int b)             { return make_int4(a.x - b, a.y - b, a.z - b, a.w - b); }
static __device__ __forceinline__ int4      operator*   (int a, const int4& b)             { return make_int4(a * b.x, a * b.y, a * b.z, a * b.w); }
static __device__ __forceinline__ int4      operator+   (int a, const int4& b)             { return make_int4(a + b.x, a + b.y, a + b.z, a + b.w); }
static __device__ __forceinline__ int4      operator-   (int a, const int4& b)             { return make_int4(a - b.x, a - b.y, a - b.z, a - b.w); }
static __device__ __forceinline__ int4      operator-   (const int4& a)                    { return make_int4(-a.x, -a.y, -a.z, -a.w); }
static __device__ __forceinline__ uint2&    operator*=  (uint2& a, const uint2& b)         { a.x *= b.x; a.y *= b.y; return a; }
static __device__ __forceinline__ uint2&    operator+=  (uint2& a, const uint2& b)         { a.x += b.x; a.y += b.y; return a; }
static __device__ __forceinline__ uint2&    operator-=  (uint2& a, const uint2& b)         { a.x -= b.x; a.y -= b.y; return a; }
static __device__ __forceinline__ uint2&    operator*=  (uint2& a, unsigned int b)         { a.x *= b; a.y *= b; return a; }
static __device__ __forceinline__ uint2&    operator+=  (uint2& a, unsigned int b)         { a.x += b; a.y += b; return a; }
static __device__ __forceinline__ uint2&    operator-=  (uint2& a, unsigned int b)         { a.x -= b; a.y -= b; return a; }
static __device__ __forceinline__ uint2     operator*   (const uint2& a, const uint2& b)   { return make_uint2(a.x * b.x, a.y * b.y); }
static __device__ __forceinline__ uint2     operator+   (const uint2& a, const uint2& b)   { return make_uint2(a.x + b.x, a.y + b.y); }
static __device__ __forceinline__ uint2     operator-   (const uint2& a, const uint2& b)   { return make_uint2(a.x - b.x, a.y - b.y); }
static __device__ __forceinline__ uint2     operator*   (const uint2& a, unsigned int b)   { return make_uint2(a.x * b, a.y * b); }
static __device__ __forceinline__ uint2     operator+   (const uint2& a, unsigned int b)   { return make_uint2(a.x + b, a.y + b); }
static __device__ __forceinline__ uint2     operator-   (const uint2& a, unsigned int b)   { return make_uint2(a.x - b, a.y - b); }
static __device__ __forceinline__ uint2     operator*   (unsigned int a, const uint2& b)   { return make_uint2(a * b.x, a * b.y); }
static __device__ __forceinline__ uint2     operator+   (unsigned int a, const uint2& b)   { return make_uint2(a + b.x, a + b.y); }
static __device__ __forceinline__ uint2     operator-   (unsigned int a, const uint2& b)   { return make_uint2(a - b.x, a - b.y); }
static __device__ __forceinline__ uint3&    operator*=  (uint3& a, const uint3& b)         { a.x *= b.x; a.y *= b.y; a.z *= b.z; return a; }
static __device__ __forceinline__ uint3&    operator+=  (uint3& a, const uint3& b)         { a.x += b.x; a.y += b.y; a.z += b.z; return a; }
static __device__ __forceinline__ uint3&    operator-=  (uint3& a, const uint3& b)         { a.x -= b.x; a.y -= b.y; a.z -= b.z; return a; }
static __device__ __forceinline__ uint3&    operator*=  (uint3& a, unsigned int b)         { a.x *= b; a.y *= b; a.z *= b; return a; }
static __device__ __forceinline__ uint3&    operator+=  (uint3& a, unsigned int b)         { a.x += b; a.y += b; a.z += b; return a; }
static __device__ __forceinline__ uint3&    operator-=  (uint3& a, unsigned int b)         { a.x -= b; a.y -= b; a.z -= b; return a; }
static __device__ __forceinline__ uint3     operator*   (const uint3& a, const uint3& b)   { return make_uint3(a.x * b.x, a.y * b.y, a.z * b.z); }
static __device__ __forceinline__ uint3     operator+   (const uint3& a, const uint3& b)   { return make_uint3(a.x + b.x, a.y + b.y, a.z + b.z); }
static __device__ __forceinline__ uint3     operator-   (const uint3& a, const uint3& b)   { return make_uint3(a.x - b.x, a.y - b.y, a.z - b.z); }
static __device__ __forceinline__ uint3     operator*   (const uint3& a, unsigned int b)   { return make_uint3(a.x * b, a.y * b, a.z * b); }
static __device__ __forceinline__ uint3     operator+   (const uint3& a, unsigned int b)   { return make_uint3(a.x + b, a.y + b, a.z + b); }
static __device__ __forceinline__ uint3     operator-   (const uint3& a, unsigned int b)   { return make_uint3(a.x - b, a.y - b, a.z - b); }
static __device__ __forceinline__ uint3     operator*   (unsigned int a, const uint3& b)   { return make_uint3(a * b.x, a * b.y, a * b.z); }
static __device__ __forceinline__ uint3     operator+   (unsigned int a, const uint3& b)   { return make_uint3(a + b.x, a + b.y, a + b.z); }
static __device__ __forceinline__ uint3     operator-   (unsigned int a, const uint3& b)   { return make_uint3(a - b.x, a - b.y, a - b.z); }
static __device__ __forceinline__ uint4&    operator*=  (uint4& a, const uint4& b)         { a.x *= b.x; a.y *= b.y; a.z *= b.z; a.w *= b.w; return a; }
static __device__ __forceinline__ uint4&    operator+=  (uint4& a, const uint4& b)         { a.x += b.x; a.y += b.y; a.z += b.z; a.w += b.w; return a; }
static __device__ __forceinline__ uint4&    operator-=  (uint4& a, const uint4& b)         { a.x -= b.x; a.y -= b.y; a.z -= b.z; a.w -= b.w; return a; }
static __device__ __forceinline__ uint4&    operator*=  (uint4& a, unsigned int b)         { a.x *= b; a.y *= b; a.z *= b; a.w *= b; return a; }
static __device__ __forceinline__ uint4&    operator+=  (uint4& a, unsigned int b)         { a.x += b; a.y += b; a.z += b; a.w += b; return a; }
static __device__ __forceinline__ uint4&    operator-=  (uint4& a, unsigned int b)         { a.x -= b; a.y -= b; a.z -= b; a.w -= b; return a; }
static __device__ __forceinline__ uint4     operator*   (const uint4& a, const uint4& b)   { return make_uint4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }
static __device__ __forceinline__ uint4     operator+   (const uint4& a, const uint4& b)   { return make_uint4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
static __device__ __forceinline__ uint4     operator-   (const uint4& a, const uint4& b)   { return make_uint4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
static __device__ __forceinline__ uint4     operator*   (const uint4& a, unsigned int b)   { return make_uint4(a.x * b, a.y * b, a.z * b, a.w * b); }
static __device__ __forceinline__ uint4     operator+   (const uint4& a, unsigned int b)   { return make_uint4(a.x + b, a.y + b, a.z + b, a.w + b); }
static __device__ __forceinline__ uint4     operator-   (const uint4& a, unsigned int b)   { return make_uint4(a.x - b, a.y - b, a.z - b, a.w - b); }
static __device__ __forceinline__ uint4     operator*   (unsigned int a, const uint4& b)   { return make_uint4(a * b.x, a * b.y, a * b.z, a * b.w); }
static __device__ __forceinline__ uint4     operator+   (unsigned int a, const uint4& b)   { return make_uint4(a + b.x, a + b.y, a + b.z, a + b.w); }
static __device__ __forceinline__ uint4     operator-   (unsigned int a, const uint4& b)   { return make_uint4(a - b.x, a - b.y, a - b.z, a - b.w); }

template<class T> static __device__ __forceinline__ T zero_value(void);
template<> __device__ __forceinline__ float  zero_value<float> (void)                      { return 0.f; }
template<> __device__ __forceinline__ float2 zero_value<float2>(void)                      { return make_float2(0.f, 0.f); }
template<> __device__ __forceinline__ float4 zero_value<float4>(void)                      { return make_float4(0.f, 0.f, 0.f, 0.f); }
static __device__ __forceinline__ float3 make_float3(const float2& a, float b)             { return make_float3(a.x, a.y, b); }
static __device__ __forceinline__ float4 make_float4(const float3& a, float b)             { return make_float4(a.x, a.y, a.z, b); }
static __device__ __forceinline__ float4 make_float4(const float2& a, const float2& b)     { return make_float4(a.x, a.y, b.x, b.y); }
static __device__ __forceinline__ int3 make_int3(const int2& a, int b)                     { return make_int3(a.x, a.y, b); }
static __device__ __forceinline__ int4 make_int4(const int3& a, int b)                     { return make_int4(a.x, a.y, a.z, b); }
static __device__ __forceinline__ int4 make_int4(const int2& a, const int2& b)             { return make_int4(a.x, a.y, b.x, b.y); }
static __device__ __forceinline__ uint3 make_uint3(const uint2& a, unsigned int b)         { return make_uint3(a.x, a.y, b); }
static __device__ __forceinline__ uint4 make_uint4(const uint3& a, unsigned int b)         { return make_uint4(a.x, a.y, a.z, b); }
static __device__ __forceinline__ uint4 make_uint4(const uint2& a, const uint2& b)         { return make_uint4(a.x, a.y, b.x, b.y); }

template<class T> static __device__ __forceinline__ void swap(T& a, T& b)                  { T temp = a; a = b; b = temp; }

//------------------------------------------------------------------------
// Triangle ID <-> float32 conversion functions to support very large triangle IDs.
//
// Values up to and including 16777216 (also, negative values) are converted trivially and retain
// compatibility with previous versions. Larger values are mapped to unique float32 that are not equal to
// the ID. The largest value that converts to float32 and back without generating inf or nan is 889192447.

#ifdef USE_HIP
static __device__ __forceinline__ unsigned int ballot_sync(volatile unsigned int* s_ballot, unsigned int mask, bool condition, int warp_size = 32) {
    // __ballot_sync
    auto active_threads = cooperative_groups::coalesced_threads();
    volatile unsigned int* s_ballot_offset = s_ballot + threadIdx.y * warp_size;
    s_ballot_offset[threadIdx.x] = condition ? 1 : 0;
    // __syncthreads();
    active_threads.sync();
    unsigned int ballot_mask = 0;
    for (int i = 0; i < warp_size; ++i) {
        if ((mask & (1 << i)) && s_ballot_offset[i]) {
            ballot_mask |= (1 << i);
        }
    }

    return ballot_mask;
}
static __device__ __forceinline__ bool all_sync(volatile unsigned int* s_ballot, unsigned int mask, bool condition, int warp_size = 32) {
    // __any_sync
    auto active_threads = cooperative_groups::coalesced_threads();
    volatile unsigned int* s_ballot_offset = s_ballot + threadIdx.y * warp_size;
    s_ballot_offset[threadIdx.x] = condition ? 1 : 0;
    // __syncthreads();
    active_threads.sync();

    bool all_true = true;
    for (int i = 0; i < warp_size; ++i) {
        if ((mask & (1 << i)) && !s_ballot_offset[i]) {
            all_true = false;
            break;
        }
    }

    return all_true;
}

static __device__ __forceinline__ int __hip_float_as_int(float x) {
    static_assert(sizeof(int) == sizeof(float), "");
    // int tmp;
    // __builtin_memcpy(&tmp, &x, sizeof(tmp));
    // return tmp;
    union {
        float f;
        int i;
    } u;
    u.f = x;
    return u.i;
}
static __device__ __forceinline__ float __hip_int_as_float(int x) {
    static_assert(sizeof(float) == sizeof(int), "");
    // float tmp;
    // __builtin_memcpy(&tmp, &x, sizeof(tmp));
    // return tmp;
    union {
        int i;
        float f;
    } u;
    u.i = x;
    return u.f;
}
static __device__ __forceinline__ int   float_to_triidx(float x) { if (x <= 16777216.f) return (int)x;   return __hip_float_as_int(x) - 0x4a800000; }
static __device__ __forceinline__ float triidx_to_float(int x)   { if (x <= 0x01000000) return (float)x; return __hip_int_as_float(0x4a800000 + x); }
#else
static __device__ __forceinline__ int   float_to_triidx(float x) { if (x <= 16777216.f) return (int)x;   return __float_as_int(x) - 0x4a800000; }
static __device__ __forceinline__ float triidx_to_float(int x)   { if (x <= 0x01000000) return (float)x; return __int_as_float(0x4a800000 + x); }
#endif

//------------------------------------------------------------------------
// Coalesced atomics. These are all done via macros.

#if __CUDA_ARCH__ >= 700 || defined(GFX942_SUPPORTED) // Warp match instruction __match_any_sync() is only available on compute capability 7.x and higher
#define CA_TEMP       _ca_temp
#define CA_SYNC_TEMP  s_ballot
#define CA_TEMP_PARAM float* CA_TEMP
#define CA_SYNC_TEMP_PARAM unsigned int* CA_SYNC_TEMP
#define CA_DECLARE_TEMP(threads_per_block) \
    __shared__ float CA_TEMP[(threads_per_block)]
#define CA_DECLARE_SYNC_TEMP(threads_per_block) \
    __shared__ unsigned int CA_SYNC_TEMP[threads_per_block]

#define CA_SET_GROUP_MASK(group, thread_mask, warp_size)                   \
    bool   _ca_leader;                                          \
    float* _ca_ptr;                                             \
    do {                                                        \
        int tidx   = threadIdx.x + blockDim.x * threadIdx.y;    \
        int lane   = tidx & 31;                                 \
        int warp   = tidx >> 5;                                 \
        auto active_threads = cooperative_groups::coalesced_threads();         \
        unsigned int* s_ballot_offset = s_ballot + threadIdx.y * warp_size;           \
        s_ballot_offset[threadIdx.x] = group;                                  \
        active_threads.sync();                                                 \
        int tmask = 0;                                                         \
        for (int i = 0; i < warp_size; ++i) {                                         \
            if ((thread_mask & (1 << i)) && (s_ballot_offset[i] == group)) {   \
                tmask |= (1 << i);                                             \
            }                                                                  \
        }                                                                      \
        int leader = __builtin_ffs(tmask) - 1;                  \
        _ca_leader = (leader == lane);                          \
        _ca_ptr    = &_ca_temp[((warp << 5) + leader)];         \
    } while(0)

#define CA_SET_GROUP(group, warp_size) \
    CA_SET_GROUP_MASK((group), 0xffffffffu, warp_size)

#define caAtomicAdd(ptr, value)         \
    do {                                \
        if (_ca_leader)                 \
            *_ca_ptr = 0.f;             \
        atomicAdd(_ca_ptr, (value));    \
        if (_ca_leader)                 \
            atomicAdd((ptr), *_ca_ptr); \
    } while(0)

#define caAtomicAdd3_xyw(ptr, x, y, w)  \
    do {                                \
        caAtomicAdd((ptr), (x));        \
        caAtomicAdd((ptr)+1, (y));      \
        caAtomicAdd((ptr)+3, (w));      \
    } while(0)

#define caAtomicAddTexture(ptr, level, idx, value, warp_size)  \
    do {                                            \
        CA_SET_GROUP((idx) ^ ((level) << 27), warp_size);      \
        caAtomicAdd((ptr)+(idx), (value));          \
    } while(0)

//------------------------------------------------------------------------
// Disable atomic coalescing for compute capability lower than 7.x

#else // __CUDA_ARCH__ >= 700
#define CA_TEMP _ca_temp
#define CA_TEMP_PARAM float CA_TEMP
#define CA_DECLARE_TEMP(threads_per_block) CA_TEMP_PARAM
#define CA_SET_GROUP_MASK(group, thread_mask)
#define CA_SET_GROUP(group)
#define caAtomicAdd(ptr, value) atomicAdd((ptr), (value))
#define caAtomicAdd3_xyw(ptr, x, y, w)  \
    do {                                \
        atomicAdd((ptr), (x));          \
        atomicAdd((ptr)+1, (y));        \
        atomicAdd((ptr)+3, (w));        \
    } while(0)
#define caAtomicAddTexture(ptr, level, idx, value) atomicAdd((ptr)+(idx), (value))
#endif // __CUDA_ARCH__ >= 700

//------------------------------------------------------------------------
#endif // __CUDACC__
