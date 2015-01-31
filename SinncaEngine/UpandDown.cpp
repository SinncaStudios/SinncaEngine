//
//  UpandDown.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 12/19/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "UpandDown.h"

namespace sinnca
{
	void upAndDown::setOtherEffect(action *a)
	{
		otherEffect = a;
	}
	
	void upAndDown::update()
	{
		if (cause->didChange)
		{
			if (cause->x == 0.0f)
			{
				wasCaused = true;
				wasUp = true;
				
				if (otherEffect)
				{
					otherEffect->call();
				}
				
			} else if (cause->x > 0.0f)
			{
				wasCaused = true;
				wasDown = true;
				
				if (effect)
				{
					effect->call();
				}
			}
			
		}
		
		wasDown = false;
		wasUp = false;
		wasCaused = false;
	}
}