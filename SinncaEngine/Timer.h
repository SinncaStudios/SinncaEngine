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
		uint ref;
		
	public:
		
		static constexpr auto metatable = "timer";
		
		timer();
		~timer();
		
		void start();
		void pause();
		void resume();
		
		sinncaTime getTicks();
		
		void* operator new(size_t s, bool l = false);
		void operator delete(void* p);
		
	};
	
	
	void registerTimer(lua_State* L);

}
#endif
