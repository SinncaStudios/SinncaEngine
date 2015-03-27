//
//  PoolHeap.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 3/17/15.
//  Copyright (c) 2015 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__PoolHeap__
#define __SinncaEngine__PoolHeap__

#include "PoolAlloc.h"
#include "Heap.h"
#include "List.h"

namespace sinnca
{
	template<class t>
	class poolHeap : public Memory
	{
		
		linkList<pool*> listdata;
		pool* currentPool;
		uint noOfElements;
		uint maxSize;
		
		
	public:
		
		poolHeap(uint num = 0) :
		noOfElements(0)
		{
			pool* p;
			
			if (num == 0) {
				p = new pool(sizeof(t), alignof(t), (sizeof(t) * 50));
				maxSize = 50;
			} else {
				p = new pool(sizeof(t), alignof(t), (sizeof(t) * num));
				maxSize = num;
			}
			
			listdata.pushBack(p);
			currentPool = p;
		}
		
		
		void* allocate(ui32 size, ui8 align)
		{
			if ((size + usedMemory) < currentPool->getSize())
			{
				currentPool->allocate(size, align);
				
			} else {
				
				// this chunk is full, make a new one
				pool* p = new pool(sizeof(t), alignof(t), (sizeof(t) * 50));
				listdata.pushBack(p);
			}
		}
		
		void deallocate(void* p)
		{
			
		}
		
	};
}

#endif /* defined(__SinncaEngine__PoolHeap__) */
