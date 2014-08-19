//
//  StackAlloc.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 12/12/13.
//  Copyright (c) 2013 Ryan Oldis. All rights reserved.
//

#include "StackAlloc.h"
#include "MemoryManager.h"

namespace sinnca
{
	
	stack::stack(const ui32& size, void* start = NULL)
	{
		assert(size > 0);
		
		if (start == NULL)
		{
			data = memoryManager->allocate(size);
			
		} else {
			
			data = start;
		}
		
		curPos = data;
		initPos = data;
		
		totalSize = 0;
		
		usedMemory = 0;
		numOfAllocations = 0;
	}
	
	stack::~stack()
	{
		curPos = nullptr;
		initPos = nullptr;
		
		totalSize = 0;
		
		usedMemory = 0;
		numOfAllocations = 0;
		
		free(data);
	}
	
	void* stack::allocate(ui32 size, ui8 align)
	{
		assert(size != 0);
		
		ui8 adjust = adjustHeader(data, align, sizeof(allocHeader));
		if (usedMemory + adjust + size > totalSize)
		{
			return nullptr;
		}
		
		uintptr_t alignedAddress = (uintptr_t)curPos + adjust;
		allocHeader* head = (allocHeader*) (alignedAddress - sizeof(allocHeader));
		head->head = adjust;
		
		curPos = (void*)(alignedAddress + size);
		
		usedMemory += size + adjust;
		numOfAllocations++;
		
		return (void*)alignedAddress;
	}
	
	void stack::deallocate(void* point)
	{
		allocHeader* head = (allocHeader*) ((uintptr_t)point - sizeof(allocHeader));
		
		usedMemory -= (uintptr_t)curPos - (uintptr_t)point + head->head;
		curPos = (void*)((uintptr_t)point - head->head);
		
		numOfAllocations--;
	}
	
	/*
	void* stack::operator new(size_t s)
	{
		return memoryManager->allocate(sizeof(stack));
	}
	
	void stack::operator delete(void *p)
	{
		memoryManager->deallocate(p);
	}
	 */
	
	
	/*
	StackAllocator::StackAllocator(ui32 size, void* pStart)
	: Allocator(), _size(size), _pInitialPosition(pStart), _pCurrentPosition(pStart)
	{
		assert(size > 0);
		
#if _DEBUG
		_pPrevPosition    = nullptr;
#endif
	}
	
	StackAllocator::~StackAllocator()
	{
		_pInitialPosition   = nullptr;
		
#if _DEBUG
		_pPrevPosition      = nullptr;
#endif
		
		_pCurrentPosition   = nullptr;
		
		_size               = 0;
	}
	
	void* StackAllocator::allocate(ui32 size, ui8 alignment)
	{
		assert(size != 0);
		
		ui8 adjustment = adjustHeader(_pCurrentPosition, alignment, sizeof(AllocationHeader));
		
		if(_usedMemory + adjustment + size > _size)
			return nullptr;
		
		uintptr_t alignedAddress = (uintptr_t)_pCurrentPosition + adjustment;
		
		//Add Allocation Header
		AllocationHeader* pHeader = (AllocationHeader*)(alignedAddress-sizeof(AllocationHeader));
		
		pHeader->adjustment   = adjustment;
		
#if _DEBUG
		pHeader->pPrevAddress = _pPrevPosition;
		
		_pPrevPosition    = (void*)alignedAddress;
#endif
		
		_pCurrentPosition = (void*)(alignedAddress + size);
		
		_usedMemory += size + adjustment;
		_numAllocations++;
		
		return (void*)alignedAddress;
	}
	
	void StackAllocator::deallocate(void* p)
	{
		//assert( p == _pPrevPosition );
		
		//Access the AllocationHeader in the bytes before p
		AllocationHeader* pHeader = (AllocationHeader*)((uintptr_t)p - sizeof(AllocationHeader));
		
		_usedMemory -= (uintptr_t)_pCurrentPosition - (uintptr_t)p + pHeader->adjustment;
		
		_pCurrentPosition = (void*)( (uintptr_t)p - pHeader->adjustment );
		
#if _DEBUG
		_pPrevPosition = pHeader->pPrevAddress;
#endif
		
		_numAllocations--;
	}
	 */
}