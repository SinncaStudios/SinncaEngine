//
//  PoolAlloc.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 1/30/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "PoolAlloc.h"
#include "MemoryManager.h"

namespace sinnca
{
	
	pool::pool(ui32 obSi, ui8 obAl, ui32 oSize)
	{
		objSize = obSi;
		objAlign = obAl;
		size = oSize;
		
		void* mem = memoryManager->allocate(oSize);
		
		assert(obSi >= sizeof(void*));
		
		ui8 adjustment = adjustAlign(mem, obAl);
		
		freelist = (void**)((uintptr_t)mem + adjustment);
		ui32 numOfObjects = (oSize - adjustment) / obSi;
		void** p = freelist;
		
		for (ui32 i = 0; i < numOfObjects-1; i++)
		{
			*p = (void*)((uintptr_t) p + obSi);
			p = (void**) *p;
		}
		
		*p = nullptr;
	}
	
	pool::~pool()
	{
		//freelist = nullptr;
		memoryManager->deallocate(freelist);
	}
	
	void* pool::allocate(ui32 oSize, ui8 align)
	{
		assert(oSize == objSize && align == objAlign);
		
		if (freelist == nullptr)
		{
			return nullptr;
		}
		
		if (usedMemory + oSize > size)
		{
			void* mem = *freelist;
			mem = memoryManager->reallocate(size + (oSize * 25), mem);
			ui8 adjustment = adjustAlign(mem, align);
			
			freelist = (void**)((uintptr_t)mem + adjustment);
		}
		
		void* p = freelist;
		
		freelist = (void**)(*freelist);
		
		usedMemory += oSize;
		numOfAllocations++;
		
		return p;
	}
	
	void pool::deallocate(void *p)
	{
		*((void**)p) = freelist;
		
		freelist= (void**)p;
		
		usedMemory -= objSize;
		numOfAllocations--;
	}
	 
	ui32 pool::getSize()
	{
		return size;
	}
}

