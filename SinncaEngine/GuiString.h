//
//  GuiString.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 3/16/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef SinncaEngine_GuiString_h
#define SinncaEngine_GuiString_h

#include "GuiWidget.h"

namespace sinnca
{
	class guiString : public guiWidget
	{
		std::string str;
		font* ft;
		
		
	public:
		
		static constexpr auto metatable = "guiString";
		
		guiString(std::string n);
		~guiString();
		
		void render();
		void setFont(font* f);
		void setStr(std::string s);
		
		void* operator new(size_t s, std::string n);
		void operator delete(void* p);
		
	};
	
	#define createGuiString(a) new(a)guiString(a)
	void registerString(lua_State* L);
}

#endif
