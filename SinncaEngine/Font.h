//
//  Font.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 3/1/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__Font__
#define __SinncaEngine__Font__

#include <iostream>
#include <vector>
#include "Script.h"
#include "i_graphics.h"

#include "Graphics.h"

#include <ft2build.h>
#include FT_FREETYPE_H

namespace sinnca
{

	struct glyph
	{
		float addx, addy;
		float left, top;
		
		sprite ob;
	};

	class font
	{
		
		int w, h;
		
		std::string name, path;
		float size, kern;
		
		int range[2];
		
		
		bool libLoad;
		
	public:
		
		GLuint atlas;
		
		std::vector<glyph> data;
		
		font(std::string n);
		~font();
		
		void generate();
		void renderGlyph(char aci);
		
		void setSize(float s);
		void setPath(std::string s);
		
	};

	font* checkFont(lua_State* L, int ind);
	void registerFont(lua_State* L);





	int l_newFont(lua_State* L);
	int l_generate(lua_State* L);
	int l_setSize(lua_State* L);
	int l_setPath(lua_State* L);

}

#endif /* defined(__SinncaEngine__Font__) */
