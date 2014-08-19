//
//  Heap.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 2/20/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__Heap__
#define __SinncaEngine__Heap__

#include <iostream>
#include "ListAlloc.h"

namespace sinnca
{
#define Heap (heap::Instance())
	class heap : public Memory
	{
		struct chunk
		{
			ui32 size;
			ui32 used;
			list* data;
			chunk* next;
		};
		
		chunk* heapList;
		chunk* current;
		
	public:
		
		heap();
		~heap();
		
		void* allocate(ui32 size, ui8 align);
		void deallocate(void* p);
		
		static heap* Instance();
		
	protected:
		
		static heap* _instance;
	};
}

#endif /* defined(__SinncaEngine__Heap__) */
