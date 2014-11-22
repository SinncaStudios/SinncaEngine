//
//  Timeline.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 11/5/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__Timeline__
#define __SinncaEngine__Timeline__

#include <stdio.h>
#include "Types.h"
#include "DoubleList.h"
#include "Heap.h"

namespace sinnca
{
	template <class T>
	class timeline
	{
		uint numOfFrames;
		uint* currentFrame;
		
		struct frame
		{
			uint pos, end;
			
			T data;
			
			frame(uint p, uint e, T d = 0) :
			pos(p),
			end(e),
			data(d) {}
			
			void* operator new(size_t s)
			{
				return Heap->allocate((unsigned int)s, alignof(frame));
			}
			
			void operator delete(void* p)
			{
				Heap->deallocate(p);
			}
			
			virtual bool isKeyFrame()
			{
				return false;
			}
		};
		
		struct keyframe : public frame
		{
			bool isKeyFrame()
			{
				return true;
			}
		};
		
		
		doubleList<frame>::iterator frameRef;

	public:
		
		doubleList<T> timeL;
		
		timeline() :
		// always has the 0th frame
		numOfFrames(1),
		currentFrame(NULL)
		{
			timeL.push_back(Heap->allocateNew<keyframe>);
			frameRef = timeL.begin();
		}
		
		// return current frame
		T* operator [](uint ind)
		{
			// if the frame we're looking for is the current one
			if (ind >= (*frameRef)->pos || ind <= (*frameRef)->end)
			{
				return frameRef;
			}
			
			doubleList<frame>::iterator traverser
			
			// which way do we go?
			if (ind > (*traverser)->pos && ind > (*traverser)->end)
			{
				// go forward
				while (ind >= (*traverser)->pos || ind <= (*traverser)->end)
				{
					traverser++;
				}
				
			} else {
				
				// go backward
				while (ind >= (*traverser)->pos || ind <= (*traverser)->end)
				{
					traverser--;
				}
			}
		}
		
		// cast to pure type, returns frame 0
		operator T()
		{
			if (currentFrame == NULL)
			{
				return timeL.begin();
				
			} else {
				
				return this[&currentFrame];
			}
			
			return NULL;
		}
		
	};
}

#endif /* defined(__SinncaEngine__Timeline__) */
