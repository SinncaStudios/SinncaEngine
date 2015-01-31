//
//  ButtonCombo.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 2/18/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__ButtonCombo__
#define __SinncaEngine__ButtonCombo__

#include "InputWatcher.h"
#include "List.h"

namespace sinnca
{
	class buttonCombo : public inputWatcher
	{
		linkList<InputType*> combo;
		
	public:
		
		void update();
	};
}

#endif /* defined(__SinncaEngine__ButtonCombo__) */
