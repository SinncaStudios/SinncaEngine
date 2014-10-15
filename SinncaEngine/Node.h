//
//  Node.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 11/29/13.
//  Copyright (c) 2013 Ryan Oldis. All rights reserved.
//

#ifndef SinncaEngine_Node_h
#define SinncaEngine_Node_h

#include "Types.h"
#include "Color.h"
#include "List.h"
#include "Script.h"
#include "Palette.h"

#include "TimeKeeping.h"

namespace sinnca
{


	class node
	{
	protected:
		
		// parent node and children nodes (obvious, I know...)
		node* parent;
		linkList<node*> children;
		int noOfChildren;
		
		std::string name;
		std::string behavior;
		
		
		bool draw;
		
		
	public:
		
		point pos, rot, scl;
		color* col;
		
		node()
		{
			parent = nullptr;
			
			noOfChildren = 0;
			draw = true;
			col = &Palette->white;
		}
		virtual ~node()
		{
			// deallocate children
			//children.clear();
		}
		
		virtual void update()
		{
			for (linkList<node*>::iterator i = children.begin(); i != children.end(); ++i)
			{
				(*i)->update();
			}
		}
		
		void setName(std::string n)
		{
			name = n;
		}
		
		bool willDraw()
		{
			return draw;
		}
		
		virtual void render()
		{
			
		}
		
		node* getParent()
		{
			return parent;
		}
		void setParent(node* np)
		{
			if (parent != NULL)
			{
				removeChild(this);
			}
			parent = np;
		}
		void addChild(node* ch)
		{
			ch->setParent(this);
			
			children.pushFront(ch);
			noOfChildren++;
		}
		void removeChild(node* ch)
		{
			children.remove(ch);
			noOfChildren--;
		}
		
		
		friend class scene;
		friend class entity;
		friend class grid;
		friend class camera;
		
	};
	
	static node* checkNode(int ind)
	{
		void* ud = 0;
		
		// check for table object
		luaL_checktype(Script->getState(), ind, LUA_TTABLE);
		
		// push the key we're looking for (in this case, it's "__self")
		lua_pushstring(Script->getState(), "__self");
		// get our table
		lua_gettable(Script->getState(), ind);
		
		// cast userdata pointer to "Node" type
		ud = dynamic_cast<node*>((node*)lua_touserdata(Script->getState(), -1));
		luaL_argcheck(Script->getState(), ud != 0, ind, "Incompatible 'node' type...");
		
		return *((node**)ud);
	}
	
	static int l_setParent(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 2)
		{
			return luaL_error(L, "You need to provide one node to be made the parent of this...");
		}
		
		node* nd = checkNode(1);
		nd->setParent(checkNode(2));
		
		return 0;
	}
	
	static int l_addChild(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n < 2)
		{
			return luaL_error(L, "You need to provide at least one other node to add. This function can handle batch adding of nodes.");
		}
		
		node* nd = checkNode(1);
		for (int i = 2; i < n; i++)
		{
			nd->addChild(checkNode(i));
		}
		
		return 0;
	}
	
	static int l_removeChild(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n < 2)
		{
			return luaL_error(L, "You need to provide at least one other node to remove. This function can handle batch removal of nodes.");
		}
		
		node* nd = checkNode(1);
		for (int i = 2; i < n; i++)
		{
			nd->removeChild(checkNode(i));
		}
		
		return 0;
	}
	
	static int l_setG(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n == 4)
		{
			node* nd = checkNode(1);
			
			nd->pos.x = lua_tonumber(L, 2);
			nd->pos.y = lua_tonumber(L, 3);
			nd->pos.z = lua_tonumber(L, 4);
		}
		return 0;
	}
	
	static int l_setR(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n == 4)
		{
			node* nd = checkNode(1);
			
			nd->rot.x = lua_tonumber(L, 2);
			nd->rot.y = lua_tonumber(L, 3);
			nd->rot.z = lua_tonumber(L, 4);
		}
		return 0;
	}
	
	static int l_setS(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n == 4)
		{
			node* nd = checkNode(1);
			
			nd->scl.x = lua_tonumber(L, 2);
			nd->scl.y = lua_tonumber(L, 3);
			nd->scl.z = lua_tonumber(L, 4);
		}
		return 0;
	}
	
	static int l_movG(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n == 4)
		{
			node* nd = checkNode(1);
			
			nd->pos.x = (lua_tonumber(L, 2) * TimeKeeper->withDeltaTime());
			nd->pos.y = (lua_tonumber(L, 3) * TimeKeeper->withDeltaTime());
			nd->pos.z = (lua_tonumber(L, 4) * TimeKeeper->withDeltaTime());
		}
		return 0;
	}
	
	static int l_movR(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n == 4)
		{
			node* nd = checkNode(1);
			
			nd->rot.x = (lua_tonumber(L, 2) * TimeKeeper->withDeltaTime());
			nd->rot.y = (lua_tonumber(L, 3) * TimeKeeper->withDeltaTime());
			nd->rot.z = (lua_tonumber(L, 4) * TimeKeeper->withDeltaTime());
		}
		return 0;
	}
	
	static int l_movS(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n == 4)
		{
			node* nd = checkNode(1);
			
			nd->scl.x = (lua_tonumber(L, 2) * TimeKeeper->withDeltaTime());
			nd->scl.y = (lua_tonumber(L, 3) * TimeKeeper->withDeltaTime());
			nd->scl.z = (lua_tonumber(L, 4) * TimeKeeper->withDeltaTime());
		}
		return 0;
	}
	
	static int l_getPos(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n == 1)
		{
			node* nd = checkNode(1);
			
			lua_pushnumber(L, nd->pos.x);
			lua_pushnumber(L, nd->pos.y);
			lua_pushnumber(L, nd->pos.z);
		}
		
		return 3;
	}
	
	static int l_getRot(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n == 1)
		{
			node* nd = checkNode(1);
			
			lua_pushnumber(L, nd->rot.x);
			lua_pushnumber(L, nd->rot.y);
			lua_pushnumber(L, nd->rot.z);
		}
		
		return 3;
	}
	
	static int l_getScl(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n == 1)
		{
			node* nd = checkNode(1);
			
			lua_pushnumber(L, nd->scl.x);
			lua_pushnumber(L, nd->scl.y);
			lua_pushnumber(L, nd->scl.z);
		}
		
		return 3;
	}
	
	static int l_setColor(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 2)
		{
			return luaL_error(L, "You need to provide a Color, Texture, or Material class...");
		}
		
		node* nd = checkNode(1);
		nd->col = checkColor(2);
		
		return 0;
	}
	
	static const luaL_Reg nodeFuncs[] = {
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
	
}
#endif
