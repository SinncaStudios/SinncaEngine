//
//  ButtonChord.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 12/19/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__ButtonChord__
#define __SinncaEngine__ButtonChord__

#include "InputWatcher.h"

namespace sinnca
{
	class buttonChord : public inputWatcher
	{
		bool incomplete, complete;
		ui8 noOfButtons;
		
		
	public:
		
		void update();
	};
}

#endif /* defined(__SinncaEngine__ButtonChord__) */
