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
#include "Asset.h"

namespace sinnca
{
	class buffer : public asset
	{
		ALuint theBuffer;
		
		int loadWAV(std::string path);
		int loadOGG(std::string path);
		int loadAIFF(std::string path);
		int loadMIDI(std::string path);
		int loadSNW(std::string path);
		
		//int loadMP3(std::string path); // maybe...
		
	public:
		
		static constexpr auto metatable = "buffer";
		
		bool loops;
		ALenum bufFormat;
		ALsizei frequency;
		ALsizei size;
		
		std::string name;
		
		buffer();
		~buffer();
		
		void load(std::string p);
		ALuint getBuffer();
		
		void* operator new(size_t s);
		void operator delete(void* p);
	};
	
	buffer* checkBuffer(int ind);
	
	void registerBuffer(lua_State* L);
}

#endif /* defined(__SinncaEngine__Buffer__) */
