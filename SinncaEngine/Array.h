//
//  Array.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 3/6/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef SinncaEngine_Array_h
#define SinncaEngine_Array_h

#include "List.h"
#include "Types.h"
#include "Heap.h"

namespace sinnca
{
	template <class t>
	class array
	{
		struct chunk
		{
			t data[10];
		};
		
		linkList<chunk> data;
		
	public:
		
		uint size;
		
		array()
		{
			size = 0;
			
		}
		~array()
		{
			data.clear();
		}
		
		t* operator [](int i)
		{
			if (i > size)
			{
				
			}
		}
		
	};
}

#endif
