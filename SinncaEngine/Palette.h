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
#define Palette (palette::Instance())
	class palette
	{
		
	public:
		
		static palette* Instance();
		palette();
		
		color defaultColor;
		
		color white;
		color black;
		color blue;
		color red;
		color yellow;
		color green;
		
	protected:
		static palette* _instance;
		
	};
}


#endif /* defined(__SinncaEngine__Palette__) */
