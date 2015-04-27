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
	
	texture::texture():
	source(nullptr)
	{
		
	}
	
	texture::~texture()
	{
		source->removeRef();
		
	}
	
	void* texture::operator new(size_t s)
	{
		texture* tx = Script::createObject<texture>(Tree::currentScene->assets.textureStorage);
		
		tx->ref = Script::makeReference();
		Tree::currentScene->assets.textureRef.push_back(tx);
		Tree::currentScene->assets.colorRef.push_back(tx);
		return ((void*)tx);
	}
	
	void texture::operator delete(void *p)
	{
		if (Tree::currentScene->assets.textureStorage != NULL)
		{
			Tree::currentScene->assets.textureStorage->deallocate(p);
			
		} else {
			
			Heap->deallocate(p);
		}
	}
	
	void texture::setSource(sinnca::image *i)
	{
		if (source) {
			source->removeRef();
		}
		
		source = i;
		source->addRef();
	}
	
	image* texture::getSource()
	{
		return source;
	}
	
	void texture::setOffset(uint x, uint y)
	{
		xOff = x;
		yOff = y;
	}
	
	void texture::setSize(uint x, uint y)
	{
		xSize = x;
		ySize = y;
	}
	
	void texture::getOffset(uint &x, uint &y)
	{
		x = xOff;
		y = yOff;
	}
	
	void texture::getSize(uint &x, uint &y)
	{
		x = xSize;
		y = ySize;
	}
	
	void texture::bind()
	{
		
		Graphics::currentShader->uniformVar("mainColor", toFloat(r), toFloat(g), toFloat(b), toFloat(a));
		
		if (!source->bound)
		{
			if (Graphics::currentImage != NULL)
			{
				Graphics::currentImage->bound = false;
			}
			
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, source->getData());
			glUniform1i(Graphics::currentShader->uniformTex, 0);
			
			source->bound = true;
			Graphics::currentImage = source;
		}
		
		
	}
	
	
	static int l_newTexture(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 1)
		{
			return luaL_error(L, "You need to name this texture...");
		}
		
		Script::checkTable(1);
		new texture();
		return 1;
	}
	
	static int l_setSource(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 2)
		{
			return luaL_error(L, "I need an image to source!");
		}
		
		texture* tx = Script::checkType<texture>(1);
		
		tx->setSource(Script::checkType<image>(2));
		
		return 0;
	}
	
	static int l_setOffset(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 3)
		{
			return luaL_error(L, "I need coordinates!");
		}
		
		texture* tx = Script::checkType<texture>(1);
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
		Script::registerType<texture>(textureFuncs);
	}
	
	
}

