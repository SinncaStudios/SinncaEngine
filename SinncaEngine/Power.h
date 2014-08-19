//
//  Power.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 10/30/13.
//  Copyright (c) 2013 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__Power__
#define __SinncaEngine__Power__

enum batteryStatus
{
	SN_NO_BATTERY = -1,
	SN_DRAINING = 0,
	SN_CHARGING = 1,
	SN_FULL = 2
};

class powerManager
{
	batteryStatus currentStatus;
	float percent;
	int time;
	
public:
	
	batteryStatus getStatus();
	float getPercent();
	int getTime();
	
};

#endif /* defined(__SinncaEngine__Power__) */
