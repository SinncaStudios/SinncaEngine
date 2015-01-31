//
//  Analog2Axis.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 12/18/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef SinncaEngine_Analog2Axis_h
#define SinncaEngine_Analog2Axis_h

#include "InputType.h"

namespace sinnca
{
	struct analog2Axis : public InputType
	{
		float y;
		float deadZone;
		
		virtual void setDown(float s, float t)
		{
			x = s;
			y = t;
		}
	};
}

#endif
