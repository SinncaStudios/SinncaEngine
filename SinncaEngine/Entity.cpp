//
//  Entity.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 2/9/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "Entity.h"

#include "Tree.h"
#include "Heap.h"
#include "Graphics.h"
#include "Palette.h"
#include "Texture.h"

namespace sinnca
{
	entity::entity(std::string n)
	{
		name = n;
		
		pos.x = 0.0f;
		pos.y = 0.0f;
		pos.z = 0.0f;
		
		rot.x = 0.0f;
		rot.y = 0.0f;
		rot.z = 0.0f;
		
		scl.x = 40.0f;
		scl.y = 40.0f;
		scl.z = 1.0f;
		
		col = &Palette::white;
		m = NULL;
		Tree::currentScene->addChild(this);
		parent = Tree::currentScene;
		
	}
	
	entity::~entity()
	{
		//Heap->deallocateDelete(col);
	}
	
	void entity::update()
	{
		
		for (linkList<node*>::iterator i = children.begin(); i != children.end(); ++i)
		{
			(*i)->update();
		}
		
		Script::getGlobal(name);
		
		Script::getLocal(-1, "update");
		Script::call(0, 0);
		
	}
	
	
	void entity::render()
	{
		Graphics::loadIdentity();
		
		for (linkList<node*>::iterator i = children.begin(); i != children.end(); ++i)
		{
			(*i)->render();
		}
	
		Graphics::move(pos);
		Graphics::rotate(rot);
		
		
		col->bind();
		
		
		Graphics::scale(scl);
		//glPopMatrix();
		
		
		
		if (m == NULL)
		{
			if (Tree::currentScene->pers() == 0)
			{
				Graphics::square->render();
				
			} else {
				
			}
			
		}
		
	}
	
	
	void* entity::operator new(size_t s, std::string n)
	{
		/*
		 Don't look at me
		 It's way too soon to see
		 What's gonna be
		 Don't look at me
		 */
		
		//Create object in lua
		entity* en = Script::createObject<entity>();
		
		Script::setGlobal(n);
		Tree::currentScene->entityRef.push_back(en);
		Tree::currentScene->nodeRef.push_back(en);
		return ((void*)en);
		
		/*
		 All my life
		 I never knew
		 What I could be, what I could do
		 Then we were new
		 */
		
	}
	void entity::operator delete(void *p)
	{
		if (Tree::currentScene->entityStorage != NULL)
		{
			Tree::currentScene->entityStorage->deallocate(p);
			
		} else {
			
			Heap->deallocate(p);
		}
		
	}
	
	
	static int l_newEntity(lua_State* L)
	{
		
		int n = lua_gettop(L);
		if (n != 2)
		{
			return luaL_error(L, "You need to name this entity...");
		}
		
		Script::checkTable(1);
		createEntity(luaL_checkstring(L, 2));
		return 0;
	}
	
	
	static const luaL_Reg entityFuncs[] = {
		
		{"new", l_newEntity},
		
		
		// node functions
		{"setParent", l_setParent},
		{"addChild", l_addChild},
		{"removeChild", l_removeChild},
		
		
		{"setG", l_setG},
		{"setR", l_setR},
		{"setS", l_setS},
		
		{"movG", l_movG},
		{"movR", l_movR},
		{"movS", l_movS},
		
		{"movGWithoutDeltaTimeButDontBecauseItsBadProgrammingHabit", l_movGWithoutDeltaTimeButDontBecauseItsBadProgrammingHabit},
		
		{"getG", l_getPos},
		{"getR", l_getRot},
		{"getS", l_getScl},
		
		{"setCol", l_setColor},
		
		{NULL, NULL}
	};
	void registerEntity(lua_State* L)
	{
		Script::registerType<entity>(entityFuncs);
	}
	
}