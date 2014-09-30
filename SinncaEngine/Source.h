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
		
		source();
		~source();
		
		void setBuffer(buffer* b);
		void update();
		
		void play();
		void pause();
		void rewind();
		
	};
}

#endif /* defined(__SinncaEngine__Source__) */
