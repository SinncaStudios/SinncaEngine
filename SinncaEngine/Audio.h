//
//  Audio.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 9/27/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__Audio__
#define __SinncaEngine__Audio__

#include <iostream>
#include <OpenAL/al.h>
#include <OpenAL/alc.h>

namespace sinnca
{
	
	#define Audio (audio::Instance())
	class audio
	{
		ALCdevice* device;
		ALCcontext* context;

	public:
		
		~audio();
		
		void setup();
		
		static audio* Instance();
		
	protected:
		
		static audio* _instance;
		
	};
}

#endif /* defined(__SinncaEngine__Audio__) */
