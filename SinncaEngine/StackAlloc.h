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
		
		
	};
	 
}

#endif /* defined(__SinncaEngine__StackAlloc__) */
