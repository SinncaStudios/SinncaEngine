//
//  GuiButton.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 3/16/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef SinncaEngine_GuiButton_h
#define SinncaEngine_GuiButton_h

#include "GuiWidget.h"

namespace sinnca
{
	
	class guiButton : public guiWidget
	{
		
		bool useAlph;
		
	public:
		
		guiButton(std::string n);
		
		void update();
		bool checkbounds();
		void render();
		
		void* operator new(size_t s, std::string n);
		void operator delete(void* p);
		
	};
	
	#define createGuiButton(a) new(a)guiButton(a)
	void registerGuiButton(lua_State* L);
}

#endif
