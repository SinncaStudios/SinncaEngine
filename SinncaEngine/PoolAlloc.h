//
//  PoolAlloc.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 1/30/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__PoolAlloc__
#define __SinncaEngine__PoolAlloc__

#include <iostream>
#include "Memory.h"

namespace sinnca
{
	
	class pool : public Memory
	{
		ui32 size;
		ui32 objSize;
		ui8 objAlign;
		
		void** freelist;
		
	public:
		
		pool(ui32 obSi, ui8 obAl, ui32 oSize);
		~pool();
		
		void* allocate(ui32 oSize, ui8 align);
		void deallocate(void* p);
		
	};
	
	/*
	class PoolAllocator : public Allocator
	{
	public:
		PoolAllocator(ui32 objectSize, ui8 objectAlignment, ui32 size, void* pMem);
		~PoolAllocator();
		
		void* allocate(ui32 size, ui8 alignment);
		
		void deallocate(void* p);
		
	private:
		//PoolAllocator(const PoolAllocator&) {}; //Prevent copies because it might cause errors
		//PoolAllocator& operator=(const PoolAllocator&) {};
		
		ui32        _size;
		ui32        _objectSize;
		ui8         _objectAlignment;
		
		void**     _pFreeList;
	};
	 */
}

#endif /* defined(__SinncaEngine__PoolAlloc__) */
