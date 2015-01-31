//
//  InputType.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 12/18/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef SinncaEngine_InputType_h
#define SinncaEngine_InputType_h

namespace sinnca
{
	struct InputType
	{
		bool didChange;
		float x;
		
		InputType() :
		didChange(false),
		x(0.0f)
		{
			
		}
		
		void setChange(bool b)
		{
			didChange = b;
		}
		
		virtual void setDown(int s) = 0;
	};
	
}


#endif
