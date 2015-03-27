//
//  AssetManager.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 2/22/15.
//  Copyright (c) 2015 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__AssetManager__
#define __SinncaEngine__AssetManager__

#include "Asset.h"
#include "Types.h"
#include "PoolAlloc.h"
#include <vector>

namespace sinnca
{
	class assetManager
	{
		uint noOfResources;
		
	public:
		pool* entityStorage;
		pool* sceneStorage;
		pool* colorStorage;
		pool* imageStorage;
		pool* textureStorage;
		pool* sourceStorage;
		pool* bufferStorage;
		pool* gridStorage;
		pool* actionStorage;
		pool* fontStorage;
		
		// reference keeping
		std::vector<void*> nodeRef;
		std::vector<void*> entityRef;
		std::vector<void*> gridRef;
		std::vector<void*> sceneRef;
		std::vector<void*> imageRef;
		std::vector<void*> colorRef;
		std::vector<void*> textureRef;
		std::vector<void*> sourceRef;
		std::vector<void*> bufferRef;
		std::vector<void*> actionRef;
		std::vector<void*> fontRef;
		
		
		void init(uint size = 50);
		void shutDown();
	};
}

#endif /* defined(__SinncaEngine__AssetManager__) */
