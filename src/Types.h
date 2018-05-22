#ifndef TYPES_H
#define TYPES_H

#include <string>

#include <cassert>
#include <cstdint>
#include <iostream>

#define PI 3.14159265

typedef int32_t i32;
typedef uint32_t u32;
typedef float f32;
typedef double f64;

const int32_t cSize = 80; //ToDo: a gameconfig
const int32_t cDepth = 4; 

struct Margins{
	i32 top;
	i32 right;
	i32 bottom;
	i32 left;
};

struct Condition{
	std::string player;
	std::string building;
	std::string condition;
	i32 value;
};

#endif