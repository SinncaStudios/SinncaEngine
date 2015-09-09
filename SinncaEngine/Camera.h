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
//#include "Types.h"
#include "Node.h"

namespace sinnca
{
	
	enum method3D
	{
		none, // no 3D effect, also default
		native, // built-in display is capible of 3D effect
		stereoscopic, // 3D using those two color glasses like the tenth doctor wears to find "stuff"
		crosseye, // displays both views next to each other. User then looks at screen crosseyed to create 3D effect
		vr // similar to crosseye, but with matrix adjustments to allow for a realistic 3D view
	};
	
	class camera : public node
	{
		
		method3D current3D;
		
	public:
		
		bool isOrtho;
		static constexpr auto metatable = "camera";
		
		//point pos;
		//point rot;
		
		point zoom;
		// col and col2 used for stereoscopic 3D
		color* col2;
		
		camera();
		~camera();
		
		void setup();
		
		void look();
		
		void render();
		
		
	};
}

#endif /* defined(__SinncaEngine__Camera__) */
