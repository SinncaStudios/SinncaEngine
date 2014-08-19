//
//  ListAlloc.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 12/13/13.
//  Copyright (c) 2013 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__ListAlloc__
#define __SinncaEngine__ListAlloc__

#include <iostream>
#include "Memory.h"

namespace sinnca
{
	
	class list : public Memory
	{
		struct allocHeader
		{
			ui32 size;
			ui32 adjust;
		};
		
		struct block
		{
			ui32 size;
			block* next;
		};
		
		// ...and this block you cannot cha-a-ange...
		block* freeBlock;

	public:
		
		list(ui32 size);
		~list();
		
		void* allocate(ui32 size, ui8 align);
		void deallocate(void* p);
	  
	};
	 
	
	/*
	class FreeListAllocator : public Allocator
	{
	public:
		FreeListAllocator(ui32 size, void* pStart);
		~FreeListAllocator();
		
		void* allocate(ui32 size, ui8 alignment);
		
		void deallocate(void* p);
		
	private:
		
		struct AllocationHeader
		{
			ui32 size;
			ui32 adjustment;
		};
		
		struct FreeBlock
		{
			ui32 size;
			FreeBlock* pNext;
		};
		
		//FreeListAllocator(const FreeListAllocator&) {}; //Prevent copies because it might cause errors
		//FreeListAllocator& operator=(const FreeListAllocator&) {};
		
		FreeBlock* _pFreeBlocks;
	};
	 */
}

#endif /* defined(__SinncaEngine__ListAlloc__) */
