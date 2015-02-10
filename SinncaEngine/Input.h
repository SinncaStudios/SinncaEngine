//
//  Input.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 2/12/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__Input__
#define __SinncaEngine__Input__

#include <iostream>
#include "Types.h"
#include "Script.h"

#include "InputType.h"
#include "DigitalButton.h"
#include "AnalogButton.h"
#include "Analog2Axis.h"
#include "Analog3Axis.h"

namespace sinnca
{
	
	namespace Input
	{
		extern ui8 noOfInputsChanged;
		extern InputType* inputsChanged[20];
		extern uint tapLimit;
		
		namespace Keyboard
		{
			extern float prevKeyState[322];
			extern digitalButton keys[322];
		}
		
		namespace Mouse
		{
			extern uint x, y;
			extern digitalButton left, middle, right;
			
			extern analogButton pressure;
		}
		
		namespace Touch
		{
			extern float magnify;
			extern float rotation;
			extern float swipeX, swipeY;
		}
		
		void setup();
		void shutDown();
		
		void keySetupHelper(int currentKey);
		void update();
		void sendKeyDown(int k);
		void sendKeyUp(int k);
		
	}
	
	int l_keyDown(lua_State* L);
}

#endif /* defined(__SinncaEngine__Input__) */
