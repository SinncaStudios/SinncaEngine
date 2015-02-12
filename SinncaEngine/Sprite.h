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


namespace sinnca
{
	class sprite : public renderObj
	{
		
		
	public:
		
		sprite();
		~sprite();
		
		
		vertex vertices[4] = {
			{{0.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
			{{1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
			{{1.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
			{{0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
		};
		GLubyte newind[4];
		
		void render();
		vertex* getVertices();
		
	};
}

#endif /* defined(__SinncaEngine__Sprite__) */
