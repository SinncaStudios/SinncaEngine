//
//  InputType.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 12/18/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef SinncaEngine_InputType_h
#define SinncaEngine_InputType_h

#include "Script.h"

namespace sinnca
{
	struct InputType
	{
		bool didChange, wasPressed, wasReleased;
		float x;
		
		InputType() :
		didChange(false),
		x(0.0f)
		{
			
		}
		
		void setChange(bool b)
		{
			didChange = b;
		}
		
		virtual void setDown(int s)
		{
			x = s;
		}
	};
	
	
	
	static int l_isDown(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n == 1)
		{
			InputType* bn = Script::checkType<InputType>(1);
			
			if (bn->x > 0.0f)
			{
				Script::push(1);
				
			} else {
				Script::push(0);
			}
		}
		
		return 1;
	}
	
	static int l_isUp(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n == 1)
		{
			InputType* bn = Script::checkType<InputType>(1);
			
			if (bn->x == 0.0f)
			{
				Script::push(1);
				
			} else {
				Script::push(0);
			}
		}
		
		return 1;
	}
	
	
	static int l_wasPressed(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n == 1)
		{
			InputType* bn = Script::checkType<InputType>(1);
			
			if (bn->x > 0.0f && bn->didChange)
			{
				Script::push(1);
				bn->didChange = false;
				
			} else {
				Script::push(0);
			}
		}
		
		return 1;
	}
	
	static int l_wasReleased(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n == 1)
		{
			InputType* bn = Script::checkType<InputType>(1);
			
			if (bn->x == 0.0f && bn->didChange)
			{
				Script::push(1);
				bn->didChange = false;
				
			} else {
				Script::push(0);
			}
		}
		
		return 1;
	}
	
	static int l_getRawPressure(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n == 1)
		{
			InputType* bn = Script::checkType<InputType>(1);
			
			Script::push(bn->x);
		}
		
		return 1;
	}
	
	
	static const luaL_Reg inputTypeFuncs[] = {
		{"isDown", l_isDown},
		{"isUp", l_isUp},
		{"wasPressed", l_wasPressed},
		{"wasReleased", l_wasReleased},
		{"getRawPressure", l_getRawPressure},
		{NULL, NULL}
	};
	
	
	
}


#endif
