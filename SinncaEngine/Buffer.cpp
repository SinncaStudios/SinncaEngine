//
//  Buffer.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 9/27/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "Buffer.h"

namespace sinnca
{
	buffer::buffer()
	{
		alGenBuffers(1, &theBuffer);
	}
	
	buffer::~buffer()
	{
		alDeleteBuffers(1, &theBuffer);
	}
}