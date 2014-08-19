//
//  Game.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 12/14/13.
//  Copyright (c) 2013 Ryan Oldis. All rights reserved.
//

#include "Game.h"
#include "MemoryManager.h"

#include "Script.h"
#include "Graphics.h"
#include "Computer.h"
#include "Input.h"
//#include "Audio.h"
#include "Tree.h"

#include "Entity.h"

namespace sinnca
{
	void game::startUp(const char* path)
	{
		memoryManager->start();
		
		// Setup lua scripting
		Script->setVar("ENGINE VERSION", "0.1.0 : Development");
		
		// Start opengl graphics
		Graphics->init(glW, glH);
		
		// Get Hardware and Software information
		Computer->getCompInfo();
		
		// We need to be able to interact with the game
		// but not on mobile devices
#if snMobile == 0
		Input->setupKeys();
#endif
		
		// Time for Audio!
		//Audio->init();
		
		// Lastly, make the root node that forms the foundation of the game
		Tree->setup(path);
		
		//createEntity("player");
	}
	
	void game::loopItr()
	{
		// first check the inputs
		Input->update();
		
		// update the current scene
		Tree->currentScene->update();
		
		// draw!
		Graphics->render();
	}
	
	void game::update()
	{
		// update the current scene
		Tree->currentScene->update();
	}
	void game::render()
	{
		// draw!
		Graphics->render();
	}
	
	
	void game::cleanUp()
	{
		
	}
}