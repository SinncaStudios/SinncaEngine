//
//  Color.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 1/30/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__Color__
#define __SinncaEngine__Color__

#include <iostream>
#include "Types.h"
#include "Graphics.h"
#include "Script.h"



namespace sinnca
{
	class color
	{
		
		// discriminated union
		
	public:
		
		static constexpr auto metatable = "color";
		
		// each variable is one byte with a range of 0 to 255
		ui8 r, g, b, a;
		std::string name;

		color(std::string n = "")
		{
			r = 255;
			g = 255;
			b = 255;
			
			a = 255;
			
			name = n;
		}
		
		float toFloat(ui8 channel)
		{
			return channel / (float)255;
		}
		
		virtual void bind()
		{
			//glColor4f(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
			
			if (Graphics::currentImage != NULL)
			{
				Graphics::currentImage->bound = false;
			}
			Graphics::currentImage = NULL;
			//Graphics::currentShader->uniformVar("textured", 0);
			Graphics::currentShader->uniformVar("mainColor", toFloat(r), toFloat(g), toFloat(b), toFloat(a));
		}
		
		virtual ui32* getPixel(float u = 0.0f, float v = 0.0f)
		{
			ui32 workingCopy;
			ui32* product = &workingCopy;
			
			product[0] = r;
			product[1] = g;
			product[2] = b;
			product[3] = a;
			
			return product;
		}
		
		virtual uint getWidth()
		{
			return 1;
		}
		virtual uint getHeight()
		{
			return 1;
		}
		
		void* operator new(size_t s, std::string n)
		{
			color* cl = Script::createObject<color>();
			
			Script::setGlobal(n);
			return (void*)cl;
		}
		#define createColor(a) new(a)color(a)
		#define createColour(a) new(a)color(a)
		
		void operator delete(void* p)
		{
			Heap->deallocate(p);
		}
		
	};
	typedef color colour;// for our friends accross the pond
	
	static int l_newColor(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 2)
		{
			return luaL_error(L, "You need to name this color...");
		}
		
		Script::checkTable(1);
		createColor(lua_tostring(L, 2));
		return 0;
	}
	
	static int l_setColorValue(lua_State* L)
	{
		int n = lua_gettop(L);
		color* cl = Script::checkType<color>(1);
		
		if (n == 3 || n == 4)
		{
			
			cl->r = lua_tointeger(L, 2);
			cl->g = lua_tointeger(L, 3);
			cl->b = lua_tointeger(L, 4);
			
		} else if (n == 4)
		{
			cl->a = lua_tointeger(L, 5);
		}
		
		return 0;
	}
	
	static const luaL_Reg colorFuncs[] = {
		{"new", l_newColor},
		{"setColor", l_setColorValue},
		{"setColour", l_setColorValue},
		{NULL, NULL}
	};
	
	
	// this function causes a duplicate symbol error
	// the actual registering will be done by the templated register function in Binding.cpp
	/*
	void registerColor()
	{
		Script::registerType<color>(colorFuncs);
	}
	 */
}
#endif /* defined(__SinncaEngine__Color__) */
