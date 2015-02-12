//
//  Source.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 9/27/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__Source__
#define __SinncaEngine__Source__

#include <iostream>
#include "Node.h"
#include "Audio.h"
#include "Buffer.h"

namespace sinnca
{
	class source : public node
	{
		
		ALuint theSource;
		buffer* theBuffer;
		bool isPlaying;
		
	public:
		
		static constexpr auto metatable = "source";
		
		ALfloat pitch, gain;
		
		source(std::string n);
		~source();
		
		void setBuffer(buffer* b);
		void update();
		
		void play();
		void pause();
		void rewind();
		
		void* operator new(size_t s, std::string n);
		void operator delete(void* p);
		
	};
	
	#define createSource(a) new(a)source(a)
	
	void registerSource(lua_State* L);
	
}

#endif /* defined(__SinncaEngine__Source__) */
