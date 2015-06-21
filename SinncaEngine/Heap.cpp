//
//  Heap.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 2/20/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "Heap.h"
#include "MemoryManager.h"
#include "Utility.h"

namespace sinnca
{
	heap* heap::_instance = NULL;
	heap* heap::Instance()
	{
		if (_instance == NULL)
		{
			_instance = new heap();
		}
		return _instance;
	}
	
	
	heap::heap()
	{
		// create a list allocator that CAN be resized
		heapList = new(memoryManager->allocate(sizeof(list))) list((ui32)toMegabyte(1), true);
	}
	
	heap::~heap()
	{
		delete heapList;
	}
	
	
	void* heap::allocate(ui32 size, ui8 align)
	{
		return heapList->allocate(size, align);
	}
	
	
	void heap::deallocate(void *p)
	{
		heapList->deallocate(p);
	}
	
}