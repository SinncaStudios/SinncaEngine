//
//  Power.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 10/30/13.
//  Copyright (c) 2013 Ryan Oldis. All rights reserved.
//

#include "Power.h"

#ifdef snMacosx
#include <Carbon/Carbon.h>
#include <IOKit/ps/IOPowerSources.h>
#include <IOKit/ps/IOPSKeys.h>
#endif

/*
batteryStatus powerManager::getStatus()
{
	CFTypeRef blob = IOPSCopyPowerSourcesInfo();
	
	if (blob != NULL)
	{
		CFArrayRef powerList = IOPSCopyPowerSourcesList(blob);
	}
}
*/