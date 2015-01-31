//
//  Grid.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 2/10/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "Grid.h"
#include "Tree.h"
#include "Input.h"
#include "Camera.h"
#include "Palette.h"
#include "MemoryManager.h"


#include <math.h>

namespace sinnca
{
	
	tile::tile()
	{
		solid = false;
		
		col = &Palette->white;
		
	}
	
	void tile::setTex(texture *t)
	{
		col = t;
	}
	
	int tile::getX()
	{
		return xy[0];
	}
	int tile::getY()
	{
		return xy[1];
	}
	bool tile::getSolid()
	{
		return solid;
	}
	color* tile::getTex()
	{
		return col;
	}
	
	void tile::render()
	{
		
		col->bind();
		
		Graphics->square->render();
	}
	
	
	//
	// Start grid functions
	//
	// http://stackoverflow.com/questions/6915555/how-to-transform-mouse-location-in-isometric-tiling-map
	
	grid::grid(std::string n, int xSize, int ySize, bool io)
	{
		name = n;
		iso = io;
		
		pos.x = 0.0;
		pos.y = 0.0;
		pos.z = 0.0;
		
		tileX = 128;
		tileY = 128;
		
		dataSource = new(memoryManager->allocate(sizeof(linear))) linear(sizeof(tile) * (xSize + 1) * (ySize + 1));
		
		data = dataSource->allocateArray<tile*>(xSize);
		//data = new (dataSource->allocate(sizeof(tile), __alignof(tile))) tile*[xSize];
		for (int i = 0; i < xSize; ++i)
		{
			data[i] = dataSource->allocateArray<tile>(ySize);
			//data[i] = new (dataSource->allocate(sizeof(tile), __alignof(tile))) tile[ySize];
		}
		
		// now we can loop through properly
		for (int i = 0; i < xSize; i++)
		{
			for (int j = 0; j < ySize; j++)
			{
				
				data[i][j].parent = this; // a tile's parent must always be the grid that creates it
				
				data[i][j].pos[0] = i;
				data[i][j].pos[1] = j;
				
				data[i][j].xy[0] = (j - i) * tileX / 2;
				data[i][j].xy[1] = (j + i) * tileY / 4;
				
				Tree->currentScene->nodeRef.push_back(&data[i][j]);
				
			}
		}
		
		// tell our grid how big it is
		size[0] = xSize;
		size[1] = ySize;
		
		Tree->currentScene->addChild(this);
		
	}
	
	grid::~grid()
	{
		//delete[] data;
		dataSource->clear();
	}
	
	void grid::callBehavior()
	{
		for (int i = 0; i < noOfChildren; i++)
		{
			//children[i]->callBehavior();
		}
		
		Script->getGlobal(name);
		
		Script->getLocal(-1, "update");
		//Script->checkType(2, LUA_TFUNCTION);
		
		Script->call(0, 0);
		
		
	}
	
	void grid::setSolid(int x, int y, bool s)
	{
		data[x][y].solid = s;
	}
	
	void grid::setTexture(int x, int y, texture *t)
	{
		data[x][y].setTex(t);
	}
	
	bool grid::checkBounds(int &x, int &y)
	{
		
		int _x = Input::Mouse::x + pos.x - Camera->pos.x * 2;
		int _y = Input::Mouse::y - pos.y - Camera->pos.y * 2;
		
		double d_x = ((2 * _y + _x) / 2.0);
		double d_y = ((2 * _y - _x) / 2.0);
		
		x = round(d_x / tileX) - 1;
		y = round(d_y / tileY);
		
		
		if (x > size[0] && x < 0 && y > size[1] && y < 0)
		{
			return false;
		} else {
			
			return true;
		}
	}
	
	void grid::getTileXY(int x, int y, int& _x, int& _y)
	{
		if (x > size[0]-1 || x < 0 || y > size[1]-1 || y < 0)
		{
			return;
		}
		
		_x = data[x][y].getX();
		_y = data[x][y].getY();
	}
	
	int grid::getX()
	{
		return size[0];
	}
	int grid::getY()
	{
		return size[1];
	}
	
	tile* grid::getTile(int x, int y)
	{
		return &data[x][y];
	}
	
	
	
	void grid::render()
	{
		
		glBindTexture(GL_TEXTURE_2D, 0);
		
		if (iso == false)
		{
			for (int i = 0; i < size[0]; i++)
			{
				for (int j = 0; j < size[1]; j++)
				{
					
					
					Graphics->loadIdentity();
					//glPushMatrix();
					
					Graphics->move(j * tileX, -i * tileY, 0.0);
					Graphics->scale(tileX, tileY, 0);
					data[i][j].render();
					
					//glPopMatrix();
				}
			}
			
			
		} else {
			
			for (int i = 0; i < size[0]; i++)
			{
				for (int j = 0; j < size[1]; j++)
				{
					//glPushMatrix();
					Graphics->loadIdentity();
					
					//glTranslatef(data[i][j].xy[0], data[i][j].xy[1], 0.0);
					Graphics->move((j - i) * tileX / 2, (j + i) * tileY / 4, 0.0);
					Graphics->scale(tileX, tileY, 0);
					data[i][j].render();
					
					//glPopMatrix();
				}
			}
			
		}
	}
	
	void* grid::operator new(size_t s, std::string n)
	{
		Script->newBlankTable();
		
		Script->pushValue(1);
		Script->setMetaTable(-2);
		
		Script->pushValue(1);
		Script->setField(1, "__index");
		
		//entity** en = Script->newUserdata<entity*>();
		grid** gd = (grid**)lua_newuserdata(Script->getState(), sizeof(grid*));
		if (Tree->currentScene->gridStorage != NULL)
		{
			*gd = (grid*)Tree->currentScene->gridStorage->allocate((unsigned int)s, __alignof(grid));
			
		} else {
			
			*gd = (grid*)Heap->allocate((unsigned int)s, __alignof(grid));
		}
		
		Script->getMetaTable("grid");
		Script->setMetaTable(-2);
		
		Script->setField(-2, "__self");
		
		
		Script->setGlobal(n);
		Tree->currentScene->gridRef.push_back(*gd);
		Tree->currentScene->nodeRef.push_back(*gd);
		return ((void*)*gd);
	}
	
	void grid::operator delete(void *p)
	{
		if (Tree->currentScene->gridStorage != NULL)
		{
			Tree->currentScene->gridStorage->deallocate(p);
			
		} else {
			
			Heap->deallocate(p);
		}
		
	}
	
	//
	// Lua functions
	//
	
	grid* checkGrid(lua_State* L, int ind)
	{
		void* ud = 0;
		
		// check for table object
		luaL_checktype(L, ind, LUA_TTABLE);
		
		// push the key we're looking for (in this case, it's "__self")
		lua_pushstring(L, "__self");
		// get our table
		lua_gettable(L, ind);
		
		// cast userdata pointer to "Node" type
		ud = dynamic_cast<grid*>((grid*)lua_touserdata(L, -1));
		luaL_argcheck(L, ud != 0, ind, "Incompatible 'node' type...");
		
		return *((grid**)ud);
	}
	
	static int l_newGrid(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 5)
		{
			return luaL_error(L, "You need to name this grid...");
		}
		
		Script->checkTable(1);
		createGrid(lua_tostring(L, 2), (int)lua_tointeger(L, 3), (int)lua_tointeger(L, 4), lua_toboolean(L, 5));
		return 0;
	}
	
	static int l_setTex(lua_State* L)
	{
		int n = lua_gettop(L);
		grid* gr = checkGrid(L, 1);
		
		if (n == 4)
		{
			gr->setTexture((int)lua_tointeger(L, 2), (int)lua_tointeger(L, 3), checkTexture(4));
			
		}
		
		return 1;
	}
	
	static int l_getTileXY(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n == 3)
		{
			grid* gr = checkGrid(L, 1);
			int x, y;
			gr->getTileXY((int)lua_tointeger(L, 2), (int)lua_tointeger(L, 3), x, y);
			
			lua_pushinteger(L, x);
			lua_pushinteger(L, y);
		}
		
		return 2;
	}
	
	static int l_hover(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n == 1)
		{
			int _x, _y;
			grid* gr = checkGrid(L, 1);
			
			gr->checkBounds(_x, _y);
			lua_pushinteger(L, _x);
			lua_pushinteger(L, _y);
		}
		
		return 2;
	}
	
	static const luaL_Reg gridFuncs[] = {
		
		{"new", l_newGrid},
		{"setTex", l_setTex},
		{"hover", l_hover},
		{"getTileXY", l_getTileXY},
		
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
	
	void registerGrid(lua_State* L)
	{
		luaL_newmetatable(L, "grid");
		
		luaL_register(L, 0, gridFuncs);
		lua_pushvalue(L, -1);
		
		lua_setfield(L, -2, "__index");
		
		
		
		luaL_register(L, "grid", gridFuncs);
	}
	
}