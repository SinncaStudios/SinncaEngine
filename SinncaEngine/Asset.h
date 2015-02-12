//
//  Asset.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 1/30/15.
//  Copyright (c) 2015 Ryan Oldis. All rights reserved.
//

#ifndef SinncaEngine_Asset_h
#define SinncaEngine_Asset_h

#include "Types.h"

namespace sinnca
{
	class asset
	{
	protected:
		
		std::string path;
		
	public:
		
		virtual void load(std::string p) = 0;
	};
}

#endif
