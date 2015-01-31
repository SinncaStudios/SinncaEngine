//
//  ButtonHold.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 12/19/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "ButtonHold.h"

namespace sinnca
{
	void buttonHold::update()
	{
		if (cause->x > 0.0)
		{
			if (cause->didChange)
			{
				durration = TimeKeeper->getTicks();
			}
			
			if ((TimeKeeper->getTicks() - durration) <= durration)
			{
				if (effect)
				{
					effect->call();
					wasCaused = true;
					return;
				}
			}
			wasCaused = false;
		}
		wasCaused = false;
	}
}