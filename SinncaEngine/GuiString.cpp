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
	guiString::guiString()
	{
		draw = true;
		
		xy[0] = 1;
		xy[1] = 1;
		
		col = &Palette->white;
		
		scl[0] = 20;
		scl[1] = 20;
		
		
		ft = NULL;
		
		//name = n;
		str = "";
	}

	void guiString::render()
	{
		/*
		if (ft != NULL)
		{
			
			glPushMatrix();
			glTranslatef(xy[0]/2, xy[1]/2, 0);
			
			glColor4f(color[0], color[1], color[2], color[3]);
			glBindTexture(GL_TEXTURE_2D, ft->atlas);
			
			glPushMatrix();
			
			for (int i = 0; i < str.length(); i++)
			{
				
				ft->renderGlyph(str[i]);
			}
			
			glPopMatrix();
			glPopMatrix();
			 
		}
		*/
	}

	void guiString::setFont(font *f)
	{
		ft = f;
	}
	void guiString::setStr(std::string s)
	{
		str = s;
	}



	guiString* checkString(lua_State* L, int ind)
	{
		void* ud = 0;
		
		// check for table object
		luaL_checktype(L, ind, LUA_TTABLE);
		
		// push the key we're looking for (in this case, it's "__self")
		lua_pushstring(L, "__self");
		// get our table
		lua_gettable(L, ind);
		
		// cast userdata pointer to "String" type
		ud = dynamic_cast<guiString*>((guiString*)lua_touserdata(L, -1));
		luaL_argcheck(L, ud != 0, ind, "Incompatible 'gui' type...");
		
		return *((guiString**)ud);
	}


	static int l_newString(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 2)
		{
			return luaL_error(L, "You need to name this widget...");
		}
		
		luaL_checktype(L, 1, LUA_TTABLE);
		
		
		lua_newtable(L);
		
		lua_pushvalue(L, 1);
		lua_setmetatable(L, -2);
		
		lua_pushvalue(L, 1);
		lua_setfield(L, 1, "__index");
		
		
		guiString** st = (guiString**)lua_newuserdata(L, sizeof(guiString*));
		*st = new guiString(/*lua_tostring(L, 2)*/);
		
		(*st)->setName(luaL_checkstring(L, 2));
		
		luaL_getmetatable(L, "string");
		lua_setmetatable(L, -2);
		
		lua_setfield(L, -2, "__self");
		
		
		lua_setglobal(L, luaL_checkstring(L, 2));
		
		
		Tree->currentScene->guiManager->children.pushBack(*st);
		return 1;
	}

	static int l_setFont(lua_State* L)
	{
		int n = lua_gettop(L);
		font* f;
		guiString* st;
		
		if (n == 2)
		{
			st = checkString(L, 1);
			f = checkFont(L, 2);
			
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
			st = checkString(L, 1);
			
			st->setStr(lua_tostring(L, 2));
		}
		
		return 0;
	}



	static const luaL_Reg stringFuncs[] = {
		
		{"new", l_newString},
		{"setFont", l_setFont},
		{"setStr", l_setStr},
		
		{"setXY", l_setXY},
		{"movXY", l_movXY},
		{"setCol", l_setCol},
		{"setWH", l_setWH},
		{"movWH", l_movWH},
		{NULL, NULL}
	};

	void registerString(lua_State* L)
	{
		luaL_newmetatable(L, "string");
		
		luaL_register(L, 0, stringFuncs);
		lua_pushvalue(L, -1);
		
		lua_setfield(L, -2, "__index");
		
		
		
		luaL_register(L, "string", stringFuncs);
	}
}

