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
		if ((Audio::error = alGetError() != AL_NO_ERROR))
		{
			printf("Source '%s' error: %d\n", n.c_str(), Audio::error);
		}
		
		
		name = n;
		
		Tree->currentScene->addChild(this);
		parent = Tree->currentScene;
		
		pitch = 1.0f;
		gain = 1.0f;
		
		alSourcef(theSource, AL_PITCH, pitch);
		alSourcef(theSource, AL_GAIN, gain);
		alSourcei(theSource, AL_LOOPING, AL_FALSE);
		
		alSource3f(theSource, AL_POSITION, pos.x, pos.y, pos.z);
		
	}
	
	source::~source()
	{
		alDeleteSources(1, &theSource);
	}
	
	void source::setBuffer(buffer* b)
	{
		theBuffer = b;
		alSourcei(theSource, AL_BUFFER, b->getBuffer());
		if ((Audio::error = alGetError() != AL_NO_ERROR))
		{
			printf("Source '%s' error: %d\n", name.c_str(), Audio::error);
		}
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
			
			if ((Audio::error = alGetError() != AL_NO_ERROR))
			{
				printf("Source '%s' error: %s\n", name.c_str(), alGetString(Audio::error));
			}
		}
	}
	
	void source::pause()
	{
		if (isPlaying)
		{
			isPlaying = false;
			alSourcePause(theSource);
		}
	}
	
	void source::rewind()
	{
		alSourceRewind(theSource);
	}
	
	void* source::operator new(size_t s, std::string n)
	{
		//Create object in lua
		
		source* sc = Script->createObject<source>();
		
		Script->setGlobal(n);
		Tree->currentScene->sourceRef.push_back(sc);
		Tree->currentScene->nodeRef.push_back(sc);
		return ((void*)sc);
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
		
		source* sc = Script->checkType<source>(1);
		sc->setBuffer(Script->checkType<buffer>(2));
		
		return 0;
	}
	
	static int l_play(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 1)
		{
			return luaL_error(L, "You need to provide a valid source...");
		}
		
		source* sc = Script->checkType<source>(1);
		sc->play();
		
		return 0;
	}
	
	static int l_pause(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 1)
		{
			return luaL_error(L, "You need to provide a valid source...");
		}
		
		source* sc = Script->checkType<source>(1);
		sc->pause();
		
		return 0;
	}
	
	static int l_rewind(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 1)
		{
			return luaL_error(L, "You need to provide a valid source...");
		}
		
		source* sc = Script->checkType<source>(1);
		sc->rewind();
		
		return 0;
	}
	
	static const luaL_Reg sourceFuncs[] = {
		
		{"new", l_newSource},
		{"setBuffer", l_setBuffer},
		
		{"play", l_play},
		{"pause", l_pause},
		{"rewind", l_rewind},
		
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
		Script->registerType<source>(sourceFuncs);
	}
}

