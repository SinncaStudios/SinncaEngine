//
//  Memory.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 11/3/13.
//  Copyright (c) 2013 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__Memory__
#define __SinncaEngine__Memory__

#include <iostream>
#include <assert.h>
#include "Types.h"

namespace sinnca
{
	
	// memory ailignment functions
	inline void* nextAddress(void* address, ui8 align)
	{
		return (void*) (((uintptr_t)address + (align - 1)) & ~(align - 1));
	}
	
	inline ui8 adjustAlign(void* address, ui8 align)
	{
		ui8 adjustment = align - ((uintptr_t)address & (align - 1));
		
		if (adjustment == align)
		{
			return 0;
		}
		
		return adjustment;
	}
	
	inline ui8 adjustHeader(void* address, ui8 align, ui8 head)
	{
		ui8 adjustment = align - ((uintptr_t)address & (align - 1));
		
		if (adjustment == align)
		{
			adjustment = 0;
			ui8 space = head;
			
			if (adjustment < space)
			{
				space -= adjustment;
				adjustment += align * (space / align);
				
				if (space % align > 0)
				{
					adjustment += align;
				}
			}
		}
		
		return adjustment;
	}
	
	
	
	class Memory
	{
	public:
		
		Memory()
		{
			usedMemory = 0;
			numOfAllocations = 0;
		}
		~Memory()
		{
			assert(usedMemory == 0 && numOfAllocations == 0);
		}
		
		virtual void* allocate(ui32 size, ui8 align) = 0;
		virtual void deallocate(void* point) = 0;
		
		template <class t> t* allocateNew()
		{
			return new (allocate(sizeof(t), __alignof(t))) t();
		}
		template <class t> void deallocateDelete(t* p)
		{
			if (p != NULL)
			{
				p->~t();
				deallocate(p);
			}
		}
		
		template<class T> T* allocateArray(ui32 length)
		{
			if(length == 0)
				return nullptr;
			
			ui32 headerSize = sizeof(ui32)/sizeof(T);
			
			if(sizeof(ui32)%sizeof(T) > 0)
				headerSize += 1;
			
			//Allocate extra space to store array length in the bytes before the array
			T* p = ( (T*) allocate(sizeof(T)*(length + headerSize), __alignof(T)) ) + headerSize;
			
			*( ((ui32*)p) - 1 ) = length;
			
			for(size_t i = 0; i < length; i++)
				new (&p[i]) T;
			
			return p;
		}
		
		template<class T> void deallocateArray(T* pArray)
		{
			if(pArray == nullptr)
				return;
			
			ui32 length = *( ((ui32*)pArray) - 1 );
			
			for(ui32 i = 0; i < length; i++)
				pArray[i].~T();
			
			//Calculate how much extra memory was allocated to store the length before the array
			ui32 headerSize = sizeof(ui32)/sizeof(T);
			
			if(sizeof(ui32)%sizeof(T) > 0)
				headerSize += 1;
			
			deallocate(pArray - headerSize);
		}
		
	protected:
		
		ulong usedMemory;
		ulong numOfAllocations;
		void* data;
	};
	 
	
	/*
	class Allocator
	{
	public:
		Allocator()
		{
			_usedMemory     = 0;
			_numAllocations = 0;
		}
		
		virtual ~Allocator()
		{
			assert(_numAllocations == 0 && _usedMemory == 0);
		}
		
		virtual void* allocate(ui32 size, ui8 alignment) = 0;
		
		virtual void deallocate(void* p) = 0;
		
		template <class T> T* allocateNew()
		{
			return new (allocate(sizeof(T), __alignof(T))) T;
		}
		
		template <class T> T* allocateNew(const T& t)
		{
			return new (allocate(sizeof(T), __alignof(T))) T(t);
		}
		
		template<class T> void deallocateDelete(T* pObject)
		{
			if (pObject != nullptr)
			{
				pObject->~T();
				deallocate(pObject);
			}
		}
		
		template<class T> T* allocateArray(ui32 length)
		{
			if(length == 0)
				return nullptr;
			
			ui32 headerSize = sizeof(ui32)/sizeof(T);
			
			if(sizeof(ui32)%sizeof(T) > 0)
				headerSize += 1;
			
			//Allocate extra space to store array length in the bytes before the array
			T* p = ( (T*) allocate(sizeof(T)*(length + headerSize), __alignof(T)) ) + headerSize;
			
			*( ((ui32*)p) - 1 ) = length;
			
			for(ui32 i = 0; i < length; i++)
				new (&p[i]) T;
			
			return p;
		}
		
		template<class T> void deallocateArray(T* pArray)
		{
			if(pArray == nullptr)
				return;
			
			ui32 length = *( ((ui32*)pArray) - 1 );
			
			for(ui32 i = 0; i < length; i++)
				pArray[i].~T();
			
			//Calculate how much extra memory was allocated to store the length before the array
			ui32 headerSize = sizeof(ui32)/sizeof(T);
			
			if(sizeof(ui32)%sizeof(T) > 0)
				headerSize += 1;
			
			deallocate(pArray - headerSize);
		}
		
		ui32 getUsedMemory()
		{
			return _usedMemory;
		}
		
		ui32 getNumAllocations()
		{
			return _numAllocations;
		}
		
	protected:
		ui32        _usedMemory;
		ui32        _numAllocations;
	};
	 */
		
}

#endif /* defined(__SinncaEngine__Memory__) */
