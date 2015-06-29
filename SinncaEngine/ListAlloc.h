//
//  ListAlloc.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 12/13/13.
//  Copyright (c) 2013 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__ListAlloc__
#define __SinncaEngine__ListAlloc__

#include <iostream>
#include "Memory.h"


namespace sinnca
{
	
	class list : public Memory
	{
		struct allocHeader
		{
			ui32 size;
			ui32 adjust;
		};
		
		struct block
		{
			ui32 size;
			block* next;
		};
		
		// ...and this block you cannot cha-a-ange...
		block* freeBlock;
		bool canResize;
		ulong capacity;

	public:
		
		list(ui32 size, bool resize = false);
		~list();
		
		void* allocate(ui32 size, ui8 align);
		void deallocate(void* p);
	  
	};
	 
	
}

#endif /* defined(__SinncaEngine__ListAlloc__) */
