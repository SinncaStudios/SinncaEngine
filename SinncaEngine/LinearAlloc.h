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
	 
}

#endif /* defined(__SinncaEngine__LinearAlloc__) */
