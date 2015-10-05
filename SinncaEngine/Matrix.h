//
//  Matrix.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 5/2/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__Matrix__
#define __SinncaEngine__Matrix__

#include <iostream>

namespace sinnca
{
	// vector declarations
	struct v2
	{
		float x, y;
	};
	
	struct v3
	{
		float x, y, z;
	};
	
	struct v4
	{
		float x, y, z, w;
	};
	
	
	// matrix declarations
	struct m3
	{
		v3 m[3];
	};
	
	struct m4
	{
		v4 m[4];
	};
	
	
	// matrix math functions
	void copyMatrix(m4* destination, m3* first);
	void copyMatrix(m3* destination, m4* first);
	void copyMatrix(m4* destination, m4* first);
	
	void multiply(m4* destination, m4* first, m3* next);
	void multiply(m4* destination, m4* first, m4* next);
	
	void snLoadIdentity(m4* mat);
	void snOrthoMatrix(m4* destination, float left, float right, float up, float down, float near, float far);
	
	void snTranslateM4(m4* destination, m4* first, v3* next);
	void snRotateM4(m4* destination, m4* first, v4* next);
	void snScaleM4(m4* destination, m4* first, v3* next);
	
	bool invert(m4* mtx);
	void transpose(m4* destination);
}

#endif /* defined(__SinncaEngine__Matrix__) */
