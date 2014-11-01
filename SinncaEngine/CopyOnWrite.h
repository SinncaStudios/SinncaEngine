//
//  CopyOnWrite.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 10/16/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__CopyOnWrite__
#define __SinncaEngine__CopyOnWrite__

#include <stdio.h>
#include "Heap.h"

namespace sinnca
{
	template <class T>
	class copyOnWrite
	{
		size_t* refcount;
		T* obj;
		
	public:
		
		copyOnWrite() : refcount(new (Heap->allocate(sizeof(size_t), alignof(size_t))) size_t(1)), obj(new T)
		{
			
		}
		copyOnWrite(const copyOnWrite &c) : refcount(c.refcount), obj(c.obj)
		{
			++*refcount;
		}
		
		const T &read() const {return *obj;}
		T &write()
		{
			if (*refcount==1)
			{
				return *obj;
			}
			
			
			obj=new T(*obj);
			--*refcount;
			refcount=new size_t(1);
			return *obj;
		}
		
	};
}

#endif /* defined(__SinncaEngine__CopyOnWrite__) */
