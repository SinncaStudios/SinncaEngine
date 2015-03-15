//
//  Display.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 3/3/15.
//  Copyright (c) 2015 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__Display__
#define __SinncaEngine__Display__


#include "Camera.h"

namespace sinnca
{
	class display
	{
		// width and height
		uint w, h;
		
		// refresh rate in hertz
		uint refereshRate;
		// bits per pixel
		int bpPixel;
		
		
		// is this display 3D naitive?
		bool naitive3D;
		// is this an ultra-resolution display?
		bool retina;
		
		// the camera object that sources what to draw
		camera* content;
		
	public:
		
		display(uint x, uint y);
		
		void setCamera(camera* c);
	};
}

#endif /* defined(__SinncaEngine__Display__) */
