//
//  RenderObj.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 2/17/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__RenderObj__
#define __SinncaEngine__RenderObj__

#include <iostream>
#include "i_graphics.h"

namespace sinnca
{
	class renderObj
	{
	protected:
		GLubyte* ind; // will be dynamic array
		GLuint vBuffer;
		GLuint iBuffer;
		
	public:
		
		renderObj()
		{
			//ind = NULL;
		}
		
		virtual void render() = 0;
	};
}

#endif /* defined(__SinncaEngine__RenderObj__) */
