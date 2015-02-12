//
//  Listener.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 9/27/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__Listener__
#define __SinncaEngine__Listener__

#include <iostream>
#include "Node.h"
#include "Audio.h"

namespace sinnca
{
	#define Listener (listener::Instance())
	class listener : public node
	{
		
		
	public:
		
		static constexpr auto metatable = "listener";
		
		listener();
		
		void update();
		void render();
		
		static listener* Instance();
		
	protected:
		
		static listener* _instance;
	};
}

#endif /* defined(__SinncaEngine__Listener__) */
