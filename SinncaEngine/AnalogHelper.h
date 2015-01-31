//
//  AnalogHelper.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 12/22/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef SinncaEngine_AnalogHelper_h
#define SinncaEngine_AnalogHelper_h

#include "InputType.h"

namespace sinnca
{
	struct analogHelper : public InputType
	{
		analog2Axis* target;
		float y, z;
	};
}

#endif
