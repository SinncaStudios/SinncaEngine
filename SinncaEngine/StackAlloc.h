//
//  StackAlloc.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 12/12/13.
//  Copyright (c) 2013 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__StackAlloc__
#define __SinncaEngine__StackAlloc__

#include <iostream>
#include "Memory.h"

namespace sinnca
{
	
	class stack : public Memory
	{
		struct allocHeader
		{
			ui8 head;
		};
		
		void* initPos;
		void* curPos;
		
		ui32 totalSize;
		
		
	public:
		
		stack(const ui32& size, void* start);
		~stack();
		
		void* allocate(ui32 size, ui8 align);
		void deallocate(void* point);
		
		//void* operator new(size_t s);
		//void operator delete(void* p);
		
	};
	 
	
	/*
	class StackAllocator : public Allocator
	{
	public:
		StackAllocator(ui32 size, void* pStart);
		~StackAllocator();
		
		void* allocate(ui32 size, ui8 alignment);
		
		void deallocate(void* p);
		
	private:
		//StackAllocator(const StackAllocator&) {}; //Prevent copies because it might cause errors
		//StackAllocator& operator=(const StackAllocator&) {};
		
		struct AllocationHeader
		{
#if _DEBUG
			void* pPrevAddress;
#endif
			ui8 adjustment;
		};
		
		void* _pInitialPosition;
		
#if _DEBUG
		void* _pPrevPosition;
#endif
		
		void* _pCurrentPosition;
		
		ui32   _size;
	};
	 */
}

#endif /* defined(__SinncaEngine__StackAlloc__) */
