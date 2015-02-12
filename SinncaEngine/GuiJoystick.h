//
//  GuiJoystick.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 8/11/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__GuiJoystick__
#define __SinncaEngine__GuiJoystick__

#include "GuiWidget.h"

namespace sinnca
{
	class guiJoystick : public guiWidget
	{
		// top of joystick, not optional
		guiWidget knob;
		
		// who's the "stick" of the joystick?
		guiWidget* shaft; //Shut your mouth!
		// I'm just talking about GuiJoystick!
		// We can dig it!
		
		// shows the limits of the joystick
		guiWidget base;
		
		
	public:
		
		
		
		void* operator new(size_t s, std::string n);
		void operator delete(void* p);
	};
}

#endif /* defined(__SinncaEngine__GuiJoystick__) */
