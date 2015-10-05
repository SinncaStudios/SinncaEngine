//
//  Matrix.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 5/2/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "Matrix.h"
#include <math.h>

namespace sinnca
{
	void copyMatrix(m4* destination, m3* first)
	{
		memcpy(&destination->m[0], &first->m[0], sizeof(v3));
		memcpy(&destination->m[1], &first->m[1], sizeof(v3));
		memcpy(&destination->m[2], &first->m[2], sizeof(v3));
	}
	void copyMatrix(m3* destination, m4* first)
	{
		memcpy(&destination->m[0], &first->m[0], sizeof(v3));
		memcpy(&destination->m[1], &first->m[1], sizeof(v3));
		memcpy(&destination->m[2], &first->m[2], sizeof(v3));
	}
	void copyMatrix(m4* destination, m4* first)
	{
		memcpy(destination, first, sizeof(m4));
	}
	
	void multiply(m4* destination, m4* first, m3* next)
	{
		m3 matrix;
		
		matrix.m[0].x = first->m[0].x * next->m[0].x + first->m[1].x * next->m[0].y + first->m[2].x * next->m[0].z;
		matrix.m[0].y = first->m[0].y * next->m[0].x + first->m[1].y * next->m[0].y + first->m[2].y * next->m[0].z;
		matrix.m[0].z = first->m[0].z * next->m[0].x + first->m[1].z * next->m[0].y + first->m[2].z * next->m[0].z;
		
		matrix.m[1].x = first->m[0].x * next->m[1].x + first->m[1].x * next->m[1].y + first->m[2].x * next->m[1].z;
		matrix.m[1].y = first->m[0].y * next->m[1].x + first->m[1].y * next->m[1].y + first->m[2].y * next->m[1].z;
		matrix.m[1].z = first->m[0].z * next->m[1].x + first->m[1].z * next->m[1].y + first->m[2].z * next->m[1].z;
		
		matrix.m[2].x = first->m[0].x * next->m[2].x + first->m[1].x * next->m[2].y + first->m[2].x * next->m[2].z;
		matrix.m[2].y = first->m[0].y * next->m[2].x + first->m[1].y * next->m[2].y + first->m[2].y * next->m[2].z;
		matrix.m[2].z = first->m[0].z * next->m[2].x + first->m[1].z * next->m[2].y + first->m[2].z * next->m[2].z;
		
		copyMatrix(destination, &matrix);
	}
	void multiply(m4* destination, m4* first, m4* next)
	{
		m4 matrix;
		
		matrix.m[0].x = first->m[0].x * next->m[0].x + first->m[1].x * next->m[0].y + first->m[2].x * next->m[0].z + first->m[3].x * next->m[0].w;
		matrix.m[0].y = first->m[0].y * next->m[0].x + first->m[1].y * next->m[0].y + first->m[2].y * next->m[0].z + first->m[3].y * next->m[0].w;
		matrix.m[0].z = first->m[0].z * next->m[0].x + first->m[1].z * next->m[0].y + first->m[2].z * next->m[0].z + first->m[3].z * next->m[0].w;
		matrix.m[0].w = first->m[0].w * next->m[0].x + first->m[1].w * next->m[0].y + first->m[2].w * next->m[0].z + first->m[3].w * next->m[0].w;
		
		matrix.m[1].x = first->m[0].x * next->m[1].x + first->m[1].x * next->m[1].y + first->m[2].x * next->m[1].z + first->m[3].x * next->m[1].w;
		matrix.m[1].y = first->m[0].y * next->m[1].x + first->m[1].y * next->m[1].y + first->m[2].y * next->m[1].z + first->m[3].y * next->m[1].w;
		matrix.m[1].z = first->m[0].z * next->m[1].x + first->m[1].z * next->m[1].y + first->m[2].z * next->m[1].z + first->m[3].z * next->m[1].w;
		matrix.m[1].w = first->m[0].w * next->m[1].x + first->m[1].w * next->m[1].y + first->m[2].w * next->m[1].z + first->m[3].w * next->m[1].w;
		
		matrix.m[2].x = first->m[0].x * next->m[2].x + first->m[1].x * next->m[2].y + first->m[2].x * next->m[2].z + first->m[3].x * next->m[2].w;
		matrix.m[2].y = first->m[0].y * next->m[2].x + first->m[1].y * next->m[2].y + first->m[2].y * next->m[2].z + first->m[3].y * next->m[2].w;
		matrix.m[2].z = first->m[0].z * next->m[2].x + first->m[1].z * next->m[2].y + first->m[2].z * next->m[2].z + first->m[3].z * next->m[2].w;
		matrix.m[2].w = first->m[0].w * next->m[2].x + first->m[1].w * next->m[2].y + first->m[2].w * next->m[2].z + first->m[3].w * next->m[2].w;
		
		matrix.m[3].x = first->m[0].x * next->m[3].x + first->m[1].x * next->m[3].y + first->m[2].x * next->m[3].z + first->m[3].x * next->m[3].w;
		matrix.m[3].y = first->m[0].y * next->m[3].x + first->m[1].y * next->m[3].y + first->m[2].y * next->m[3].z + first->m[3].y * next->m[3].w;
		matrix.m[3].z = first->m[0].z * next->m[3].x + first->m[1].z * next->m[3].y + first->m[2].z * next->m[3].z + first->m[3].z * next->m[3].w;
		matrix.m[3].w = first->m[0].w * next->m[3].x + first->m[1].w * next->m[3].y + first->m[2].w * next->m[3].z + first->m[3].w * next->m[3].w;
		
		copyMatrix(destination, &matrix);
	}
	
	
	
	void snLoadIdentity(m4* matrix)
	{
		memset(&matrix[0], 0, sizeof(m4));
		
		matrix->m[0].x = 1.0f;
		matrix->m[1].y = 1.0f;
		matrix->m[2].z = 1.0f;
		matrix->m[3].w = 1.0f;
	}
	void snOrthoMatrix(m4* destination, float right, float left, float down, float up, float near, float far)
	{
		m4 matrix;
		
		matrix.m[0].x = 2.0f / (right - left);
		matrix.m[1].x = 0.0f;
		matrix.m[2].x = 0.0f;
		matrix.m[3].x = -(right + left) / (right - left);
		
		matrix.m[0].y = 0.0f;
		matrix.m[1].y = 2.0f / (up - down);
		matrix.m[2].y = 0.0f;
		matrix.m[3].y = -(up + down) / (up - down);
		
		matrix.m[0].z = 0.0f;
		matrix.m[1].z = 0.0f;
		matrix.m[2].z = -2.0f / (far - near);
		matrix.m[3].z = -(far + near) / (far - near);
		
		matrix.m[0].w = 0.0f;
		matrix.m[1].w = 0.0f;
		matrix.m[2].w = 0.0f;
		matrix.m[3].w = 1.0f;
		
		
		multiply(destination, destination, &matrix);
	}
	
	
	
	void snTranslateM4(m4* destination, m4* first, v3* next)
	{
		destination->m[3].x = first->m[0].x * next->x + first->m[1].x * next->y + first->m[2].x * next->z + first->m[3].x;
		destination->m[3].y = first->m[0].y * next->x + first->m[1].y * next->y + first->m[2].y * next->z + first->m[3].y;
		destination->m[3].z = first->m[0].z * next->x + first->m[1].z * next->y + first->m[2].z * next->z + first->m[3].z;
		destination->m[3].w = first->m[0].w * next->x + first->m[1].w * next->y + first->m[2].w * next->z + first->m[3].w;
	}
	void snRotateM4(m4* destination, m4* first, v4* next)
	{
		
	}
	void snScaleM4(m4* destination, m4* first, v3* next)
	{
		destination->m[0].x = first->m[0].x * next->x;
		destination->m[0].y = first->m[0].y * next->x;
		destination->m[0].z = first->m[0].z * next->x;
		destination->m[0].w = first->m[0].w * next->x;
		
		destination->m[1].x = first->m[1].x * next->y;
		destination->m[1].y = first->m[1].y * next->y;
		destination->m[1].z = first->m[1].z * next->y;
		destination->m[1].w = first->m[1].w * next->y;
		
		destination->m[2].x = first->m[2].x * next->z;
		destination->m[2].y = first->m[2].y * next->z;
		destination->m[2].z = first->m[2].z * next->z;
		destination->m[2].w = first->m[2].w * next->z;
	}
	
	
	bool invert(m4* mtx)
	{
		m4 final;
		float determinant;
		
		// first... no 0th places, and...
		// no "X"s
		final.m[0].x = mtx->m[1].y * mtx->m[2].z * mtx->m[3].w -
					   mtx->m[1].y * mtx->m[2].w * mtx->m[3].z -
					   mtx->m[2].y * mtx->m[1].z * mtx->m[3].w +
					   mtx->m[2].y * mtx->m[1].w * mtx->m[3].z +
					   mtx->m[3].y * mtx->m[1].z * mtx->m[2].w -
					   mtx->m[3].y * mtx->m[1].w * mtx->m[2].z;
		
		// no "Y"s
		final.m[1].x = mtx->m[1].x * mtx->m[2].z * mtx->m[3].w -
					   mtx->m[1].x * mtx->m[2].w * mtx->m[3].z -
					   mtx->m[2].x * mtx->m[1].z * mtx->m[3].w +
					   mtx->m[2].x * mtx->m[1].w * mtx->m[3].z +
					   mtx->m[3].x * mtx->m[1].z * mtx->m[2].w -
					   mtx->m[3].x * mtx->m[1].w * mtx->m[2].z;
		
		// no "Z"s
		final.m[2].x = mtx->m[1].x * mtx->m[2].y * mtx->m[3].w -
					   mtx->m[1].x * mtx->m[2].w * mtx->m[3].y -
					   mtx->m[2].x * mtx->m[1].y * mtx->m[3].w +
					   mtx->m[2].x * mtx->m[1].w * mtx->m[3].y +
					   mtx->m[3].x * mtx->m[1].y * mtx->m[2].w -
					   mtx->m[3].x * mtx->m[1].w * mtx->m[2].y;
		
		// no "W"s
		final.m[3].x = mtx->m[1].x * mtx->m[2].y * mtx->m[3].z -
					   mtx->m[1].x * mtx->m[2].z * mtx->m[3].y -
					   mtx->m[2].x * mtx->m[1].y * mtx->m[3].z +
					   mtx->m[2].x * mtx->m[1].z * mtx->m[3].y +
					   mtx->m[3].x * mtx->m[1].y * mtx->m[2].z -
					   mtx->m[3].x * mtx->m[1].z * mtx->m[2].y;
		
		// ...then no 1st places, and...
		// no "X"s
		final.m[0].y = mtx->m[0].y * mtx->m[2].z * mtx->m[3].w -
						mtx->m[0].y * mtx->m[2].w * mtx->m[3].z -
						mtx->m[2].y * mtx->m[0].z * mtx->m[3].w +
						mtx->m[2].y * mtx->m[0].w * mtx->m[3].z +
						mtx->m[3].y * mtx->m[0].z * mtx->m[2].w -
						mtx->m[3].y * mtx->m[0].w * mtx->m[2].z;
		
		// no "Y"s
		final.m[1].y = mtx->m[0].x * mtx->m[2].z * mtx->m[3].w -
						mtx->m[0].x * mtx->m[2].w * mtx->m[3].z -
						mtx->m[2].x * mtx->m[0].z * mtx->m[3].w +
						mtx->m[2].x * mtx->m[0].w * mtx->m[3].z +
						mtx->m[3].x * mtx->m[0].z * mtx->m[2].w -
						mtx->m[3].x * mtx->m[0].w * mtx->m[2].z;
		
		// no "Z"s
		final.m[2].y = mtx->m[0].x * mtx->m[2].y * mtx->m[3].w -
						mtx->m[0].x * mtx->m[2].w * mtx->m[3].y -
						mtx->m[2].x * mtx->m[0].y * mtx->m[3].w +
						mtx->m[2].x * mtx->m[0].w * mtx->m[3].y +
						mtx->m[3].x * mtx->m[0].y * mtx->m[2].w -
						mtx->m[3].x * mtx->m[0].w * mtx->m[2].y;
		
		// no "W"s
		final.m[3].y = mtx->m[0].x * mtx->m[2].y * mtx->m[3].z -
						mtx->m[0].x * mtx->m[2].z * mtx->m[3].y -
						mtx->m[2].x * mtx->m[0].y * mtx->m[3].z +
						mtx->m[2].x * mtx->m[0].z * mtx->m[3].y +
						mtx->m[3].x * mtx->m[0].y * mtx->m[2].z -
						mtx->m[3].x * mtx->m[0].z * mtx->m[2].y;
		
		// ...then no 3rd places, and...
		// no "X"s
		final.m[0].y = mtx->m[0].y * mtx->m[1].z * mtx->m[3].w -
						mtx->m[0].y * mtx->m[1].w * mtx->m[3].z -
						mtx->m[1].y * mtx->m[0].z * mtx->m[3].w +
						mtx->m[1].y * mtx->m[0].w * mtx->m[3].z +
						mtx->m[3].y * mtx->m[0].z * mtx->m[1].w -
						mtx->m[3].y * mtx->m[0].w * mtx->m[1].z;
		
		// no "Y"s
		final.m[1].y = mtx->m[0].x * mtx->m[1].z * mtx->m[3].w -
						mtx->m[0].x * mtx->m[1].w * mtx->m[3].z -
						mtx->m[1].x * mtx->m[0].z * mtx->m[3].w +
						mtx->m[1].x * mtx->m[0].w * mtx->m[3].z +
						mtx->m[3].x * mtx->m[0].z * mtx->m[1].w -
						mtx->m[3].x * mtx->m[0].w * mtx->m[1].z;
		
		// no "Z"s
		final.m[2].y = mtx->m[0].x * mtx->m[1].y * mtx->m[3].w -
						mtx->m[0].x * mtx->m[1].w * mtx->m[3].y -
						mtx->m[1].x * mtx->m[0].y * mtx->m[3].w +
						mtx->m[1].x * mtx->m[0].w * mtx->m[3].y +
						mtx->m[3].x * mtx->m[0].y * mtx->m[1].w -
						mtx->m[3].x * mtx->m[0].w * mtx->m[1].y;
		
		// no "W"s
		final.m[3].y = mtx->m[0].x * mtx->m[1].y * mtx->m[3].z -
						mtx->m[0].x * mtx->m[1].z * mtx->m[3].y -
						mtx->m[1].x * mtx->m[0].y * mtx->m[3].z +
						mtx->m[1].x * mtx->m[0].z * mtx->m[3].y +
						mtx->m[3].x * mtx->m[0].y * mtx->m[1].z -
						mtx->m[3].x * mtx->m[0].z * mtx->m[1].y;
		
		// ...then no 4th places, and...
		// no "X"s
		final.m[0].y = mtx->m[0].y * mtx->m[1].z * mtx->m[2].w -
						mtx->m[0].y * mtx->m[1].w * mtx->m[2].z -
						mtx->m[1].y * mtx->m[0].z * mtx->m[2].w +
						mtx->m[1].y * mtx->m[0].w * mtx->m[2].z +
						mtx->m[2].y * mtx->m[0].z * mtx->m[1].w -
						mtx->m[2].y * mtx->m[0].w * mtx->m[1].z;
		
		// no "Y"s
		final.m[1].y = mtx->m[0].x * mtx->m[1].z * mtx->m[2].w -
						mtx->m[0].x * mtx->m[1].w * mtx->m[2].z -
						mtx->m[1].x * mtx->m[0].z * mtx->m[2].w +
						mtx->m[1].x * mtx->m[0].w * mtx->m[2].z +
						mtx->m[2].x * mtx->m[0].z * mtx->m[1].w -
						mtx->m[2].x * mtx->m[0].w * mtx->m[1].z;
		
		// no "Z"s
		final.m[2].y = mtx->m[0].x * mtx->m[1].y * mtx->m[2].w -
						mtx->m[0].x * mtx->m[1].w * mtx->m[2].y -
						mtx->m[1].x * mtx->m[0].y * mtx->m[2].w +
						mtx->m[1].x * mtx->m[0].w * mtx->m[2].y +
						mtx->m[2].x * mtx->m[0].y * mtx->m[1].w -
						mtx->m[2].x * mtx->m[0].w * mtx->m[1].y;
		
		// no "W"s
		final.m[3].y = mtx->m[0].x * mtx->m[1].y * mtx->m[2].z -
						mtx->m[0].x * mtx->m[1].z * mtx->m[2].y -
						mtx->m[1].x * mtx->m[0].y * mtx->m[2].z +
						mtx->m[1].x * mtx->m[0].z * mtx->m[2].y +
						mtx->m[2].x * mtx->m[0].y * mtx->m[1].z -
						mtx->m[2].x * mtx->m[0].z * mtx->m[1].y;
		
		// now that that's out of the way...
		determinant = mtx->m[0].x * final.m[0].x +
					  mtx->m[0].y * final.m[1].x +
					  mtx->m[0].z * final.m[2].x +
					  mtx->m[0].w * final.m[3].x;
		
		if (determinant == 0)
			return false;
		
		determinant = 1.0f / determinant;
		
		final.m[0].x *= determinant;
		final.m[0].y *= determinant;
		final.m[0].z *= determinant;
		final.m[0].w *= determinant;
		
		final.m[1].x *= determinant;
		final.m[1].y *= determinant;
		final.m[1].z *= determinant;
		final.m[1].w *= determinant;
		
		final.m[2].x *= determinant;
		final.m[2].y *= determinant;
		final.m[2].z *= determinant;
		final.m[2].w *= determinant;
		
		final.m[3].x *= determinant;
		final.m[3].y *= determinant;
		final.m[3].z *= determinant;
		final.m[3].w *= determinant;
		
		copyMatrix(mtx, &final);
		
		return true;
	}
	
	void transpose(m4* destination)
	{
		/*
		 | a b c d |
		 | e f g h |
		 | i j k l |
		 | m n o p |
		*/
		
		// spots a, f, k, and p are going to be left alone
		float temp;
		
		// switch e and b
		temp = destination->m[0].y;
		destination->m[0].y = destination->m[1].x;
		destination->m[1].x = temp;
		
		// switch i and c
		temp = destination->m[0].z;
		destination->m[0].z = destination->m[2].x;
		destination->m[2].x = temp;
		
		// switch m and d
		temp = destination->m[0].w;
		destination->m[0].w = destination->m[3].x;
		destination->m[3].x = temp;
		
		// switch j and g
		temp = destination->m[1].z;
		destination->m[1].z = destination->m[2].y;
		destination->m[2].y = temp;
		
		// switch n and h
		temp = destination->m[1].w;
		destination->m[1].w = destination->m[3].y;
		destination->m[3].y = temp;
		
		// switch o and l
		temp = destination->m[2].w;
		destination->m[2].w = destination->m[3].z;
		destination->m[3].z = temp;
		
		// and done!
	}
	
}
