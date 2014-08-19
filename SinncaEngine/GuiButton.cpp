//
//  GuiButton.cpp
//  Sinnca Engine
//
//  Created by Ryan Oldis on 3/29/12.
//  Copyright (c) 2012 Sinnca Studios. All rights reserved.
//

#include "GuiButton.h"

#include "Node.h"
#include "Graphics.h"
#include "Input.h"
#include "Script.h"
#include "Tree.h"

namespace sinnca
{

	guiButton::guiButton()
	{
		draw = true;
		
		xy[0] = 1;
		xy[1] = 1;
		
		col = &Palette->white;
		
		scl[0] = 20;
		scl[1] = 20;
		
		rendOb = Graphics->square;
		
		//name = n;
		
		useAlph = false;
	}

	void guiButton::update()
	{
		Script->getGlobal(name);
		
		Script->getLocal(-1, "update");
		//Script->checkType(2, LUA_TFUNCTION);
		
		Script->call(0, 0);
	}

	bool guiButton::checkbounds()
	{
		/*
		// check if in button bounds
		if ((Input->m_x >= xy[0]) && (Input->m_x <= xy[0] + scl[0]) && (Input->m_y >= xy[1]) && (Input->m_y <= xy[1] + scl[1]))
		{
			if (useAlph == true && tex != NULL)
			{
				
				// mouse coords - button coords = local coords
				int localX = Input->m_x - xy[0];
				int localY = Input->m_y - xy[1];
				
				// percent of local to size = tex coords
				float percX = (1 / scl[0]) * localX;
				float percY = (1 / scl[1]) * localY;
				
				// get percentage based on texture coords
				float texCoX = percX / rendOb->vertices->tex->u;
				float texCoY = percY / rendOb->vertices->tex->v;
				
				GLubyte* pix = tex->getPixel(texCoX * tex->getW(), texCoY * tex->getH());
				if (pix[3] == 0x00)
				{
					return false;
					
				} else {
					return true;
				}
				
				
			} else {
				// then return true
				return true;
			}
			
			
		}
		 */
		return false;
		
	}

	guiButton* checkButton(lua_State* L, int ind)
	{
		void* ud = 0;
		
		// check for table object
		luaL_checktype(L, ind, LUA_TTABLE);
		
		// push the key we're looking for (in this case, it's "__self")
		lua_pushstring(L, "__self");
		// get our table
		lua_gettable(L, ind);
		
		// cast userdata pointer to "Node" type
		ud = dynamic_cast<guiButton*>((guiButton*)lua_touserdata(L, -1));
		luaL_argcheck(L, ud != 0, ind, "Incompatible 'gui' type...");
		
		return *((guiButton**)ud);
	}

	static int newButton(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n > 2)
		{
			return luaL_error(L, "You need to name this button...");
		}
		
		luaL_checktype(L, 1, LUA_TTABLE);
		
		
		lua_newtable(L);
		
		lua_pushvalue(L, 1);
		lua_setmetatable(L, -2);
		
		lua_pushvalue(L, 1);
		lua_setfield(L, 1, "__index");
		
		
		guiWidget** bn = (guiWidget**)lua_newuserdata(L, sizeof(guiButton*));
		*bn = new guiButton(/*luaL_checkstring(L, 2)*/);
		
		//(*bn)->setName(luaL_checkstring(L, 2));
		
		luaL_getmetatable(L, "button");
		lua_setmetatable(L, -2);
		
		lua_setfield(L, -2, "__self");
		
		
		lua_setglobal(L, luaL_checkstring(L, 2));
		
		
		Tree->currentScene->guiManager->children.pushBack(*bn);
		return 1;
	}

	static int hover(lua_State* L)
	{
		int n = lua_gettop(L);
		
		if (n == 1)
		{
			guiButton* bn = checkButton(L, 1);
			
			if (bn->checkbounds())
			{
				lua_pushboolean(L, 1);
			} else {
				lua_pushboolean(L, 0);
			}
		}
		
		return 1;
	}



	static const luaL_Reg buttonFuncs[] = {
		{"new", newButton},
		{"hover", hover},
		
		{"setXY", l_setXY},
		{"movXY", l_movXY},
		{"setCol", l_setCol},
		{"setWH", l_setWH},
		{"movWH", l_movWH},
		{NULL, NULL}
	};

	void registerButton(lua_State* L)
	{
		luaL_register(L, "button", buttonFuncs);
		
		lua_pushvalue(L, -1);
		lua_setfield(L, -2, "__index");
	}
}

