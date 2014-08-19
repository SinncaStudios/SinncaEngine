//
//  GuiMenu.cpp
//  Sinnca Engine
//
//  Created by Ryan Oldis on 5/24/12.
//  Copyright (c) 2012 Sinnca Studios. All rights reserved.
//

#include "GuiMenu.h"

#include "Graphics.h"

namespace sinnca
{

	guiMenu::guiMenu()
	{
		draw = true;
		
		xy[0] = 0;
		xy[1] = 0;
		
		col = &Palette->white;
		
		scl[0] = 20;
		scl[1] = 20;
		
		//name = n;
	}

	void guiMenu::update()
	{
		
	}

	void guiMenu::render()
	{
		
		glPushMatrix();
		// render widget first
			// menus have no widget to render
		
		// set scissor area
		Graphics->enableScissor(xy[0], xy[1], scl[0], scl[1]);
		
		// render contents
		for (linkList<guiWidget*>::iterator i = children.begin(); i != children.end(); ++i)
		{
			(*i)->render();
		}
		
		glPopMatrix();
	}
}

