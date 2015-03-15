//
//  RapidPress.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 2/18/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "RapidPress.h"
#include "TimeKeeping.h"

namespace sinnca
{
	rapidPress::rapidPress() :
	frequency(350),
	durration(0)
	{
		
	}
	
	void rapidPress::update()
	{
		if(cause->didChange == true && cause->x > 0.0f)
		{
			isWatching = true;
			
			durration = TimeKeeper::getTicks();
			wasCaused = true;
			timesPressed++;
			
			if((TimeKeeper::getTicks() - durration) > frequency)
			{
				// the player has held the button
				isWatching = false;
				durration = 0;
				wasCaused = false;
				timesPressed = 0;
			}
		}
		
		if(isWatching)
		{
			if((TimeKeeper::getTicks() - durration) > frequency)
			{
				// the player has stopped rappidly pressing the button
				isWatching = false;
				durration = 0;
				wasCaused = false;
				timesPressed = 0;
			}
		}
	
	
	}
}