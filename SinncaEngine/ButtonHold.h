//
//  ButtonHold.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 12/19/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__ButtonHold__
#define __SinncaEngine__ButtonHold__

#include "InputWatcher.h"
#include "Timer.h"

namespace sinnca
{
	class buttonHold : public inputWatcher
	{
		sinncaTime durration;
		
	public:
		
		void update();
	};
}


#endif /* defined(__SinncaEngine__ButtonHold__) */
