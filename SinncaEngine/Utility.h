//
//  Utility.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 11/21/13.
//  Copyright (c) 2013 Ryan Oldis. All rights reserved.
//

#ifndef SinncaEngine_Utility_h
#define SinncaEngine_Utility_h



namespace sinnca
{
	// C++ declarations
	const double pi = 3.1415926535897932389793238463;
	
	// Numeric functions
	bool isEven(long i);
	bool isOdd(long i);
	
	long nextPowerOfTwo(long i);
	
	float pathagoras(float a, float b);
	
	void convertToAngle(float x, float y, float* r, float* a);
	void convertToCoord(float a, float r, float* x, float* y);
	
	// byte formating
	
	long toKilobyte(long b);
	long toMegabyte(long b);
	long toGigabyte(long b);
	
	float fromKilobyte(long b);
	float fromMegabyte(long b);
	float fromGigabyte(long b);
	
	// endian swapping
	short endian16bit(short input);
	long endian32bit(long input);
	
	// Lua declarations
	
	// useful stuff
	#define ARRAYSIZE(a) (sizeof(a) / sizeof((a)[0]))
}


#endif
