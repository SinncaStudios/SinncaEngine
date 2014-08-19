//
//  GuiWidget.h
//  Sinnca Engine
//
//  Created by Ryan Oldis on 2/21/12.
//  Copyright (c) 2012 Sinnca Studios. All rights reserved.
//

#ifndef Sinnca_Engine_GuiWidget_h
#define Sinnca_Engine_GuiWidget_h

#include "List.h"

#include "Sprite.h"
#include "Texture.h"
#include "Font.h"
#include "Palette.h"


namespace sinnca
{
	class guiWidget
	{
	protected:
		int xy[2];
		color* col;
		int scl[2];
		
		std::string name;
		
	public:
		
		guiWidget* parent;
		linkList<guiWidget*> children;
		
		sprite* rendOb;
		bool draw;
		
		guiWidget()
		{
			draw = true;
			
			xy[0] = 0;
			xy[1] = 0;
			
			col = &Palette->white;
			
			scl[0] = 20;
			scl[1] = 20;
			
			rendOb = Graphics->square;
			
			//name = n;
			
		}
		
		void setPos(int x, int y)
		{
			xy[0] = x;
			xy[1] = y;
		}
		
		void movPos(int x, int y)
		{
			xy[0] += x;
			xy[1] += y;
		}
		
		void setCol(float r, float g, float b, float a)
		{
			/*
			color[0] = r;
			color[1] = g;
			color[2] = b;
			color[3] = a;
			 */
		}
		
		void setScl(int x, int y)
		{
			scl[0] = x;
			scl[1] = y;
		}
		
		void movScl(int x, int y)
		{
			scl[0] += x;
			scl[1] += y;
		}
		
		void setName(std::string n)
		{
			name = n;
		}
		
		void update()
		{
			for (linkList<guiWidget*>::iterator i = children.begin(); i != children.end(); ++i)
			{
				(*i)->update();
			}
			
			Script->getGlobal(name);
			
			Script->getLocal(-1, "update");
			//Script->checkType(2, LUA_TFUNCTION);
			
			Script->call(0, 0);
		}
		
		
		void render()
		{
			/*
			glPushMatrix();
			
			if (tex == NULL)
			{
				glBindTexture(GL_TEXTURE_2D, 0);
			} else {
				tex->bind();
			}
			
			glTranslatef(xy[0]/2, xy[1]/2, 0);
			
			
			glColor4f(color[0], color[1], color[2], color[3]);
			glScalef(scl[0]/2, scl[1]/2, 0);
			//Graphics->drawSquare();
			
			for (linkList<guiWidget*>::iterator i = children.begin(); i != children.end(); ++i)
			{
				(*i)->render();
			}
			
			glPopMatrix();*/
		}
		
		
	};




	static guiWidget* checkWidget(lua_State* L, int ind)
	{
		void* ud = 0;
		
		// check for table object
		luaL_checktype(L, ind, LUA_TTABLE);
		
		// push the key we're looking for (in this case, it's "__self")
		lua_pushstring(L, "__self");
		// get our table
		lua_gettable(L, ind);
		
		// cast userdata pointer to "guiWidget" type
		ud = dynamic_cast<guiWidget*>((guiWidget*)lua_touserdata(L, -1));
		luaL_argcheck(L, ud != 0, ind, "Incompatible 'gui' type...");
		
		return *((guiWidget**)ud);
	}

	static int l_setXY(lua_State* L)
	{
		int n = lua_gettop(L);
		guiWidget* wd;
		
		if (n == 3)
		{
			wd = checkWidget(L, 1);
			
			wd->setPos((int)lua_tointeger(L, 2), (int)lua_tointeger(L, 3));
		}
		
		return 0;
	}
	static int l_movXY(lua_State* L)
	{
		int n = lua_gettop(L);
		
		if (n == 3)
		{
			guiWidget* wd = checkWidget(L, 1);
			
			wd->movPos((int)lua_tointeger(L, 2), (int)lua_tointeger(L, 3));
		}
		
		return 0;
	}

	static int l_setCol(lua_State* L)
	{
		int n = lua_gettop(L);
		
		if (n == 5)
		{
			guiWidget* wd = checkWidget(L, 1);
			
			wd->setCol(lua_tonumber(L, 2), lua_tonumber(L, 3), lua_tonumber(L, 4), lua_tonumber(L, 5));
		}
		
		return 0;
	}

	static int l_setWH(lua_State* L)
	{
		int n = lua_gettop(L);
		
		if (n == 3)
		{
			guiWidget* wd = checkWidget(L, 1);
			
			wd->setScl((int)lua_tointeger(L, 2), (int)lua_tointeger(L, 3));
		}
		
		return 0;
	}

	static int l_movWH(lua_State* L)
	{
		int n = lua_gettop(L);
		
		if (n == 3)
		{
			guiWidget* wd = checkWidget(L, 1);
			
			wd->movScl((int)lua_tointeger(L, 2), (int)lua_tointeger(L, 3));
		}
		
		return 0;
	}


	static int newWidget(lua_State* L)
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
		
		
		guiWidget** wt = (guiWidget**)lua_newuserdata(L, sizeof(guiWidget*));
		*wt = new guiWidget();
		
		(*wt)->setName(luaL_checkstring(L, 2));
		
		luaL_getmetatable(L, "widget");
		lua_setmetatable(L, -2);
		
		lua_setfield(L, -2, "__self");
		
		
		lua_setglobal(L, luaL_checkstring(L, 2));
		
		
		//Tree->currentScene->guiManager->children.pushBack(*wt);
		return 1;
	}


	static const luaL_Reg widgetFuncs[] = {
		{"new", newWidget},
		{"setXY", l_setXY},
		{"movXY", l_movXY},
		{"setCol", l_setCol},
		{"setWH", l_setWH},
		{"movWH", l_movWH},
		{NULL, NULL}
	};

	void registerWidget(lua_State* L);
	

}


#endif
