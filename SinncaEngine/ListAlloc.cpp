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
	 
	
	/*
	FreeListAllocator::FreeListAllocator(ui32 size, void* pStart)
	: Allocator(), _pFreeBlocks((FreeBlock*)pStart)
	{
		assert(size > sizeof(FreeBlock));
		
		_pFreeBlocks->size  = size;
		_pFreeBlocks->pNext = nullptr;
	}
	
	FreeListAllocator::~FreeListAllocator()
	{
		_pFreeBlocks        = nullptr;
	}
	
	void* FreeListAllocator::allocate(ui32 size, ui8 alignment)
	{
		assert(size != 0);
		
		//Check free blocks
		FreeBlock* pPrevFreeBlock = nullptr;
		FreeBlock* pFreeBlock     = _pFreeBlocks;
		
		while(pFreeBlock)
		{
			//Calculate adjustment needed to keep object correctly aligned
			ui8 adjustment = adjustHeader(pFreeBlock, alignment, sizeof(AllocationHeader));
			
			//If allocation doesn't fit in this FreeBlock, try the next
			if(pFreeBlock->size < size + adjustment)
			{
				pPrevFreeBlock = pFreeBlock;
				pFreeBlock = pFreeBlock->pNext;
				continue;
			}
			
			assert(sizeof(AllocationHeader) >= sizeof(FreeBlock));
			
			//If allocations in the remaining memory will be impossible
			if(pFreeBlock->size - size - adjustment <= sizeof(AllocationHeader))
			{
				//Increase allocation size instead of creating a new FreeBlock
				size = pFreeBlock->size;
				
				if(pPrevFreeBlock != nullptr)
					pPrevFreeBlock = pFreeBlock->pNext;
				else
					_pFreeBlocks = pFreeBlock->pNext;
			}
			else
			{
				//Else create a new FreeBlock containing remaining memory
				FreeBlock* pNextBlock = (FreeBlock*)( (uintptr_t)pFreeBlock + size + adjustment );
				pNextBlock->size = pFreeBlock->size - size - adjustment;
				pNextBlock->pNext = pFreeBlock->pNext;
				
				if(pPrevFreeBlock != nullptr)
					pPrevFreeBlock = pNextBlock;
				else
					_pFreeBlocks = pNextBlock;
			}
			
			uintptr_t alignedAddress = (uintptr_t)pFreeBlock + adjustment;
			
			AllocationHeader* pHeader = (AllocationHeader*)(alignedAddress - sizeof(AllocationHeader));
			pHeader->size             = size + adjustment;
			pHeader->adjustment       = adjustment;
			
			_usedMemory     += adjustment + size;
			_numAllocations++;
			
			return (void*)alignedAddress;
		}
		
		assert(false && "Couldn't find free block large enough!");
		
		return nullptr;
	}
	
	void FreeListAllocator::deallocate(void* p)
	{
		AllocationHeader* pHeader = (AllocationHeader*)((uintptr_t)p - sizeof(AllocationHeader));
		
		ui32 size = pHeader->size;
		
		uintptr_t blockStart = (uintptr_t)p - pHeader->adjustment;
		uintptr_t blockEnd   = blockStart + size;
		ui32 blockSize   = size;
		
		bool blockMerged = false;
		
		//Find adjacent free blocks and merge
		bool search = true;
		
		while(search)
		{
			search = false;
			
			FreeBlock* pPrevFreeBlock = nullptr;
			FreeBlock* pFreeBlock = _pFreeBlocks;
			
			while(pFreeBlock != nullptr)
			{
				if( (uintptr_t)pFreeBlock + pFreeBlock->size == blockStart )
				{
					pFreeBlock->size += blockSize;
					
					blockStart = (uintptr_t)pFreeBlock;
					blockEnd   = blockStart + pFreeBlock->size;
					blockSize  = pFreeBlock->size;
					
					search = true;
					blockMerged = true;
					break;
				} else if(blockEnd == (uintptr_t) pFreeBlock)
				{
					FreeBlock* pNewFreeBlock = (FreeBlock*) blockStart;
					pNewFreeBlock->pNext = pFreeBlock->pNext;
					pNewFreeBlock->size = blockSize + pFreeBlock->size;
					
					if(pFreeBlock == _pFreeBlocks)
						_pFreeBlocks = pNewFreeBlock;
					else if(pPrevFreeBlock != pNewFreeBlock)
						pPrevFreeBlock->pNext = pNewFreeBlock;
					
					blockStart = (uintptr_t)pNewFreeBlock;
					blockEnd   = blockStart + pNewFreeBlock->size;
					blockSize  = pNewFreeBlock->size;
					
					search = true;
					blockMerged = true;
					break;
				}
				
				pPrevFreeBlock = pFreeBlock;
				pFreeBlock = pFreeBlock->pNext;
			}
		}
		
		if(!blockMerged)
		{
			FreeBlock* pBlock         = (FreeBlock*)( (uintptr_t)p - pHeader->adjustment);
			pBlock->size              = blockSize;
			pBlock->pNext             = _pFreeBlocks;
			
			_pFreeBlocks              = pBlock;
		}
		
		_numAllocations--;
		_usedMemory -= size;
	}
	 */
}

