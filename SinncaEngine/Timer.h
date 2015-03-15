//
//  Timer.h
//  Sinnca Engine
//
//  Created by Ryan Oldis on 2/21/12.
//  Copyright (c) 2012 Sinnca Studios. All rights reserved.
//

#ifndef Sinnca_Engine_Timer_h
#define Sinnca_Engine_Timer_h

#include <iostream>
#include "Platform.h"

#ifdef snApple
#include <CoreFoundation/CFDate.h>
typedef CFTimeInterval sinncaTime;

#elif snWindows
typedef uint sinncaTime;

#elif snLinux
typedef uint sinncaTime;

#endif


#include "Script.h"

namespace sinnca
{
	
	class timer
	{
		sinncaTime startTicks, pauseTicks;
		
		bool started, paused;
		std::string name;
		
	public:
		timer();
		void setName(std::string n);
		
		void start();
		void pause();
		void resume();
		
		sinncaTime getTicks();
		
	};
	
	
	void registerTimer(lua_State* L);

}
#endif
