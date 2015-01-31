//
//  DigitalButton.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 12/18/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef SinncaEngine_DigitalButton_h
#define SinncaEngine_DigitalButton_h

#include "InputType.h"

namespace sinnca
{
	struct digitalButton : public InputType
	{
		// for buttons on a controller or keys on a keyboard
		
		void setDown(int s)
		{
			x = (float)s;
		}
	};
}

#endif
