//
//  Buffer.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 9/27/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__Buffer__
#define __SinncaEngine__Buffer__

#include <iostream>
#include "Audio.h"

namespace sinnca
{
	class buffer
	{
		ALuint theBuffer;
		
		int loadWAV(std::string path);
		int loadOGG(std::string path);
		int loadAIFF(std::string path);
		int loadMIDI(std::string path);
		int loadSNW(std::string path);
		
		//int loadMP3(std::string path); // maybe...
		
	public:
		
		bool loops;
		
		buffer();
		~buffer();
		
		int load(std::string path);
	};
}

#endif /* defined(__SinncaEngine__Buffer__) */
