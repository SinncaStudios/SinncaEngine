//
//  PoolAlloc.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 1/30/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "PoolAlloc.h"
#include "MemoryManager.h"

namespace sinnca
{
	
	pool::pool(ui32 obSi, ui8 obAl, ui32 oSize)
	{
		objSize = obSi;
		objAlign = obAl;
		size = oSize;
		
		void* mem = memoryManager->allocate(oSize);
		
		assert(obSi >= sizeof(void*));
		
		ui8 adjustment = adjustAlign(mem, obAl);
		
		freelist = (void**)((uintptr_t)mem + adjustment);
		ui32 numOfObjects = (oSize - adjustment) / obSi;
		void** p = freelist;
		
		for (ui32 i = 0; i < numOfObjects-1; i++)
		{
			*p = (void*)((uintptr_t) p + obSi);
			p = (void**) *p;
		}
		
		*p = nullptr;
	}
	
	pool::~pool()
	{
		freelist = nullptr;
	}
	
	void* pool::allocate(ui32 oSize, ui8 align)
	{
		assert(oSize == objSize && align == objAlign);
		
		if (freelist == nullptr)
		{
			return nullptr;
		}
		
		void* p = freelist;
		
		freelist = (void**)(*freelist);
		
		usedMemory += oSize;
		numOfAllocations++;
		
		return p;
	}
	
	void pool::deallocate(void *p)
	{
		*((void**)p) = freelist;
		
		freelist= (void**)p;
		
		usedMemory -= objSize;
		numOfAllocations--;
	}
	 
	/*
	PoolAllocator::PoolAllocator(ui32 objectSize, ui8 objectAlignment, ui32 size, void* pMem)
	: Allocator(), _objectSize(objectSize), _objectAlignment(objectAlignment), _size(size)
	{
		assert(objectSize >= sizeof(void*));
		
		//Calculate adjustment needed to keep object correctly aligned
		ui8 adjustment = adjustAlign(pMem, objectAlignment);
		
		_pFreeList = (void**)((uintptr_t)pMem + adjustment);
		
		ui32 numObjects = (size-adjustment)/objectSize;
		
		void** p = _pFreeList;
		
		//Initialize free blocks list
		for(ui32 i = 0; i < numObjects-1; i++)
		{
			*p = (void*)( (uintptr_t) p + objectSize );
			p = (void**) *p;
		}
		
		*p = nullptr;
	}
	
	PoolAllocator::~PoolAllocator()
	{
		_pFreeList = nullptr;
	}
	
	void* PoolAllocator::allocate(ui32 size, ui8 alignment)
	{
		assert(size == _objectSize && alignment == _objectAlignment);
		
		if(_pFreeList == nullptr)
			return nullptr;
		
		void* p = _pFreeList;
		
		_pFreeList = (void**)(*_pFreeList);
		
		_usedMemory += size;
		_numAllocations++;
		
		return p;
	}
	
	void PoolAllocator::deallocate(void* p)
	{
		*((void**)p) = _pFreeList;
		
		_pFreeList = (void**)p;
		
		_usedMemory -= _objectSize;
		_numAllocations--;
	}
	 */
}

