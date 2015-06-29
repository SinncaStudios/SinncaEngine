//
//  ListAlloc.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 12/13/13.
//  Copyright (c) 2013 Ryan Oldis. All rights reserved.
//

#include "ListAlloc.h"
#include "MemoryManager.h"
#include "Utility.h"

namespace sinnca
{
	
	list::list(ui32 size, bool resize) :
	canResize(resize),
	capacity(size)
	{
		data = memoryManager->allocate(size);
		freeBlock = (block*)data;
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
		bool trying = true;
		
		do
		{
			trying = false;
			while(freeBlocks)
			{
				ui8 adjust = adjustHeader(freeBlocks, align, sizeof(allocHeader));
				
				if (freeBlocks->size < size + adjust)
				{
					prevBlock = freeBlocks;
					freeBlocks = freeBlocks->next;
					continue;
				}
				
				assert(sizeof(allocHeader) >= sizeof(freeBlocks));
				
				if(freeBlocks->size - size - adjust <= sizeof(allocHeader))
				{
					
					size = freeBlocks->size;
					
					if(prevBlock != nullptr)
					{
						prevBlock->next = freeBlocks->next;
					} else {
						freeBlocks = freeBlocks->next;
					}
					
				} else {
					
					block* nextBlock = (block*)((uintptr_t)freeBlocks + size +adjust);
					nextBlock->size = freeBlocks->size - size - adjust;
					nextBlock->next = freeBlocks->next;
					
					if(prevBlock != nullptr)
					{
						prevBlock->next = nextBlock;
						
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
			
			if (canResize)
			{
				// if we reach this point, it means that this allocator has run out of memory, BUT NEVER FEAR! We can re-allocate
				size_t allocSize = toMegabyte(1);
				if (size > allocSize)
					allocSize = size;
				
				
				block* newBlock = (block*)memoryManager->reallocate(size + allocSize, freeBlock);
				size += allocSize;
				
				if (newBlock != nullptr)
				{
					freeBlock = newBlock;
					
				} else {
					memoryManager->deallocate(freeBlock);
					assert("Memory resizing failed!");
				}
				freeBlock = newBlock;
				
				// now go and make the actual allocation
				trying = true;
			}
		} while (trying);
		
		
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
		
		
		if (canResize)
		{
			// check size after deallocation
			// shrink the block if you can
		 
			if ((capacity - usedMemory) > toMegabyte(1.5))
			{
				// shrink so that 1MB is free
				ui32 allocSize = (ui32)capacity - (ui32)toMegabyte(1);
				
				while ((capacity - usedMemory) > toMegabyte(1.5)) {
					allocSize -= toMegabyte(1);
					printf("size of data: %lu\nfree mem: %lu\n", capacity, capacity - usedMemory);
				}
				
				void* newBlock = memoryManager->reallocate(size + allocSize, data);
				if (newBlock != nullptr)
				{
					freeBlock = (block*)newBlock;
					freeBlock->size = allocSize;
					
				} else {
					memoryManager->deallocate(freeBlock);
					assert("Memory resizing failed!");
				}
				
			}
		}
		
	}
	 
	
}

