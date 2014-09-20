//
//  Utility.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 2/9/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "Utility.h"
#include <math.h>

namespace sinnca
{
	// C++ declarations
	
	// Numeric functions
	bool isEven(long i)
	{
		return (i % 2 == 0);
	}
	
	bool isOdd(long i)
	{
		return (i % 2 == 1);
	}
	
	long nextPowerOfTwo(long i)
	{
		int p = 1;
		
		while (p < i)
			p *= 2;
		
		return p;
	}
	
	float pathagoras(float a, float b)
	{
		// A-sq * B-sq = Csq
		return (powf(a, 2) * powf(b, 2));
	}
	
	void convertToPolar(float x, float y, float* r, float* a)
	{
		*r = sqrtf(pathagoras(x, y));
		*a = (tanf(x / y)) * -1;
	}
	void convertToCoord(float a, float r, float* x, float* y)
	{
		*x = cosf(a) * r;
		*y = sinf(a) * r;
	}
	
	// byte formating
	
	long toKilobyte(long b)
	{
		return b * 1024;
	}
	
	long toMegabyte(long b)
	{
		return b * 1048576;
	}
	
	long toGigabyte(long b)
	{
		return b * 1048576000;
	}
	
	float fromKilobyte(long b)
	{
		return b / 1024.0f;
	}
	
	float fromMegabyte(long b)
	{
		return b / 1048576.0f;
	}
	
	float fromGigabyte(long b)
	{
		return b / 1048576000.0f;
	}
	
	// endian swapping
	
	short endian16bit(short input)
	{
		short output;
		char* swap_a = (char*) &input;
		char* swap_b = (char*) &output;
		
		swap_b[0] = swap_a[1];
		swap_b[1] = swap_a[0];
		
		return output;
	}
	
	long endian32bit(long input)
	{
		long output;
		char* swap_a = (char*)&input;
		char* swap_b = (char*)&output;
		
		swap_b[0] = swap_a[2];
		swap_b[1] = swap_a[3];
		swap_b[2] = swap_a[0];
		swap_b[3] = swap_a[1];
		
		return output;
	}
	
}
