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
			float prevKeyState[322];
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
			Script::newBlankTable();
			
			for (int i = 0; i < 322; i++)
			{
				Keyboard::keys[i].x = 0.0f;
				Keyboard::prevKeyState[i] = 0.0f;
				
				keySetupHelper(i);
				// new table
				Script::newBlankTable();
				
				// copy table
				Script::pushValue(1);
				// set metatable and pop from stack
				Script::setMetaTable(-2);
				// copy table
				Script::pushValue(1);
				// metatable[1] = "__index" then pop
				Script::setField(1, "__index");
				
				digitalButton** k = Script::newUserdata<digitalButton*>();
				*k = &Keyboard::keys[i];
				
				
				
				Script::getMetaTable("button");
				Script::setMetaTable(-2);
				
				Script::setField(-2, "__self");
				
				
				
				//Script::push((char)i);
				
				Script::setTable(-3);
			}
			
			Script::setGlobal("Key");
			//setupKeys();
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
			// this area can probably be better optimized
			// maybe this can work without prevKeyState
			#warning Why can't I use arrow keys?
			
			Keyboard::prevKeyState[k] = Keyboard::keys[k].x;
			Keyboard::keys[k].x = 1.0f;
			
			if (Keyboard::prevKeyState[k] != Keyboard::keys[k].x)
			{
				Keyboard::keys[k].didChange = true;
			} else {
				Keyboard::keys[k].didChange = false;
			}
			
			inputsChanged[noOfInputsChanged] = &Keyboard::keys[k];
			noOfInputsChanged++;
		}
		void sendKeyUp(int k)
		{
			
			Keyboard::prevKeyState[k] = Keyboard::keys[k].x;
			Keyboard::keys[k].x = 0.0f;
			
			if (Keyboard::prevKeyState[k] != Keyboard::keys[k].x)
			{
				Keyboard::keys[k].didChange = true;
			} else {
				Keyboard::keys[k].didChange = false;
			}
			
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