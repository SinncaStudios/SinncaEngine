//
//  Font.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 3/1/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "Font.h"
#include "Utility.h"
#include "Tree.h"


namespace sinnca
{
	
	
	font::font()
	{
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
	
	void font::load(std::string p = "")
	{
		
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
			
			
			
//			tmp.addx = g->advance.x;
//			tmp.addy = g->advance.y;
//			
//			tmp.w = g->bitmap.width;
//			tmp.h = g->bitmap.rows;
//			
//			tmp.left = g->bitmap_left;
//			tmp.top = g->bitmap_top;
//			
//			tmp.tx = offx / (float)w;
//			tmp.ty = offy / (float)h;
			
			tmp.ob.vertices[0].position[1] = g->bitmap.rows;
			tmp.ob.vertices[2].position[0] = g->bitmap.width;
			tmp.ob.vertices[3].position[0] = g->bitmap.width;
			tmp.ob.vertices[3].position[1] = g->bitmap.rows;
			
			tmp.ob.vertices[0].texco[0] = offx / (float)w;
			tmp.ob.vertices[0].texco[1] = ((1.0f / h) * (float)g->bitmap.rows);
			tmp.ob.vertices[1].texco[0] = offx / (float)w;
			tmp.ob.vertices[1].texco[1] = offy / (float)h;
			tmp.ob.vertices[2].texco[0] = ((1.0f / w) * (float)g->bitmap.width);
			tmp.ob.vertices[2].texco[1] = offy / (float)h;
			tmp.ob.vertices[3].texco[0] = ((1.0f / w) * (float)g->bitmap.width);
			tmp.ob.vertices[3].texco[1] = ((1.0f / h) * (float)g->bitmap.rows);
			
			data.push_back(tmp);
			
			rowHeight = std::max(rowHeight, g->bitmap.rows);
			offx += g->bitmap.width + 1;
		}
		
		FT_Done_Face(fontface);
		FT_Done_FreeType(ft);
		glBindTexture(GL_TEXTURE_2D, 0);
		
	}
	
	void font::renderGlyph(char aci)
	{
		
		int ref = ((int)aci) - range[0];
		
		
		if (aci == '\n')
		{
			Graphics::popMatrix();
			Graphics::move(0.0f, size, 0.0f);
			Graphics::pushMatrix();
			
		} else {
			// texture was set by string renderer
			
			Graphics::pushMatrix();
			Graphics::move(0.0f, (data[ref].top * -1) + 16, 0.0f);
			if (!data[ref].addx) {
				return;
			}
			
			data[ref].ob.render();
			
			
			
			Graphics::popMatrix();
		}
		
		Graphics::move(data[ref].addx / 64.f, 0, 0);
		
	}
	
	void font::setSize(float s)
	{
		size = s;
	}
	void font::setPath(std::string s)
	{
		path = s;
	}
	
	
	void* font::operator new(size_t s)
	{
		uint reference;
		font* ft = Script::createObject<font>(&reference);
		ft->ref = reference;
		
		return (void*)ft;
	}
	
	void font::operator delete(void *p)
	{
		if (Tree::currentScene->fontStorage != NULL)
		{
			Tree::currentScene->fontStorage->deallocate(p);
			
		} else {
			Heap->deallocate(p);
		}
	}
	
	
	
	int l_newFont(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 1)
		{
			return luaL_error(L, "You need to put this object into a variable");
		}
		
		Script::checkTable(1);
		new font();
		return 1;
	}
	
	int l_generate(lua_State* L)
	{
		int n = lua_gettop(L);
		font* ft;
		
		if (n == 1)
		{
			ft = Script::checkType<font>(1);
			ft->load();
		}
		
		return 0;
	}
	
	int l_setPath(lua_State* L)
	{
		int n = lua_gettop(L);
		font* ft;
		
		if (n == 2)
		{
			ft = Script::checkType<font>(1);
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
			ft = Script::checkType<font>(1);
			ft->setSize(lua_tonumber(L, 2));
		}
		
		return 0;
	}
	
	int clear(lua_State* L)
	{
		int n = lua_gettop(L);
		font* ft = Script::checkType<font>(1);
		
		if (n == 1)
		{
			delete ft;
		}
		return 0;
	}
	
//	static const luaL_Reg fontGc[] = {
//		{"__gc", clear},
//		{NULL, NULL}
//	};
	
	static const luaL_Reg fontFuncs[] = {
		
		{"new", l_newFont},
		{"generate", l_generate},
		{"setSize", l_setSize},
		{"setPath", l_setPath},
		{NULL, NULL}
	};
	
	void registerFont(lua_State* L)
	{
		Script::registerType<font>(fontFuncs);
		
	}
	
	
	

}