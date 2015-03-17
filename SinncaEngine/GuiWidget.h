//
//  GuiWidget.h
//  Sinnca Engine
//
//  Created by Ryan Oldis on 2/21/12.
//  Copyright (c) 2012 Sinnca Studios. All rights reserved.
//

#ifndef Sinnca_Engine_GuiWidget_h
#define Sinnca_Engine_GuiWidget_h

#include "List.h"
#include "Node.h"

#include "Sprite.h"
#include "Texture.h"
#include "Font.h"
#include "Palette.h"


namespace sinnca
{
	class guiWidget: public node
	{
	protected:
		
		renderObj* m;
		
	public:
		
		static constexpr auto metatable = "guiWidget";
		
		guiWidget(std::string n)
		{
			draw = true;
			
			pos.x = 0;
			pos.y = 0;
			
			col = &Palette::white;
			
			scl.x = 20;
			scl.y = 20;
			
			m = Graphics::square;
			
			//name = n;
			
		}
		
		
		void update()
		{
			for (linkList<node*>::iterator i = children.begin(); i != children.end(); ++i)
			{
				(*i)->update();
			}
			
			Script::getGlobal(name);
			
			Script::getLocal(-1, "update");

			
			Script::call(0, 0);
		}
		
		
		void render()
		{
			/*
			glPushMatrix();
			
			if (tex == NULL)
			{
				glBindTexture(GL_TEXTURE_2D, 0);
			} else {
				tex->bind();
			}
			
			glTranslatef(xy[0]/2, xy[1]/2, 0);
			
			
			glColor4f(color[0], color[1], color[2], color[3]);
			glScalef(scl[0]/2, scl[1]/2, 0);
			//Graphics->drawSquare();
			
			for (linkList<guiWidget*>::iterator i = children.begin(); i != children.end(); ++i)
			{
				(*i)->render();
			}
			
			glPopMatrix();*/
		}
		
		void addChild(guiWidget* ch)
		{
			ch->setParent(this);
			
			children.pushFront(ch);
			noOfChildren++;
		}
		
		void* operator new(size_t s, std::string n)
		{
			guiWidget* wd = Script::createObject<guiWidget>();
			
			Script::setGlobal(n);
			return (void*)wd;
		}
		#define createGuiWidget(a) new(a)guiWidget(a)
		
		
		void operator delete(void* p)
		{
			#warning "needs a specific allocator to alloc and dealloc"
			Heap->deallocate(p);
		}
	};

	void registerWidget(lua_State* L);
	

}


#endif
