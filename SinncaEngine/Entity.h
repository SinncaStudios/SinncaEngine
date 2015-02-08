//
//  Entity.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 2/9/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__Entity__
#define __SinncaEngine__Entity__

#include <iostream>
#include "Script.h"
#include "Node.h"
#include "RenderObj.h"

namespace sinnca
{
	class entity : public node
	{
	  
		//point pos, rot, scl;
		
		renderObj* m;

	public:
		
		//when it's time to specify a lua metatable, this will be looked up
		static constexpr auto metatable = "entity";
		
		entity(std::string n);
		~entity();
		
		void update();
		
		void render();
		void* operator new(size_t s, std::string n);
		void operator delete(void* p);
	  
	};
	
#define createEntity(a) new(a)entity(a)
	entity* checkEntity(int ind);
	
	void registerEntity(lua_State* L);
}

#endif /* defined(__SinncaEngine__Entity__) */
