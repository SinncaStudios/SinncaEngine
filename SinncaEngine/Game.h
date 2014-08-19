//
//  Game.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 12/14/13.
//  Copyright (c) 2013 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__Game__
#define __SinncaEngine__Game__

#include <iostream>



namespace sinnca
{
	class game
	{
		
	public:
		
		unsigned int glW, glH;
		
		void startUp(const char* path = "");
		
		void loopItr();
		void mainLoop();
		
		void update();
		void render();
		
		void cleanUp();
		
	};
}

#endif /* defined(__SinncaEngine__Game__) */
