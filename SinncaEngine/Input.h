//
//  Input.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 2/12/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__Input__
#define __SinncaEngine__Input__

#include <iostream>
#include "Types.h"
#include "Script.h"

namespace sinnca
{
	
	struct mse
	{
		unsigned int x, y;
		
		bool left, right, middle, scrollUp, scrollDown;
	};
	
#define Input (input::Instance())
	class input
	{
		// there will be room for 512 keys!
		//ui64 keyArray;
		
		
	public:
		bool keyArray[322];
		mse Mouse;
		
		input();
		~input();
		
		void setupKeys();
		void update();
		
		void sendKeyDown(int k);
		void sendKeyUp(int k);
		
		static input* Instance();
		
	protected:
		
		static input* _instance;
	};
	
	int l_keyDown(lua_State* L);
}

#endif /* defined(__SinncaEngine__Input__) */
