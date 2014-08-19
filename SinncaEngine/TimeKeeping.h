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
	#define TimeKeeper (timeKeeping::Instance())
	class timeKeeping : public timer
	{
		
		float fps;
		sinncaTime deltaTicks;
		
	public:
		
		static timeKeeping* Instance();
		
		timeKeeping();
		void update();
		
		float withDeltaTime();
		
	protected:
		
		static timeKeeping* _instance;
	};
}

#endif /* defined(__SinncaEngine__TimeKeeping__) */
