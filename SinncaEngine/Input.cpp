//
//  Input.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 2/12/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "Input.h"
#include "Heap.h"


namespace sinnca
{
	namespace Input
	{
		ui8 noOfInputsChanged = 0;
		InputType* inputsChanged[20];
		uint tapLimit = 500;
		
		namespace Keyboard
		{
			digitalButton keys[322];
		}
		
		namespace Mouse
		{
			uint x, y;
			digitalButton left, middle, right;
			
			analogButton pressure;
		}
		
		namespace Touch
		{
			float magnify;
			float rotation;
			float swipeX, swipeY;
		}
		
		void setup()
		{
			
			
			for (int i = 0; i < 322; i++)
			{
				Keyboard::keys[i].x = 0.0f;
			}
			
			setupKeys();
		}
		
		void shutDown()
		{
			
		}
		
		void update()
		{
			
			
			noOfInputsChanged = 0;
			for (int i = 0; i < 20; i++)
			{
				inputsChanged[i] = nullptr;
			}
		}
		
		void sendKeyDown(int k)
		{
			Keyboard::keys[k].x = 1.0f;
			Keyboard::keys[k].didChange = true;
			
			inputsChanged[noOfInputsChanged] = &Keyboard::keys[k];
			noOfInputsChanged++;
		}
		void sendKeyUp(int k)
		{
			Keyboard::keys[k].x = 0.0f;
			Keyboard::keys[k].didChange = true;
			
			inputsChanged[noOfInputsChanged] = &Keyboard::keys[k];
			noOfInputsChanged++;
		}
	}
	
	int l_keyDown(lua_State* L)
	{
		
		
		int a = (int)lua_tointeger(L, -1);
		lua_pushnumber(L, Input::Keyboard::keys[a].x);
		
		return 1;
	}
}