//
//  Camera.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 2/10/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "Camera.h"
#include "Graphics.h"
#include "Heap.h"

namespace sinnca
{
	
	camera::camera()
	{
		pos.x = 0.0f;
		pos.y = 0.0f;
		pos.z = 0.0f;
		
		
		zoom.x = 1.0f;
		zoom.y = 1.0f;
		zoom.z = 45.0f;
		
		// 3D off by default
		current3D = none;
	}
	camera::~camera()
	{
		
	}
	
	void camera::look()
	{
		
	}
	
	void camera::look2D()
	{
		Graphics::setMatrixMode(SINNCA_PROJECTION_MATRIX);
		// move camera
		Graphics::move(pos);
		
		// zoom is taking z and putting in in the x and y
		Graphics::scale(zoom.x, zoom.x, 0.0);
		
		// put the modelview back
		Graphics::setMatrixMode(SINNCA_MODELVIEW_MATRIX);
	}
	
	void camera::render()
	{
		for (linkList<node*>::iterator i = children.begin(); i != children.end(); ++i)
		{
			(*i)->render();
		}
	}
	
}