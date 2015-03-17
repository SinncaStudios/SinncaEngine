//
//  ListAlloc.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 12/13/13.
//  Copyright (c) 2013 Ryan Oldis. All rights reserved.
//

#include "ListAlloc.h"
#include "MemoryManager.h"

namespace sinnca
{
	
	list::list(ui32 size)
	{
		freeBlock = (block*)memoryManager->allocate(size);
		assert(size > sizeof(freeBlock));
		
		freeBlock->size = size;
		freeBlock->next = nullptr;
	}
	
	list::~list()
	{
		freeBlock = nullptr;
	}
	
	void* list::allocate(ui32 size, ui8 align)
	{
		assert(size != 0);
		
		block* prevBlock = nullptr;
		block* freeBlocks = freeBlock;
		
		while(freeBlocks)
		{
			ui8 adjust = adjustHeader(freeBlocks, align, sizeof(allocHeader));
			
			if (freeBlocks->size < size + adjust)
			{
				prevBlock = freeBlocks;
				freeBlocks = freeBlocks->next;
				continue; // HERE >:(
			}
			
			assert(sizeof(allocHeader) >= sizeof(freeBlocks));
			
			if(freeBlocks->size - size - adjust <= sizeof(allocHeader))
			{
				
				size = freeBlocks->size;
				
				if(prevBlock != nullptr)
				{
					prevBlock = freeBlocks->next;
				} else {
					freeBlocks = freeBlocks->next;
				}
				
			} else {
				
				block* nextBlock = (block*)((uintptr_t)freeBlocks + size +adjust);
				nextBlock->size = freeBlocks->size - size - adjust;
				nextBlock->next = freeBlocks->next;
				
				if(prevBlock != nullptr)
				{
					prevBlock = nextBlock;
					
				} else {
					
					freeBlock = nextBlock;
				}
				
			}
			
			uintptr_t alignedAddress = (uintptr_t)freeBlocks + adjust;
			allocHeader* header = (allocHeader*)(alignedAddress - sizeof(allocHeader));
			header->size = size + adjust;
			header->adjust = adjust;
			
			usedMemory += adjust + size;
			numOfAllocations++;
			
			return (void*)alignedAddress;
		}
		
		return nullptr;
	}

	void list::deallocate(void *p)
	{
		allocHeader* header = (allocHeader*)((uintptr_t)p - sizeof(allocHeader));
		
		ui32 size = header->size;
		
		uintptr_t start = (uintptr_t)p - header->adjust;
		uintptr_t end = start + size;
		ui32 blockSize = size;
		
		bool merged = false;
		
		bool search = true;
		
		while (search)
		{
			search = false;
			
			block* prevBlock = nullptr;
			block* freeBlocks = freeBlock;
			
			while (freeBlocks != nullptr)
			{
				if ((uintptr_t)freeBlocks + freeBlocks->size == start)
				{
					freeBlocks->size += blockSize;
					
					start = (uintptr_t)freeBlocks;
					end = start + freeBlocks->size;
					blockSize = freeBlocks->size;
					
					search = true;
					merged = true;
					break;
					
				} else if (end == (uintptr_t)freeBlocks)
				{
					block* newBlock = (block*)start;
					newBlock->next = freeBlocks->next;
					newBlock->size = blockSize + freeBlocks->size;
					
					if (freeBlocks == freeBlock)
					{
						freeBlock = newBlock;
					} else if (prevBlock != newBlock)
					{
						prevBlock->next = newBlock;
					}
					
					start = (uintptr_t)newBlock;
					end = start + newBlock->size;
					blockSize = newBlock->size;
					
					search = true;
					merged = true;
					break;
				}
				
				prevBlock = freeBlocks;
				freeBlocks = freeBlocks->next;
			}
		}
		
		if (!merged)
		{
			block* aBlock = (block*)((uintptr_t)p - header->adjust);
			aBlock->size = blockSize;
			aBlock->next = freeBlock;
			
			freeBlock = aBlock;
		}
		
		numOfAllocations--;
		usedMemory -= size;
	}
	 
	
}

