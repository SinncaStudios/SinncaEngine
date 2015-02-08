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
	image::image(std::string n)
	{
		glGenTextures(1, &data);
		clients = 0;
		bound = false;
		
		name = n;
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
	
	void* image::operator new(size_t s, std::string n)
	{
		Script->newBlankTable();
		
		Script->pushValue(1);
		Script->setMetaTable(-2);
		
		Script->pushValue(1);
		Script->setField(1, "__index");
		
		//entity** en = Script->newUserdata<entity*>();
		image** im = (image**)lua_newuserdata(Script->getState(), sizeof(image*));
		if (Tree->currentScene->imageStorage != NULL)
		{
			*im = (image*)Tree->currentScene->imageStorage->allocate((unsigned int)s, __alignof(image));
			
		} else {
			
			*im = (image*)Heap->allocate((unsigned int)s, __alignof(image));
		}
		
		//(*im)->name = n;
		
		Script->getMetaTable("image");
		Script->setMetaTable(-2);
		
		Script->setField(-2, "__self");
		
		
		Script->setGlobal(n);
		Tree->currentScene->imageRef.push_back(*im);
		return ((void*)*im);
	}
	
	void image::operator delete(void *p)
	{
		if (Tree->currentScene->imageStorage != NULL)
		{
			Tree->currentScene->imageStorage->deallocate(p);
			
		} else {
			
			Heap->deallocate(p);
		}
	}
	
	
	image* checkImage(int ind)
	{
		void* ud = 0;
		
		// check for table object
		luaL_checktype(Script->getState(), ind, LUA_TTABLE);
		
		// push the key we're looking for (in this case, it's "__self")
		lua_pushstring(Script->getState(), "__self");
		// get our table
		lua_gettable(Script->getState(), ind);
		
		// cast userdata pointer to "Image" type
		ud = dynamic_cast<image*>((image*)lua_touserdata(Script->getState(), -1));
		luaL_argcheck(Script->getState(), ud != 0, ind, "Incompatible 'image' type...");
		
		return *((image**)ud);
		
	}
	
	static int l_newImage(lua_State* L)
	{
		
		int n = lua_gettop(L);
		if (n != 2)
		{
			return luaL_error(L, "You need to name this image...");
		}
		
		Script->checkTable(1);
		//new(luaL_checkstring(L, 2)) entity(luaL_checkstring(L, 2));
		createImage(luaL_checkstring(L, 2));
		return 0;
	}
	
	static int l_loadImage(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 2)
		{
			return luaL_error(L, "You need to provide a file to load...");
		}
		
		image* im = checkImage(1);
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
		
		luaL_newmetatable(L, "image");
		
		luaL_register(L, 0, imageFuncs);
		lua_pushvalue(L, -1);
		
		lua_setfield(L, -2, "__index");
		
		
		
		luaL_register(L, "image", imageFuncs);
	}
}

