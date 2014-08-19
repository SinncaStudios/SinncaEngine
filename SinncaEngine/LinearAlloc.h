//
//  LinearAlloc.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 11/18/13.
//  Copyright (c) 2013 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__LinearAlloc__
#define __SinncaEngine__LinearAlloc__

#include <iostream>
#include "Memory.h"

namespace sinnca
{
	
	class linear : public Memory
	{
		void* initPos;
		void* curPos;
		
		ui32 totalSize;
		
	public:
		
		linear(ui32 size);
		~linear();
		
		void* allocate(ui32 size, ui8 align);
		void deallocate(void* point);
		
		void clear();
		
	};
	 
	/*
	class LinearAllocator : public Allocator
	{
	public:
		LinearAllocator(ui32 size, void* pStart);
		~LinearAllocator();
		
		void* allocate(ui32 size, ui8 alignment);
		
		void deallocate(void* p);
		
		void clear();
		
	private:
		//LinearAllocator(const LinearAllocator&) {}; //Prevent copies because it might cause errors
		//LinearAllocator& operator=(const LinearAllocator&) {};
		
		void* _pInitialPosition;
		
		void* _pCurrentPosition;
		
		ui32   _size;
	};
	 */
}

#endif /* defined(__SinncaEngine__LinearAlloc__) */
