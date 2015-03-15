//
//  RapidPress.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 2/18/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__RapidPress__
#define __SinncaEngine__RapidPress__

#include "InputWatcher.h"
#include "Timer.h"

namespace sinnca
{
	class rapidPress : public inputWatcher
	{
		bool isWatching;
		uint frequency;
		ui64 timesPressed;
		
		sinncaTime durration;
		
	public:
		
		rapidPress();
		void update();
	};
}

#endif /* defined(__SinncaEngine__RapidPress__) */
