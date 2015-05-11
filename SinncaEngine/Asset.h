//
//  Asset.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 1/30/15.
//  Copyright (c) 2015 Ryan Oldis. All rights reserved.
//

#ifndef SinncaEngine_Asset_h
#define SinncaEngine_Asset_h

//#include "Types.h"
#include "Script.h"
#include <string>
#include <assert.h>

namespace sinnca
{
	class asset
	{
		//for reference counting
		unsigned int count;
		
		// if false, destroy if 0 references
		bool standingBy;
	
	protected:
		
		std::string path;
		unsigned int ref;
		
	public:
		
		asset() :
		count(0),
		standingBy(true)
		{
			
		}
		
		virtual ~asset()
		{
			Script::unReference(ref);
		}
		
		
		virtual void load(std::string p) = 0;
		
		void addRef()
		{
			if (count == 4294967295) {
				// detect very unlikley integer overflow
				assert("ERROR: too many references caused reference count to overflow");
			}
			
			count++;
			standingBy = false;
		}
		
		void removeRef()
		{
			--count;
			if (count == 0 && !standingBy)
			{
				delete this;
			}
		}
		
		void standBy()
		{
			standingBy = true;
		}
	};
}

#endif
