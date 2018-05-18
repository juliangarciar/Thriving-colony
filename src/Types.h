#ifndef TYPES_H
#define TYPES_H

#include <string>

#include <cstdint>
#include <iostream>

typedef int32_t i32;
typedef uint32_t u32;
typedef float f32;
const int32_t cSize = 80;

struct Margins{
	i32 top;
	i32 right;
	i32 bottom;
	i32 left;
};

#endif