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
	input* input::_instance = NULL;
	
	input* input::Instance()
	{
		if (_instance == NULL)
		{
			_instance = Heap->allocateNew<input>();
		}
		
		return _instance;
	}
	
	input::input()
	{
		for (int i = 0; i < 322; i++)
		{
			keyArray[i] = false;
		}
	}
	
	input::~input()
	{
		
	}
	
	void input::update()
	{
		
	}
	
	void input::sendKeyDown(int k)
	{
		keyArray[k] = true;
	}
	void input::sendKeyUp(int k)
	{
		keyArray[k] = false;
	}
	
	
	int l_keyDown(lua_State* L)
	{
		int n = lua_gettop(L);
		int a;
		
		for (int i = -1; i >= (n * -1); i--)
		{
			a = (int)lua_tointeger(L, i);
			if (Input->keyArray[a])
			{
				lua_pushboolean(L, 0);
				return 1;
			}
			
		}
		lua_pushboolean(L, 1);
		
		return 1;
	}
}