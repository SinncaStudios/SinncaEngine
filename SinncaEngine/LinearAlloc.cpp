//
//  LinearAlloc.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 11/18/13.
//  Copyright (c) 2013 Ryan Oldis. All rights reserved.
//

#include "LinearAlloc.h"
#include "MemoryManager.h"

namespace sinnca
{
	
	linear::linear(ui32 size)
	{
		assert(size > 0);
		
		data = (void*)memoryManager->allocate(size);
		curPos = data;
		initPos = data;
		
		totalSize = size;
		
		usedMemory = 0;
		numOfAllocations = 0;
	}
	
	linear::~linear()
	{
		curPos = nullptr;
		initPos = nullptr;
		
		totalSize = 0;
		
		usedMemory = 0;
		numOfAllocations = 0;
		
		free(data);
	}
	
	void* linear::allocate(ui32 size, ui8 align)
	{
		assert(size != 0);
		
		ui8 adjust = adjustAlign(data, align);
		
		if (usedMemory + adjust + size > totalSize)
		{
			return nullptr;
		}
		
		uintptr_t alignedAddress = (uintptr_t)curPos + adjust;
		
		curPos = (void*)(alignedAddress + size);
		
		numOfAllocations++;
		usedMemory += size + adjust;
		
		return (void*)alignedAddress;
		
	}
	
	void linear::deallocate(void* point)
	{
		return;
	}
	
	void linear::clear()
	{
		curPos = initPos;
		
		usedMemory = 0;
		numOfAllocations = 0;
	}
	
	/*
	LinearAllocator::LinearAllocator(ui32 size, void* pStart)
	: Allocator(), _size(size), _pInitialPosition(pStart), _pCurrentPosition(pStart)
	{
		assert(size > 0);
	}
	
	LinearAllocator::~LinearAllocator()
	{
		_pInitialPosition   = nullptr;
		_pCurrentPosition   = nullptr;
		
		_size               = 0;
	}
	
	void* LinearAllocator::allocate(ui32 size, ui8 alignment)
	{
		assert(size != 0);
		
		ui8 adjustment =  adjustAlign(_pCurrentPosition, alignment);
		
		if(_usedMemory + adjustment + size > _size)
			return nullptr;
		
		uintptr_t alignedAddress = (uintptr_t)_pCurrentPosition + adjustment;
		
		_pCurrentPosition = (void*)(alignedAddress + size);
		
		_usedMemory += size + adjustment;
		_numAllocations++;
		
		return (void*)alignedAddress;
	}
	
	void LinearAllocator::deallocate(void* p)
	{
		assert( false && "Use clear() instead" );
	}
	
	void LinearAllocator::clear()
	{
		_numAllocations     = 0;
		_usedMemory         = 0;
		
		_pCurrentPosition   = _pInitialPosition;
	}
	 */
}