//
//  Computer.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 10/30/13.
//  Copyright (c) 2013 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__Computer__
#define __SinncaEngine__Computer__

#include <iostream>
#include <string>
#include "Platform.h"


namespace sinnca
{
	
	namespace Computer
	{
		extern int cpus, vcpus;
		extern int cpuSpeed;
		extern long memAvalible;
		// gpus
		extern int gpuMemAvailible;
		
		
		
		extern std::string machineName,
						   machineModel,
						   arch;
		
		extern std::string resourcePath;
		
	
		void setup();
		void getCompInfo();
		std::string getResourcePath();
		void setResourcePath(const char* path);
		
	};
}

#endif /* defined(__SinncaEngine__Computer__) */
