//
//  GuiString.cpp
//  Sinnca Engine
//
//  Created by Ryan Oldis on 4/25/12.
//  Copyright (c) 2012 Sinnca Studios. All rights reserved.
//

#include "GuiString.h"
#include "Node.h"
#include "Tree.h"

namespace sinnca
{
	guiString::guiString(std::string n) : guiWidget(n)
	{
		/*
		draw = true;
		
		pos.x = 1;
		pos.y = 1;
		
		col = &Palette->white;
		
		scl.x = 20;
		scl.y = 20;
		*/
		
		ft = NULL;
		str = "";
	}
	
	guiString::~guiString()
	{
		
	}

	void guiString::render()
	{
		
		if (ft != NULL)
		{
			
			Graphics::pushMatrix();
			Graphics::move(pos.x/2, pos.y/2, 0);
			
			//glColor4f(color[0], color[1], color[2], color[3]);
			col->bind();
			glBindTexture(GL_TEXTURE_2D, ft->atlas);
			
			Graphics::pushMatrix();
			
			for (int i = 0; i < str.length(); i++)
			{
				
				ft->renderGlyph(str[i]);
			}
			
			Graphics::popMatrix();
			Graphics::popMatrix();
			 
		}
		
	}

	void guiString::setFont(font *f)
	{
		if (ft) {
			ft->removeRef();
		}
		
		ft = f;
		ft->addRef();
	}
	void guiString::setStr(std::string s)
	{
		str = s;
	}

	
	void* guiString::operator new(size_t s, std::string n)
	{
		guiString* st = Script::createObject<guiString>(Tree::guiStorage);
		
		Script::setGlobal(n);
		Tree::currentScene->guiManager->addChild(st);
		return (void*)st;
	}
	
	void guiString::operator delete(void *p)
	{
		Tree::guiStorage->deallocate(p);
	}


	static int l_newString(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 2)
		{
			return luaL_error(L, "You need to name this widget...");
		}
		
		Script::checkTable(1);
		createGuiString(lua_tostring(L, 2));
		
		return 1;
	}

	static int l_setFont(lua_State* L)
	{
		int n = lua_gettop(L);
		font* f;
		guiString* st;
		
		if (n == 2)
		{
			st = Script::checkType<guiString>(1);
			f = Script::checkType<font>(2);
			
			st->setFont(f);
		}
		
		return 0;
	}

	static int l_setStr(lua_State* L)
	{
		int n = lua_gettop(L);
		guiString* st;
		
		if (n == 2)
		{
			st = Script::checkType<guiString>(1);
			
			st->setStr(lua_tostring(L, 2));
		}
		
		return 0;
	}



	static const luaL_Reg stringFuncs[] = {
		
		{"new", l_newString},
		{"setFont", l_setFont},
		{"setStr", l_setStr},
		
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

	void registerString(lua_State* L)
	{
		Script::registerType<guiString>(stringFuncs);
	}
}

