//
//  GuiWidget.c
//  SinncaEngine
//
//  Created by Ryan Oldis on 3/17/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "GuiWidget.h"
#include "Tree.h"

namespace sinnca
{
	void* guiWidget::operator new(size_t s, std::string n)
	{
		guiWidget* wd = Script::createObject<guiWidget>(Tree::guiStorage);
		
		Script::setGlobal(n);
		return (void*)wd;
	}
	
	void guiWidget::operator delete(void *p)
	{
		Tree::guiStorage->deallocate(p);
	}
	
	static int newWidget(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 2)
		{
			return luaL_error(L, "You need to name this widget...");
		}
		
		guiWidget* wt = createGuiWidget(lua_tostring(L, 2));
		
		Tree::currentScene->guiManager->addChild(wt);
		return 1;
	}
	
	
	static const luaL_Reg widgetFuncs[] = {
		{"new", newWidget},
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
	
	
	void registerWidget(lua_State* L)
	{
		Script::registerType<guiWidget>(widgetFuncs);
	}
}
