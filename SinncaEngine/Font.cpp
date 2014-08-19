//
//  Font.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 3/1/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "Font.h"
#include "Utility.h"

#include "i_graphics.h"

namespace sinnca
{
	
	
	font::font(std::string n)
	{
		
		name = n;
		path = "";
		
		size = 12.0; // 12 point is default
		kern = 0.1;
		
		w = 0;
		h = 0;
		
		range[0] = 32;
		range[1] = 128;
		
	}
	
	font::~font()
	{
		glDeleteTextures(1, &atlas);
		data.clear();
	}
	
	void font::generate()
	{
		/*
		FT_Library ft;
		//int hang, bearing;
		
		
		if (FT_Init_FreeType(&ft))
		{
			printf("Could not init freetype library");
		}
		
		FT_Face fontface;
		
		if (path != "") // don't try to load if a path hasn't been specified
		{
			if (FT_New_Face(ft, path.c_str(), 0, &fontface))
			{
				printf("could not open font");
			}
		} else {
			return;
		}
		
		FT_Set_Pixel_Sizes(fontface, 0, size);
		FT_GlyphSlot g = fontface->glyph;
		
		int rowWidth = 0, rowHeight = 0;
		
		
		for (int i = range[0]; i < range[1]; i++)
		{
			if (FT_Load_Char(fontface, i, FT_LOAD_RENDER))
			{
				printf("couldn't load character for some reason....");
			}
			
			if (rowWidth + g->bitmap.width + 1 >= 1024)
			{
				w = std::max(w, rowWidth);
				h += rowHeight;
				
				rowWidth = 0;
				rowHeight = 0;
			}
			rowWidth += g->bitmap.width + 1;
			rowHeight = std::max(rowHeight, g->bitmap.rows);
			
		}
		
		w = (int)nextPowerOfTwo(std::max(w, rowWidth));
		h = (int)nextPowerOfTwo(rowHeight);
		
		
		//
		// Open GL stuff now.
		//
		
		GLuint* pixels = new GLuint[w * h];
		//printf("%ld\n", sizeof(pixels) / sizeof(GLuint));
		
		for (int i = 0; i < (w * h); i++)
		{
			GLuint newCol;
			GLubyte* pixColor = (GLubyte*)&newCol;
			
			pixColor[0] = 0x00;
			pixColor[1] = 0x00;
			pixColor[2] = 0x00;
			pixColor[3] = 0x00;
			
			pixels[i] = newCol;
			
		}
		
		glActiveTexture(GL_TEXTURE0);
		glGenTextures(1, &atlas);
		glBindTexture(GL_TEXTURE_2D, atlas);
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, w, h, 0, GL_ALPHA, GL_UNSIGNED_BYTE, pixels);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		
		delete [] pixels;
		int offx = 0;
		int offy = 0;
		glyph tmp;
		
		rowHeight = 0;
		
		for (int i = range[0]; i < range[1]; i++)
		{
			if (FT_Load_Char(fontface, i, FT_LOAD_RENDER))
			{
				printf("couldn't load character for some reason....");
				continue;
			}
			
			if (offx + g->bitmap.width + 1 >= 1024)
			{
				offy +=rowHeight;
				
				rowHeight = 0;
				offx = 0;
			}
			
			glTexSubImage2D(GL_TEXTURE_2D, 0, offx, offy, g->bitmap.width, g->bitmap.rows, GL_ALPHA, GL_UNSIGNED_BYTE, g->bitmap.buffer);
			
			
			
			tmp.addx = g->advance.x;
			tmp.addy = g->advance.y;
			
			tmp.w = g->bitmap.width;
			tmp.h = g->bitmap.rows;
			
			tmp.left = g->bitmap_left;
			tmp.top = g->bitmap_top;
			
			tmp.tx = offx / (float)w;
			tmp.ty = offy / (float)h;
			
			data.push_back(tmp);
			
			rowHeight = std::max(rowHeight, g->bitmap.rows);
			offx += g->bitmap.width + 1;
		}
		
		FT_Done_Face(fontface);
		FT_Done_FreeType(ft);
		glBindTexture(GL_TEXTURE_2D, 0);
		*/
	}
	
	void font::renderGlyph(char aci)
	{
		
		int ref = ((int)aci) - range[0];
		
		
		if (aci == '\n')
		{
			glPopMatrix();
			glTranslatef(0.0f, size, 0.0f);
			glPushMatrix();
			
		} else {
			// texture was set by string renderer
			
			glPushMatrix();
			glTranslatef(0.0f, (data[ref].top * -1) + 16, 0.0f);
			
			float x = data[ref].tx;
			float y = data[ref].ty;
			float wth = data[ref].tx + ((1.0f / w) * (float)data[ref].w);
			float hgt = ((1.0f / h) * (float)data[ref].h);
			
			//printf("%c %f %f %f\n", ref, data[ref - range[0]].tx, data[ref - range[0]].w, wth);
			if (!data[ref].addx) {
				return;
			}
			
#if snMobile == 0
			glBegin(GL_QUADS);
			glTexCoord2d(x, hgt);	glVertex2f(0, data[ref].h);
			glTexCoord2d(x, y);		glVertex2f(0, 0);
			glTexCoord2d(wth, y);	glVertex2f(data[ref].w, 0);
			glTexCoord2d(wth, hgt);	glVertex2f(data[ref].w, data[ref].h);
			glEnd();
#endif
			
			glPopMatrix();
		}
		
		glTranslatef(data[ref].addx / 64.f, 0, 0);
		
	}
	
	void font::setSize(float s)
	{
		size = s;
	}
	void font::setPath(std::string s)
	{
		path = s;
	}
	
	
	font* checkFont(lua_State* L, int ind)
	{
		void* ud = 0;
		
		// check for table object
		luaL_checktype(L, ind, LUA_TTABLE);
		
		// push the key we're looking for (in this case, it's "__self")
		lua_pushstring(L, "__self");
		// get our table
		lua_gettable(L, ind);
		
		// cast userdata pointer to "Node" type
		ud = dynamic_cast<font*>((font*)lua_touserdata(L, -1));
		luaL_argcheck(L, ud != 0, ind, "Incompatible 'gui' type...");
		
		return *((font**)ud);
		
	}
	
	int l_newFont(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 2)
		{
			return luaL_error(L, "You need to name this font object...");
		}
		
		luaL_checktype(L, 1, LUA_TTABLE);
		
		
		lua_newtable(L);
		
		lua_pushvalue(L, 1);
		lua_setmetatable(L, -2);
		
		lua_pushvalue(L, 1);
		lua_setfield(L, 1, "__index");
		
		
		font** ft = (font**)lua_newuserdata(L, sizeof(font*));
		*ft = new font(luaL_checkstring(L, 2));
		
		//(*en)->setParent(Tree->currentScene);
		
		luaL_getmetatable(L, "font");
		lua_setmetatable(L, -2);
		
		lua_setfield(L, -2, "__self");
		
		
		lua_setglobal(L, luaL_checkstring(L, 2));
		
		
		return 1;
	}
	
	int l_generate(lua_State* L)
	{
		int n = lua_gettop(L);
		font* ft;
		
		if (n == 1)
		{
			ft = checkFont(L, 1);
			ft->generate();
		}
		
		return 0;
	}
	
	int l_setPath(lua_State* L)
	{
		int n = lua_gettop(L);
		font* ft;
		
		if (n == 2)
		{
			ft = checkFont(L, 1);
			ft->setPath(lua_tostring(L, 2));
		}
		
		return 0;
	}
	
	int l_setSize(lua_State* L)
	{
		int n = lua_gettop(L);
		font* ft;
		
		if (n == 2)
		{
			ft = checkFont(L, 1);
			ft->setSize(lua_tonumber(L, 2));
		}
		
		return 0;
	}
	
	int clear(lua_State* L)
	{
		int n = lua_gettop(L);
		font* ft = checkFont(L, 1);
		
		if (n == 1)
		{
			delete ft;
		}
		return 0;
	}
	
	static const luaL_Reg fontGc[] = {
		{"__gc", clear},
		{NULL, NULL}
	};
	
	static const luaL_Reg fontFuncs[] = {
		
		{"new", l_newFont},
		{"generate", l_generate},
		{"setSize", l_setSize},
		{"setPath", l_setPath},
		{NULL, NULL}
	};
	
	void registerFont(lua_State* L)
	{
		
		luaL_newmetatable(L, "font");
		
		luaL_register(L, 0, fontFuncs);
		lua_pushvalue(L, -1);
		
		lua_setfield(L, -2, "__index");
		
		
		
		luaL_register(L, "font", fontFuncs);
		
	}
	
	
	

}