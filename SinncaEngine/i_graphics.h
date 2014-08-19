//
//  i_graphics.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 3/17/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef SinncaEngine_i_graphics_h
#define SinncaEngine_i_graphics_h

#include "Platform.h"

#ifdef snWindows
// include windows.h an other stuff...

#elif snMacosx
	#include <OpenGL/OpenGL.h>
	#include <OpenGL/glu.h>
	#include <OpenGL/glext.h>

#elif sniPhone
	
		#import <UIKit/UIKit.h>
		#import <GLKit/GLKit.h>

#import <OpenGLES/EAGL.h>
#import <OpenGLES/ES2/gl.h>
#import <OpenGLES/ES2/glext.h>

#define glClearDepth glClearDepthf

#endif

#endif
