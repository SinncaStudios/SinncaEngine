//
//  Grid.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 2/10/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__Grid__
#define __SinncaEngine__Grid__

#include <iostream>
#include "Node.h"
#include "Texture.h"
#include "LinearAlloc.h"

namespace sinnca
{
	class tile: public node
	{
		int pos[2];
		int xy[2];
		bool solid;
		
		texture* tex;
		
	public:
		friend class grid;
		
		tile();
		void setTex(texture* t);
		int getX();
		int getY();
		bool getSolid();
		texture* getTex();
		void render();
		
		
	};
	
	class grid: public node
	{
		
		float tileX, tileY; // the size of the tiles
		int size[2];
		
		tile** data; // need container with random access
		linear* dataSource; // ...and a data source
		
		
	public:
		
		//float xy[2];
		bool iso; // isometric?
		friend class tile;
		
		grid(std::string n, int xSize, int ySize, bool io);
		~grid();
		
		void callBehavior();
		void setSolid(int x, int y, bool s);
		void setTexture(int x, int y, texture* t);
		bool checkBounds(int& x, int& y);
		void getTileXY(int x, int y, int& _x, int& _y);
		int getX();
		int getY();
		tile* getTile(int x, int y);
		
		void render();
		
		void* operator new(size_t s, std::string n);
		void operator delete(void* p);
		
	};
	
	#define createGrid(a, b, c, d) new(a)grid(a, b, c, d)
	
	void registerGrid(lua_State* L);
}

#endif /* defined(__SinncaEngine__Grid__) */
