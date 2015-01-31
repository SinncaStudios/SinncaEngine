//
//  InputWatcher.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 12/19/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef SinncaEngine_InputWatcher_h
#define SinncaEngine_InputWatcher_h

#include "InputType.h"
#include "Action.h"

namespace sinnca
{
	
	class inputWatcher
	{
	protected:
		
		InputType* cause;
		action* effect;
		bool wasCaused, enabled;
		
	public:
		
		virtual void setCause(InputType* c)
		{
			cause = c;
		}
		
		virtual void setEffect(action* a)
		{
			effect = a;
		}
		
		virtual void update() = 0;
		
	};
	
	
}

#endif
