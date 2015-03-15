//
//  GuiMenu.cpp
//  Sinnca Engine
//
//  Created by Ryan Oldis on 5/24/12.
//  Copyright (c) 2012 Sinnca Studios. All rights reserved.
//

#include "GuiMenu.h"

#include "Graphics.h"
#include "Tree.h"

namespace sinnca
{

	guiMenu::guiMenu(std::string n) : guiWidget(n)
	{
		/*
		draw = true;
		
		pos.x = 0;
		pos.y = 0;
		
		col = &Palette->white;
		
		scl.x = 20;
		scl.y = 20;
		
		name = n;
		 */
	}

	void guiMenu::update()
	{
		
	}

	void guiMenu::render()
	{
		/*
		glPushMatrix();
		// render widget first
			// menus have no widget to render
		
		// set scissor area
		Graphics->enableScissor(pos.x, pos.y, scl.x, scl.y);
		
		// render contents
		for (linkList<node*>::iterator i = children.begin(); i != children.end(); ++i)
		{
			(*i)->render();
		}
		
		glPopMatrix();
		 */
	}
	
	void* guiMenu::operator new(size_t s, std::string n)
	{
		guiMenu* mu = Script::createObject<guiMenu>();
		
		Script::setGlobal(n);
		if (Tree::currentScene)
		{
			if (Tree::currentScene->guiManager != nullptr) {
				Tree::currentScene->guiManager->addChild(mu);
			}
		}
		return (void*)mu;
	}
	
	void guiMenu::operator delete(void *p)
	{
		Heap->deallocate(p);
	}
	
	
}

