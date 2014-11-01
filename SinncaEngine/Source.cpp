//
//  Source.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 9/27/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "Source.h"
#include "Tree.h"


namespace sinnca
{
	source::source(std::string n)
	{
		alGenSources(1, &theSource);
		name = n;
	}
	
	source::~source()
	{
		alDeleteSources(1, &theSource);
	}
	
	void source::setBuffer(buffer* b)
	{
		theBuffer = b;
	}
	
	void source::update()
	{
		
	}
	
	void source::play()
	{
		if (!isPlaying)
		{
			isPlaying = true;
			alSourcePlay(theSource);
		}
	}
	
	void* source::operator new(size_t s, std::string n)
	{
		//Create object in lua
		
		
		Script->newBlankTable();
		
		Script->pushValue(1);
		Script->setMetaTable(-2);
		
		Script->pushValue(1);
		Script->setField(1, "__index");
		
		source** sc = (source**)lua_newuserdata(Script->getState(), sizeof(source*));
		if (Tree->currentScene->sourceStorage != NULL)
		{
			*sc = (source*)Tree->currentScene->sourceStorage->allocate((unsigned int)s, __alignof(source));
			
		} else {
			
			*sc = (source*)Heap->allocate((unsigned int)s, __alignof(source));
		}
		
		//(*en)->name = n;
		
		Script->getMetaTable("source");
		Script->setMetaTable(-2);
		
		Script->setField(-2, "__self");
		
		
		Script->setGlobal(n);
		Tree->currentScene->sourceRef.push_back(*sc);
		Tree->currentScene->nodeRef.push_back(*sc);
		return ((void*)*sc);
	}
	
	void source::operator delete(void *p)
	{
		if (Tree->currentScene->sourceStorage != NULL)
		{
			Tree->currentScene->sourceStorage->deallocate(p);
			
		} else {
			
			Heap->deallocate(p);
		}
	}
	
	source* checkSource(int ind)
	{
		void* ud = 0;
		
		// check for table object
		luaL_checktype(Script->getState(), ind, LUA_TTABLE);
		
		// push the key we're looking for (in this case, it's "__self")
		lua_pushstring(Script->getState(), "__self");
		// get our table
		lua_gettable(Script->getState(), ind);
		
		// cast userdata pointer to "Image" type
		ud = dynamic_cast<source*>((source*)lua_touserdata(Script->getState(), -1));
		luaL_argcheck(Script->getState(), ud != 0, ind, "Incompatible 'source' type...");
		
		return *((source**)ud);
	}
	
	static int l_newSource(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 2)
		{
			return luaL_error(L, "You need to name this source...");
		}
		
		Script->checkTable(1);
		//new(luaL_checkstring(L, 2)) entity(luaL_checkstring(L, 2));
		createSource(luaL_checkstring(L, 2));
		return 0;
	}
	
	static int l_setBuffer(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 2)
		{
			return luaL_error(L, "You need to provide a valid buffer...");
		}
		
		source* sc = checkSource(1);
		sc->setBuffer(checkBuffer(2));
		
		return 0;
	}
	
	static const luaL_Reg sourceFuncs[] = {
		
		{"new", l_newSource},
		{"setBuffer", l_setBuffer},
		
		// node functions
		{"setParent", l_setParent},
		{"addChild", l_addChild},
		{"removeChild", l_removeChild},
		
		
		{"setG", l_setG},
		{"setR", l_setR},
		{"setS", l_setS},
		
		{"movG", l_movG},
		{"movR", l_movR},
		{"movS", l_movS},
		
		{"getG", l_getPos},
		{"getR", l_getRot},
		{"getS", l_getScl},
		
		{"setCol", l_setColor},
		
		{NULL, NULL}
	};
	
	void registerSource(lua_State* L)
	{
		luaL_newmetatable(L, "source");
		
		//luaL_register(L, 0, entityGc);
		luaL_register(L, 0, sourceFuncs);
		lua_pushvalue(L, -1);
		
		lua_setfield(L, -2, "__index");
		
		
		
		luaL_register(L, "source", sourceFuncs);
	}
}

