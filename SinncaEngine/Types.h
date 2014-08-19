//
//  Types.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 11/7/13.
//  Copyright (c) 2013 Ryan Oldis. All rights reserved.
//

#ifndef SinncaEngine_Types_h
#define SinncaEngine_Types_h

#include <cstdint>
//#include "MemoryManager.h"

typedef unsigned int uint;
typedef unsigned long ulong;

typedef unsigned char raw;

typedef int8_t i8;
typedef u_int8_t ui8;
typedef int16_t i16;
typedef u_int16_t ui16;
typedef int32_t i32;
typedef u_int32_t ui32;
typedef int64_t i64;
typedef u_int64_t ui64;


struct point
{
	float x = 0.0f, y = 0.0f, z = 0.0f;
};
struct texCoord
{
	float u = 0.0f, v = 0.0f;
};

typedef float celcius;
typedef float fahrenhiet;


#endif
