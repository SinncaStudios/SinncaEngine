//
//  MemoryManager.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 1/30/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__MemoryManager__
#define __SinncaEngine__MemoryManager__

#include <iostream>
#include <vector>

#include "Memory.h"
#include "ListAlloc.h"
#include "StackAlloc.h"

namespace sinnca
{
#define memoryManager (memManager::Instance())
	
	
	class memManager
	{
	  /*
		struct element
		{
			ui32 size;
			ui32 used;
			void* p;
			element* prev;
			element* next;
			
		};
	   */
		std::vector<void*> alloations;
		void* systemSpace;
		
	public:
		
		//element* base;
		
		ui32 size;
		ui32 memUsed;
		
		stack* systems;
		//list* heap;
		
		memManager();
		~memManager();
		
		void* allocate(size_t size);
		void* reallocate(size_t size, void* p);
		void deallocate(void* p);
		void start();
		
		
		static memManager* Instance();
		
	protected:
		
		static memManager* _instance;
	  
	};
	
}

/*
void* operator new(size_t size);
void operator delete(void* p);

void* operator new[](size_t size);
void operator delete[](void* p);
*/
 
 
#endif /* defined(__SinncaEngine__MemoryManager__) */
