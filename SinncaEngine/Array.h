//
//  Array.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 3/6/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef SinncaEngine_Array_h
#define SinncaEngine_Array_h

#include "Types.h"
#include "Heap.h"
#include "List.h"

namespace sinnca
{
	template <class t>
	class array
	{
		struct chunk
		{
			t data[10];
		};
		
		linkList<chunk*> data;
		
	public:
		
		uint size;
		
		
		array()
		{
			size = 0;
			data.pushBack(new(Heap->allocateNew<chunk*>) chunk());
		}
		
		~array()
		{
			data.clear();
		}
		
		t* operator [](int i)
		{
			uint inChunk = i / 10;
			int access = i % 10;
			
			for (chunk* start = data, int i = 0; i < inChunk; i++)
			{
				start = start->next
			}
			
			return start[access];
		}
		
	};
}

#endif
