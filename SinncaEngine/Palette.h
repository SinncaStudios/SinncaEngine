//
//  Palette.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 7/16/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__Palette__
#define __SinncaEngine__Palette__

#include "Color.h"

namespace sinnca
{
	
	namespace Palette
	{
		
		inline void addColor(std::string n, color* c);
		
		
		void setup();
		
		extern color defaultColor;
		
		extern color white;
		extern color black;
		extern color blue;
		extern color red;
		extern color yellow;
		extern color green;
		
	};
}


#endif /* defined(__SinncaEngine__Palette__) */
