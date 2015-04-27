//
//  Binding.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 12/12/13.
//  Copyright (c) 2013 Ryan Oldis. All rights reserved.
//

#include "Script.h"


#include "Computer.h"
#include "Input.h"
#include "DigitalButton.h"
#include "Entity.h"
#include "Font.h"
#include "Image.h"
#include "Texture.h"
#include "Grid.h"
#include "Scene.h"
#include "Tree.h"
#include "Buffer.h"
#include "Source.h"

namespace sinnca
{
	
	namespace Script
	{
		void bindFunctions()
		{
			std::string tempPath = Computer::getResourcePath().c_str();
			setVar("resourcePath", tempPath + "/");
			
			lua_register(L, "keyDown", l_keyDown);
			registerButton(L);
			
			// register node classes
			registerEntity(L);
			registerScene(L);
			registerGrid(L);
			registerTree(L);
			registerSource(L);
			
			// register color classes
			registerType<color>(colorFuncs);
			registerImage(L);
			registerTexture(L);
			
			// register sound classes
			registerBuffer(L);
			
			// register gui classes
			registerFont(L);
			
			
		}
	}
	
}