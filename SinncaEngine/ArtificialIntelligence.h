//
//  ArtificialIntelligence.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 9/8/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__ArtificialIntelligence__
#define __SinncaEngine__ArtificialIntelligence__

#include <iostream>
#include "Node.h"
#include "Grid.h"



namespace sinnca
{
	enum aiState
	{
		dead = 0,
		idle = 1
	};
	
	class ai : public node
	{
		// the grid we will be using for pathfinding
		grid* map;
		
		// the player, used as a reference so that ai can follow or avoid
		node* player;

	public:
		
		void update();
		void render();
		
	};
}

#endif /* defined(__SinncaEngine__ArtificialIntelligence__) */
