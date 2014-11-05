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
#include "Script.h"

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
		ALenum bufFormat;
		ALsizei frequency;
		ALsizei size;
		
		std::string name;
		
		buffer(std::string n);
		~buffer();
		
		int load(std::string p);
		ALuint getBuffer();
		
		void* operator new(size_t s, std::string n);
		void operator delete(void* p);
	};
	
	#define createBuffer(a) new(a)buffer(a)
	buffer* checkBuffer(int ind);
	
	void registerBuffer(lua_State* L);
}

#endif /* defined(__SinncaEngine__Buffer__) */
