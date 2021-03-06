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
#include "Entity.h"
#include "Font.h"
#include "Image.h"
#include "Texture.h"
#include "Grid.h"
#include "Scene.h"
#include "Tree.h"

namespace sinnca
{
	
	
	
	void luaScript::bindFunctions()
	{
		std::string tempPath = Computer->getResourcePath().c_str();
		setVar("resourcePath", tempPath + "/");
		
		lua_register(L, "keyDown", l_keyDown);
		
		// register node classes
		registerEntity(L);
		registerScene(L);
		registerGrid(L);
		registerTree(L);
		
		// register color classes
		registerImage(L);
		registerTexture(L);
		
		// register gui classes
		registerFont(L);
	}
	
}