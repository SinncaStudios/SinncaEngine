//
//  StackAlloc.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 12/12/13.
//  Copyright (c) 2013 Ryan Oldis. All rights reserved.
//

#include "StackAlloc.h"
#include "MemoryManager.h"

namespace sinnca
{
	
	stack::stack(const ui32& size, void* start = NULL)
	{
		assert(size > 0);
		
		if (start == NULL)
		{
			data = memoryManager->allocate(size);
			
		} else {
			
			data = start;
		}
		
		curPos = data;
		initPos = data;
		
		totalSize = 0;
		
		usedMemory = 0;
		numOfAllocations = 0;
	}
	
	stack::~stack()
	{
		curPos = nullptr;
		initPos = nullptr;
		
		totalSize = 0;
		
		usedMemory = 0;
		numOfAllocations = 0;
		
		free(data);
	}
	
	void* stack::allocate(ui32 size, ui8 align)
	{
		assert(size != 0);
		
		ui8 adjust = adjustHeader(data, align, sizeof(allocHeader));
		if (usedMemory + adjust + size > totalSize)
		{
			return nullptr;
		}
		
		uintptr_t alignedAddress = (uintptr_t)curPos + adjust;
		allocHeader* head = (allocHeader*) (alignedAddress - sizeof(allocHeader));
		head->head = adjust;
		
		curPos = (void*)(alignedAddress + size);
		
		usedMemory += size + adjust;
		numOfAllocations++;
		
		return (void*)alignedAddress;
	}
	
	void stack::deallocate(void* point)
	{
		allocHeader* head = (allocHeader*) ((uintptr_t)point - sizeof(allocHeader));
		
		usedMemory -= (uintptr_t)curPos - (uintptr_t)point + head->head;
		curPos = (void*)((uintptr_t)point - head->head);
		
		numOfAllocations--;
	}
	
	
}