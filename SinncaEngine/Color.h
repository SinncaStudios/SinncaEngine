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
			
	public:
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
			
			if (Graphics->currentImage != NULL)
			{
				Graphics->currentImage->bound = false;
			}
			Graphics->currentImage = NULL;
			//Graphics->currentShader->uniformVar("textured", 0);
			Graphics->currentShader->uniformVar("mainColor", toFloat(r), toFloat(g), toFloat(b), toFloat(a));
		}
		
	};
	typedef color colour;// for our friends accross the pond

	static color* checkColor(int ind)
	{
		void* ud = 0;
		
		// check for table object
		luaL_checktype(Script->getState(), ind, LUA_TTABLE);
		
		// push the key we're looking for (in this case, it's "__self")
		lua_pushstring(Script->getState(), "__self");
		// get our table
		lua_gettable(Script->getState(), ind);
		
		// cast userdata pointer to "Color" type
		ud = dynamic_cast<color*>((color*)lua_touserdata(Script->getState(), -1));
		luaL_argcheck(Script->getState(), ud != 0, ind, "Incompatible 'color' type...");
		
		return *((color**)ud);
		
	}
}
#endif /* defined(__SinncaEngine__Color__) */
