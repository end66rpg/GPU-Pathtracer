#pragma once
// This file contains things that are shared between the CUDA files and the C++ files

// Screen related
#define SCREEN_WIDTH  904
#define SCREEN_HEIGHT 600

#define PIXEL_COUNT (SCREEN_WIDTH * SCREEN_HEIGHT)

#define BLOCK_WIDTH  8
#define BLOCK_HEIGHT 4
#define BLOCK_SIZE   (BLOCK_WIDTH * BLOCK_HEIGHT)

static_assert(SCREEN_WIDTH  % BLOCK_WIDTH  == 0, "Screen width  should be divisible by the Block width!");
static_assert(SCREEN_HEIGHT % BLOCK_HEIGHT == 0, "Screen height should be divisible by the Block height!");
static_assert(BLOCK_SIZE == 32, "Block size should equal CUDA warp size!");

// Tracing related
#define EPSILON 0.001f

#define NUM_BOUNCES 5

// SVGF
#define ATROUS_ITERATIONS 4

#define ALPHA_COLOUR 0.2f
#define ALPHA_MOMENT 0.2f

#define SIGMA_Z 1.0f
#define SIGMA_N 128.0f
#define SIGMA_L 400.0f

// Pi related
#define PI          3.14159265359f
#define ONE_OVER_PI 0.31830988618f

#define TWO_PI          6.28318530718f
#define ONE_OVER_TWO_PI 0.15915494309f

// Material related
#define MAX_MATERIALS 128
#define MAX_TEXTURES  32

// BVH related
#define BVH_AXIS_X_BITS (0b01 << 30)
#define BVH_AXIS_Y_BITS (0b10 << 30)
#define BVH_AXIS_Z_BITS (0b11 << 30)
#define BVH_AXIS_MASK   (0b11 << 30)

#define MBVH_WIDTH 4
static_assert(MBVH_WIDTH >= 2, "MBVH tree must be at least binary");
