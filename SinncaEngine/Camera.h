//
//  Camera.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 2/10/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__Camera__
#define __SinncaEngine__Camera__

#include <iostream>
#include "Types.h"
#include "Node.h"

namespace sinnca
{
	#define Camera (camera::Instance())
	class camera : public node
	{
		
	public:
		
		static constexpr auto metatable = "camera";
		
		//point pos;
		//point rot;
		
		point zoom;
		
		camera();
		~camera();
		static camera* Instance();
		
		void look();
		void look2D();
		
		void render();
		
	protected:
		static camera* _instance;
		
	};
}

#endif /* defined(__SinncaEngine__Camera__) */
