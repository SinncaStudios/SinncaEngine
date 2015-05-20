//
//  MemoryManager.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 1/30/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "MemoryManager.h"
#include "Utility.h"

namespace sinnca
{
	memManager* memManager::_instance = NULL;
	
	
	memManager* memManager::Instance()
	{
		if (_instance == NULL)
		{
			void* temp = malloc(sizeof(memManager));
			_instance = new(temp) memManager();
		}
		return _instance;
	}
	
	void memManager::start()
	{
		// nothing, just to get the singleton up
	}
	
	
	memManager::memManager()
	{
		size = 0;
		memUsed = 0;
		
		systemSpace = malloc(1024);
		void* temp = malloc(sizeof(stack));
		systems = new(temp) stack(1024, systemSpace);
		
	}
	
	memManager::~memManager()
	{
		// deallocate all
		
		size = 0;
		memUsed = 0;
		
		free(systems);
		free(this);
	}
	
	void* memManager::allocate(size_t size)
	{
		// make the actual allocation
		void* temp = malloc(size);
		memUsed += size;
		
		// add allocation to the list, then return
		alloations.push_back(temp);
		return temp;
	}
	
	void* memManager::reallocate(size_t size, void *p)
	{
		if (size == 0)
		{
			// do nothing
			return p;
		}
		
		void* newPointer = nullptr;
		for (int i = 0; i < alloations.size(); i++)
		{
			if (alloations[i] == p)
			{
				newPointer = realloc(p, size);
				
				break;
			}
		}
		
		return newPointer;
	}
	
	void memManager::deallocate(void *p)
	{
		for (int i = 0; i < alloations.size(); i++)
		{
			if (alloations[i] == p)
			{
				free(alloations[i]);
				alloations.erase(alloations.begin() + i);
			}
		}
		
	}
}

/*
void* operator new(size_t size)
{
	using namespace sinnca;
	memoryManager->memUsed += size;
	return memoryManager->heap->allocate(size, __alignof());
}
void operator delete(void* p)
{
	using namespace sinnca;
	memoryManager->heap->deallocate(p);
}

void* operator new[](size_t size)
{
	return NULL;
}
void operator delete[](void* p)
{
	
}
*/

