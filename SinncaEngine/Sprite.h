//
//  Sprite.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 3/2/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__Sprite__
#define __SinncaEngine__Sprite__

#include <iostream>
#include "RenderObj.h"
#include "Vertex.h"

namespace sinnca
{
	class sprite : public renderObj
	{
		
		
	public:
		
		sprite();
		~sprite();
		
		const float POSITION[ 8 ] = {
			0.0f, 0.0f, // Down left (pivot point)
			1.0f, 0.0f, // Up left
			0.0f, 1.0f, // Down right
			1.0f, 1.0f  // Up right
		};
		
		vertex vertices[4] = {
			{{0.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
			{{1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
			{{1.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
			{{0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
		};
		GLubyte newind[4];
		
		void render();
		
	};
}

#endif /* defined(__SinncaEngine__Sprite__) */
