//
//  TimeKeeping.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 8/12/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__TimeKeeping__
#define __SinncaEngine__TimeKeeping__

#include "Timer.h"

namespace sinnca
{
	//#define TimeKeeper (timeKeeping::Instance())
	namespace TimeKeeper
	{
		
		extern float fps;
		extern sinncaTime deltaTicks;
		
		extern timer* t;
		
	//public:
		
		//static timeKeeping* Instance();
		
		void setup();
		void shutDown();
		void update();
		
		float withDeltaTime();
		sinncaTime getTicks();
		
	//protected:
		
		//static timeKeeping* _instance;
	};
}

#endif /* defined(__SinncaEngine__TimeKeeping__) */
