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
		heapList = new(memoryManager->allocate(sizeof(chunk))) chunk();
		heapList->data = new (memoryManager->allocate(sizeof(list))) list((ui32)toMegabyte(1));
		heapList->size = (ui32)toMegabyte(1);
		heapList->used = 0;
		
		current = heapList;
	}
	
	heap::~heap()
	{
		/*
		chunk* temp = heapList;
		chunk* anotherTemp = NULL;
		
		while (temp->next)
		{
			
		}
		 */
	}
	
	
	void* heap::allocate(ui32 size, ui8 align)
	{
		if (current->used + size > current->size)
		{
			chunk* temp = heapList;
			
			while (temp->next)
			{
				if (temp->used + size > temp->size)
				{
					// if this chunk is full...
					continue;
				} else {
					// this chunk has enough room
					current = temp;
					break;
				}
				
				if (!temp->next)
				{
					// we ran out of empty chunks! Time to make a new one
					chunk* newOne = temp->data->allocateNew<chunk>();
					newOne->data = new (memoryManager->allocate(sizeof(list))) list(toMegabyte(1));
					newOne->size = toMegabyte(1);
					newOne->used = 0;
					
					temp->next = newOne;
					current = newOne;
					
					return newOne->data->allocate(size, align);
				}
				
				temp = temp->next;
			}
		}
		
		numOfAllocations++;
		current->used += size;
		return current->data->allocate(size, align);
	}
	
	void heap::deallocate(void *p)
	{
		current->data->deallocate(p);
		numOfAllocations--;
		
		// now check the status of the chunks
		if (current->used <= 0)
		{
			// if this is the only chunk, we don't need to do the rest
			if (heapList->next == NULL)
			{
				return;
			}
			
			chunk* temp = heapList;
			chunk* anotherTemp = NULL;
			
			while (temp->next)
			{
				if (temp->used <= 0 && temp != current)
				{
					// we found another empty chunk
					chunk* thirdTemp = temp->next;
					
					anotherTemp->data->deallocate(temp);
					anotherTemp->next = thirdTemp;
					
					return;
				}
				
				anotherTemp = temp;
				temp = temp->next;
			}
		}
	}
	
}