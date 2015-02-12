//
//  GuiMenu.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 3/16/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef SinncaEngine_GuiMenu_h
#define SinncaEngine_GuiMenu_h

#include "GuiWidget.h"

namespace sinnca
{
	class guiMenu : public guiWidget
	{
	public:
		
		guiMenu(std::string n);
		
		//void setName(std::string n);
		void update();
		void render();
		
		void* operator new(size_t s, std::string n);
		void operator delete(void* p);
		
	};
	
	#define createGuiMenu(a) new(a)guiMenu(a)
	void registerGuiMenu();
}

#endif
