//
//  Texture.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 3/3/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "Texture.h"
#include "Tree.h"

namespace sinnca
{
	
	texture::texture(std::string n)
	{
		source = nullptr;
		name = n;
	}
	
	texture::~texture()
	{
		source->clients--;
		
		if (source->clients == 0)
		{
			delete source;
		}
	}
	
	void* texture::operator new(size_t s, std::string n)
	{
		Script->newBlankTable();
		
		Script->pushValue(1);
		Script->setMetaTable(-2);
		
		Script->pushValue(1);
		Script->setField(1, "__index");
		
		//entity** en = Script->newUserdata<entity*>();
		texture** tx = (texture**)lua_newuserdata(Script->getState(), sizeof(texture*));
		if (Tree->currentScene->textureStorage != NULL)
		{
			*tx = (texture*)Tree->currentScene->textureStorage->allocate((unsigned int)s, __alignof(texture));
			
		} else {
			
			*tx = (texture*)Heap->allocate((unsigned int)s, __alignof(texture));
		}
		
		
		Script->getMetaTable("texture");
		Script->setMetaTable(-2);
		
		Script->setField(-2, "__self");
		
		
		Script->setGlobal(n);
		Tree->currentScene->textureRef.push_back(*tx);
		return ((void*)*tx);
	}
	
	void texture::operator delete(void *p)
	{
		if (Tree->currentScene->textureStorage != NULL)
		{
			Tree->currentScene->textureStorage->deallocate(p);
			
		} else {
			
			Heap->deallocate(p);
		}
	}
	
	void texture::setSource(sinnca::image *i)
	{
		source = i;
		i->clients++;
	}
	
	image* texture::getSource()
	{
		return source;
	}
	
	void texture::setOffset(int x, int y)
	{
		xOff = x;
		yOff = y;
	}
	
	void texture::setSize(int x, int y)
	{
		xSize = x;
		ySize = y;
	}
	
	void texture::getOffset(int &x, int &y)
	{
		x = xOff;
		y = yOff;
	}
	
	void texture::getSize(int &x, int &y)
	{
		x = xSize;
		y = ySize;
	}
	
	void texture::bind()
	{
		
		//Graphics->currentShader->uniformVar("textured", 1);
		Graphics->currentShader->uniformVar("mainColor", toFloat(r), toFloat(g), toFloat(b), toFloat(a));
		
		if (!source->bound)
		{
			if (Graphics->currentImage != NULL)
			{
				Graphics->currentImage->bound = false;
			}
			
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, source->getData());
			glUniform1i(Graphics->currentShader->uniformTex, 0);
			
			source->bound = true;
			Graphics->currentImage = source;
		}
		
		
	}
	
	texture* checkTexture(int ind)
	{
		void* ud = 0;
		
		// check for table object
		luaL_checktype(Script->getState(), ind, LUA_TTABLE);
		
		// push the key we're looking for (in this case, it's "__self")
		lua_pushstring(Script->getState(), "__self");
		// get our table
		lua_gettable(Script->getState(), ind);
		
		// cast userdata pointer to "Texture" type
		ud = dynamic_cast<texture*>((texture*)lua_touserdata(Script->getState(), -1));
		luaL_argcheck(Script->getState(), ud != 0, ind, "Incompatible 'color' type...");
		
		return *((texture**)ud);
	}
	
	static int l_newTexture(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 2)
		{
			return luaL_error(L, "You need to name this texture...");
		}
		
		Script->checkTable(1);
		//new(luaL_checkstring(L, 2)) entity(luaL_checkstring(L, 2));
		createTexture(luaL_checkstring(L, 2));
		return 0;
		
		return 0;
	}
	
	static int l_setSource(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 2)
		{
			return luaL_error(L, "I need an image to source!");
		}
		
		texture* tx = checkTexture(1);
		
		tx->setSource(checkImage(2));
		
		return 0;
	}
	
	static int l_setOffset(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 3)
		{
			return luaL_error(L, "I need coordinates!");
		}
		
		texture* tx = checkTexture(1);
		tx->setOffset((int)lua_tointeger(L, 2), (int)lua_tointeger(L, 3));
		
		return 0;
	}
	
	static const luaL_Reg textureFuncs[] = {
		{"new", l_newTexture},
		{"setSource", l_setSource},
		{"setOffset", l_setOffset},
		{NULL, NULL}
	};
	
	void registerTexture(lua_State* L)
	{
		
		luaL_newmetatable(L, "texture");
		
		luaL_register(L, 0, textureFuncs);
		lua_pushvalue(L, -1);
		
		lua_setfield(L, -2, "__index");
		
		
		
		luaL_register(L, "texture", textureFuncs);
	}
	
	
}

