//
//  LightTap.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 12/19/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__LightTap__
#define __SinncaEngine__LightTap__

#include "InputWatcher.h"
#include "Timer.h"

namespace sinnca
{
	class lightTap : public inputWatcher
	{
		sinncaTime durration;
		
	public:
		
		
		void update();
		
	};
	
	
	void registerLightTap(lua_State* L);
}

#endif /* defined(__SinncaEngine__LightTap__) */
