//
//  AssetManager.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 2/22/15.
//  Copyright (c) 2015 Ryan Oldis. All rights reserved.
//

#include "AssetManager.h"

#include "Entity.h"
#include "Grid.h"
#include "Image.h"
#include "Texture.h"
#include "Source.h"
#include "Buffer.h"
#include "Action.h"
#include "Font.h"

namespace sinnca
{
	void assetManager::init(uint size)
	{
		entityStorage = new pool(sizeof(entity), alignof(entity), sizeof(entity) * size);
		//sceneStorage?
		colorStorage = new pool(sizeof(color), alignof(color), sizeof(color) * size);
		imageStorage = new pool(sizeof(image), alignof(image), sizeof(image) * size);
		textureStorage = new pool(sizeof(texture), alignof(texture), sizeof(texture) * size);
		sourceStorage = new pool(sizeof(source), alignof(source), sizeof(source) * size);
		bufferStorage = new pool(sizeof(buffer), alignof(buffer), sizeof(buffer) * size);
		gridStorage = new pool(sizeof(grid), alignof(grid), sizeof(grid) * size);
		actionStorage = new pool(sizeof(action), alignof(action), sizeof(action) * size);
		fontStorage = new pool(sizeof(font), alignof(font), sizeof(font) * 4);
		
	}
	
	void assetManager::shutDown()
	{
		delete entityStorage;
		delete colorStorage;
		delete imageStorage;
		delete textureStorage;
		delete sourceStorage;
		delete bufferStorage;
		delete gridStorage;
		delete actionStorage;
		delete fontStorage;
	}
}