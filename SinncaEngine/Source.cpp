//
//  Source.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 9/27/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "Source.h"


namespace sinnca
{
	source::source()
	{
		alGenSources(1, &theSource);
	}
	
	source::~source()
	{
		alDeleteSources(1, &theSource);
	}
	
	void source::update()
	{
		
	}
	
	void source::play()
	{
		if (!isPlaying)
		{
			isPlaying = true;
			alSourcePlay(theSource);
		}
	}
}

