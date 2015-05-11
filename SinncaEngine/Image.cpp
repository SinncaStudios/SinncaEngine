//
//  Image.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 3/3/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "Image.h"
#include "Tree.h"
#include "Heap.h"


namespace sinnca
{
	image::image() :
	bound(false)
	{
		glGenTextures(1, &data);
	}
	
	image::~image()
	{
		glDeleteTextures(1, &data);
	}
	
	
	void image::load(std::string p)
	{
		std::size_t fileTypePos = p.find_last_of(".");
		std::string type = p.substr(fileTypePos);
		path = p;
		tb = smooth;
		
		if (type == ".png")
		{
			loadPNG(p);
		}
	}

	
	GLuint image::getData()
	{
		return data;
	}
	
	void* image::operator new(size_t s)
	{
		uint reference;
		image* im = Script::createObject<image>(&reference);
		
		im->ref = reference;
		Tree::currentScene->imageRef.push_back(im);
		return ((void*)im);
	}
	
	void image::operator delete(void *p)
	{
		if (Tree::currentScene->imageStorage != NULL)
		{
			Tree::currentScene->imageStorage->deallocate(p);
			
		} else {
			
			Heap->deallocate(p);
		}
	}
	
	
	static int l_newImage(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 1)
		{
			return luaL_error(L, "You need to put this object into a variable");
		}
		
		Script::checkTable(1);
		new image();
		return 1;
	}
	
	static int l_loadImage(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 2)
		{
			return luaL_error(L, "You need to provide a file to load...");
		}
		
		image* im = Script::checkType<image>(1);
		im->load(lua_tostring(L, 2));
		
		return 0;
	}
	
	static const luaL_reg imageFuncs[] = {
		{"new", l_newImage},
		{"load", l_loadImage},
		{NULL, NULL}
	};
	
	void registerImage(lua_State* L)
	{
		Script::registerType<image>(imageFuncs);
	}
}

