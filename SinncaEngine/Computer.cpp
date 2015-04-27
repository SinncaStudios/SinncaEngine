
//
//  Computer.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 10/30/13.
//  Copyright (c) 2013 Ryan Oldis. All rights reserved.
//

#include "Computer.h"
#include "Utility.h"
#include "Heap.h"
#include "Platform.h"

#include <sys/sysctl.h>
#if snMacosx
#include <CoreFoundation/CoreFoundation.h>
#endif

namespace sinnca
{
	
	
	namespace Computer
	{
		int cpus, vcpus;
		int cpuSpeed;
		long memAvalible;
		bool hyperThreading;
		// gpus
		int gpuMemAvailible;
		
		
		
		std::string machineName,
		machineModel,
		arch;
		
		std::string resourcePath;
	
		void setup()
		{
			cpus = 0;
			vcpus = 0;
			cpuSpeed = 0;
			memAvalible = 0;
			
			// ----------------------------------------------------------------------------
			// This makes relative paths work in C++ in Xcode by changing directory to the Resources folder inside the .app bundle
			// Thanks to http://stackoverflow.com/questions/516200/relative-paths-not-working-in-xcode-c for the following code.
	#ifdef snMacosx
			CFBundleRef mainBundle = CFBundleGetMainBundle();
			CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
			char path[PATH_MAX];
			if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX))
			{
				// error!
				printf("file error\n");
			}
			CFRelease(resourcesURL);
			
			chdir(path);
			std::cout << "Current Path: " << path << std::endl;
			resourcePath = path;
	#endif
			// ----------------------------------------------------------------------------
		}

		void getCompInfo()
		{
			// Lets start with the number of proccessors
			if (cpus == 0)
			{
				#ifdef snWin_32
				
				// Windows functions will go here
				
				#elif snMacosx
				// open, read, and parse:
				// System/Library/CoreServices/Loginwindow.app/Contents/Resources/english.lproj/AboutThisMac.Strings
				
				// gets COMPLETE info
				
				#elif snUnix
				size_t size = sizeof(cpus);
				sysctlbyname("hw.physicalcpu", &cpus, &size, NULL, 0);
				printf("cpus: %i\n", cpus);
				
				size = sizeof(vcpus);
				sysctlbyname("hw.logicalcpu", &vcpus, &size, NULL, 0);
				printf("virtual cpus: %i\n", vcpus);
				
				size = sizeof(memAvalible);
				sysctlbyname("hw.memsize", &memAvalible, &size, NULL, 0);
				printf("RAM: %f\n", fromGigabyte(memAvalible));
				
				size = sizeof(machineModel);
				sysctlbyname("hw.model", &machineModel, &size, NULL, 0);
				printf("Model: %s\n", machineModel.c_str());
				
				#endif
			}
			
			if (vcpus == (cpus * 2))
			{
				hyperThreading = true;
			} else {
				hyperThreading = false;
			}
		}
		
		std::string getResourcePath()
		{
			return resourcePath;
		}
		void setResourcePath(const char *path)
		{
			resourcePath = path;
		}
	}
}