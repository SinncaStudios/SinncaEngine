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
		
		guiButton();
		
		void update();
		bool checkbounds();
		//void render();
		
	};
	
	void registerGuiButton(lua_State* L);
}

#endif
