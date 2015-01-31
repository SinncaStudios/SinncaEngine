//
//  AnalogButton.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 12/18/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef SinncaEngine_AnalogButton_h
#define SinncaEngine_AnalogButton_h

#include "InputType.h"

namespace sinnca
{
	struct analogButton : public InputType
	{
		float deadZone;
		
		void setDown(int s)
		{
			x = (float)s;
		}
		
		void setDown(float s)
		{
			x = s;
		}
	};
}

#endif
