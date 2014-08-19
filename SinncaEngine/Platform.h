//
//  Platform.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 12/12/13.
//  Copyright (c) 2013 Ryan Oldis. All rights reserved.
//

#ifndef SinncaEngine_Platform_h
#define SinncaEngine_Platform_h

// Are we on a Microsoft platform?
#ifdef _WIN64
	#define snWin_64 1
	#define snWindows 1
	#define snDesktop 1

#elif _WIN32
	#define snWin_32 1
	#define snWindows 1
	#define snDesktop 1

// Are we on an apple platform?
#elif __APPLE__
//#include "AvailabilityMacros.h"
#include "TargetConditionals.h"
	// Is the project targeting iOS?
	#if TARGET_IPHONE_SIMULATOR
		#define snIos_sim 1
		#define sniPhone 1
		#define snApple 1
		#define snMobile 1

	#elif TARGET_OS_IPHONE
		#define sniPhone 1
		#define snMobile 1
		#define snApple 1

	#elif TARGET_OS_MAC
		#define snMacosx 1
		#define snApple 1
		#define snDesktop 1

	#endif

#elif __linux
	#define snLinux 1
	#define snDesktop 1

#elif __unix
	#define snUnix 1
	#define snDesktop 1

#else
	#define snOtherOS 1

#endif

#endif