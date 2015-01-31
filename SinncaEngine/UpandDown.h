//
//  UpandDown.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 12/19/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__UpandDown__
#define __SinncaEngine__UpandDown__

#include "InputWatcher.h"

namespace sinnca
{
	class upAndDown : public inputWatcher
	{
		bool wasDown, wasUp;
		action* otherEffect;
		
	public:
		
		void setOtherEffect(action* a);
		void update();
	};
}

#endif /* defined(__SinncaEngine__UpandDown__) */
