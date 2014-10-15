
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

#if snIsUnix
#include <sys/sysctl.h>
#endif


#if snMacosx
#include <CoreFoundation/CoreFoundation.h>
#endif

namespace sinnca
{
	
	computer* computer::_instance = NULL;
	
	computer* computer::Instance()
	{
		if (_instance == NULL)
		{
			_instance = Heap->allocateNew<computer>();
		}
		
		return _instance;
	}
	
	computer::computer()
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

	void computer::getCompInfo()
	{
		// Lets start with the number of proccessors
		if (cpus == 0)
		{
			#ifdef snWindows
			
			// Windows functions will go here
			
			#else
			
			size_t size = sizeof(cpus);
			sysctlbyname("hw.physicalcpu", &cpus, &size, NULL, 0);
			
			size = sizeof(vcpus);
			sysctlbyname("hw.logicalcpu", &vcpus, &size, NULL, 0);
			
			size = sizeof(memAvalible);
			sysctlbyname("hw.memsize", &memAvalible, &size, NULL, 0);
			
			size = sizeof(machineModel);
			sysctlbyname("hw.model", &machineModel, &size, NULL, 0);
			
			size = sizeof(arch);
			sysctlbyname("hw.machine", &arch, &size, NULL, 0);
			
			size = sizeof(floatingPoint);
			sysctlbyname("hw.floatingpoint", &floatingPoint, &size, NULL, 0);
			
			size = sizeof(byteOrder);
			sysctlbyname("hw.byteorder", &byteOrder, &size, NULL, 0);
			
			
			#endif
		}
	}
	
	void computer::printInfo()
	{
		printf("cpus: %i\n", cpus);
		printf("virtual cpus: %i\n", vcpus);
		printf("RAM: %f\n", fromGigabyte(memAvalible));
		printf("Model: %s\n", machineModel);
		printf("Machine Architecture: %s\n", arch);
		printf("Floating point support: %i\n", floatingPoint);
		printf("Byte Order: %i\n", byteOrder);
		printf("Graphics Card Manufacturer: %s\n", gVendor.c_str());
		printf("Graphics Card: %s\n", gCard.c_str());
		printf("\n");
	}
	
	std::string computer::getResourcePath()
	{
		return resourcePath;
	}
	void computer::setResourcePath(const char *path)
	{
		resourcePath = path;
	}

}