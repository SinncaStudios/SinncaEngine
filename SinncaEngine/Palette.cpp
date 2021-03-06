//
//  Palette.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 7/16/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "Palette.h"
#include "Heap.h"

namespace sinnca
{
	palette* palette::_instance = NULL;
	palette* palette::Instance()
	{
		if (_instance == NULL)
		{
			//_instance = new graphics;
			_instance = Heap->allocateNew<palette>();
			
		}
		return _instance;
	}
	
	palette::palette()
	{
		// 0.1, 0.24, 0.4, 0
		defaultColor.r = 25;
		defaultColor.g = 61;
		defaultColor.b = 102;
		defaultColor.a = 255;
		
		white.r = 255;
		white.g = 255;
		white.b = 255;
		white.a = 255;
		
		black.r = 0;
		black.g = 0;
		black.b = 0;
		black.a = 255;
		
		blue.r = 0;
		blue.g = 0;
		blue.b = 255;
		blue.a = 255;
		
		red.r = 255;
		red.g = 0;
		red.b = 0;
		red.a = 255;
		
		yellow.r = 255;
		yellow.g = 240;
		yellow.b = 0;
		yellow.a = 255;
		
		green.r = 0;
		green.g = 220;
		green.b = 0;
		green.a = 255;
		
		
	}
	
}