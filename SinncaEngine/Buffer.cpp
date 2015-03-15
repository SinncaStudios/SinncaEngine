//
//  Buffer.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 9/27/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "Buffer.h"
#include "Tree.h"
#include "Heap.h"

namespace sinnca
{
	buffer::buffer(std::string n)
	{
		alGenBuffers(1, &theBuffer);
		if ((Audio::error = alGetError() != AL_NO_ERROR))
		{
			fprintf(stdout, "Buffer '%s' error: %d\n", n.c_str(), Audio::error);
			
		}
		
		name = n;
	}
	
	buffer::~buffer()
	{
		alDeleteBuffers(1, &theBuffer);
	}
	
	
	void buffer::load(std::string p)
	{
		std::size_t fileTypePos = p.find_last_of(".");
		std::string type = p.substr(fileTypePos);
		
		if (type == ".wav")
		{
			loadWAV(p);
		}
		
	}
	
	ALuint buffer::getBuffer()
	{
		return theBuffer;
	}
	
	void* buffer::operator new(size_t s, std::string n)
	{
		//Create object in lua
		buffer* bf = Script::createObject<buffer>();
		
		Script::setGlobal(n);
		Tree::currentScene->bufferRef.push_back(bf);
		return ((void*)bf);
	}
	
	void buffer::operator delete(void *p)
	{
		if (Tree::currentScene->bufferStorage != NULL)
		{
			Tree::currentScene->bufferStorage->deallocate(p);
			
		} else {
			
			Heap->deallocate(p);
		}
	}
	
	
	
	static int l_newBuffer(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 2)
		{
			return luaL_error(L, "You need to name this buffer...");
		}
		
		Script::checkTable(1);
		//new(luaL_checkstring(L, 2)) entity(luaL_checkstring(L, 2));
		createBuffer(luaL_checkstring(L, 2));
		return 0;
	}
	
	static int l_load(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 2)
		{
			return luaL_error(L, "You need to provide a file path...");
		}
		
		buffer* bf = Script::checkType<buffer>(1);
		bf->load(luaL_checkstring(L, 2));
		
		return 0;
	}
	
	static const luaL_Reg bufferFuncs[] = {
		
		{"new", l_newBuffer},
		{"load", l_load},
		{NULL, NULL}
	};
	
	void registerBuffer(lua_State* L)
	{
		Script::registerType<buffer>(bufferFuncs);
	}
}