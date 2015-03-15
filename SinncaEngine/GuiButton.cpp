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

	guiButton::guiButton(std::string n) : guiWidget(n)
	{
		
		useAlph = false;
	}

	void guiButton::update()
	{
		Script::getGlobal(name);
		
		Script::getLocal(-1, "update");
		//Script::checkType(2, LUA_TFUNCTION);
		
		Script::call(0, 0);
	}

	bool guiButton::checkbounds()
	{
		
		// check if in button bounds
		if ((Input::Mouse::x >= pos.x) && (Input::Mouse::x <= pos.x + scl.x) && (Input::Mouse::y >= pos.y) && (Input::Mouse::y <= pos.y + scl.y))
		{
			if (useAlph == true && col != NULL)
			{
				
				// mouse coords - button coords = local coords
				int localX = Input::Mouse::x - pos.x;
				int localY = Input::Mouse::y - pos.y;
				
				// percent of local to size = tex coords
				float percX = (1 / scl.x) * localX;
				float percY = (1 / scl.y) * localY;
				
				// get percentage based on texture coords
				float texCoX = percX / m->getVertices()->texco[0];
				float texCoY = percY / m->getVertices()->texco[1];
				
				ui32* pix = col->getPixel(texCoX * col->getWidth(), texCoY * col->getHeight());
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
		
		return false;
		
	}
	
	void guiButton::render()
	{
		
	}
	
	void* guiButton::operator new(size_t s, std::string n)
	{
		guiButton* bn = Script::createObject<guiButton>();
		
		Script::setGlobal(n);
		Tree::currentScene->guiManager->addChild(bn);
		return (void*)bn;
	}
	
	void guiButton::operator delete(void *p)
	{
		Heap->deallocate(p);
	}


	static int newButton(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n > 2)
		{
			return luaL_error(L, "You need to name this button...");
		}
		
		Script::checkTable(1);
		createGuiButton(lua_tostring(L, 2));
		return 0;
	}

	static int hover(lua_State* L)
	{
		int n = lua_gettop(L);
		
		if (n == 1)
		{
			guiButton* bn = Script::checkType<guiButton>(1);
			
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

	void registerGuiButton(lua_State* L)
	{
		Script::registerType<guiButton>(buttonFuncs);
	}
}

