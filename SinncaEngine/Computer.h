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
	
#define Computer (computer::Instance())
	class computer
	{
		int cpus, vcpus;
		int cpuSpeed;
		long memAvalible;
		// gpus
		int gpuMemAvailible;
		
		
		
		std::string machineName,
					machineModel,
					arch;
		
		std::string resourcePath;
		
	public:
		
		std::string gCard;
		
		computer();
		void getCompInfo();
		std::string getResourcePath();
		void setResourcePath(const char* path);
		
		static computer* Instance();
		
	protected:
		
		static computer* _instance;
		
	};
}

#endif /* defined(__SinncaEngine__Computer__) */
