//
//  Analog3Axis.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 12/18/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef SinncaEngine_Analog3Axis_h
#define SinncaEngine_Analog3Axis_h

#include "Analog2Axis.h"

namespace sinnca
{
	struct analog3Axis : public analog2Axis
	{
		float z;
		
		void setDown(float s, float t, float u)
		{
			x = s;
			y = t;
			z = u;
		}
	};
}

#endif
