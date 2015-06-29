//
//  OptTree.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 6/21/15.
//  Copyright (c) 2015 Ryan Oldis. All rights reserved.
//

#ifndef SinncaEngine_OptTree_h
#define SinncaEngine_OptTree_h

#include "Node.h"

namespace sinnca
{
	class optTree
	{
		// when the objects in a leaf node exceed this limit, the node will subdivide
		uint objectsPerLeaf;
		
		struct leaf : public node
		{
			leaf* subNodes;
			uint level;
			
			virtual void update()
			{
				for (auto i = children.begin(); i != children.end(); ++i)
				{
					(*i)->update();
				}
			}
			
			virtual bool subdivide()
			{
				// this is virtual, so just return true
				return true;
			}
		}
		
	};
}

#endif
