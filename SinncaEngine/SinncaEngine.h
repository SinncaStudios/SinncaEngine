//
//  SinncaEngine.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 10/30/13.
//  Copyright (c) 2013 Ryan Oldis. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "Game.h"
#include "Platform.h"
#include "Global.h"

#ifdef snMacosx
@interface SinncaEngine : NSOpenGLView
{

	BOOL running;
	
	NSTimer* timer;
	CFAbsoluteTime engineTime;
	sinnca::game myGame;
}
- (void) run: (NSTimer*)timer;
- (void) awakeFromNib;
- (void) drawRect:(NSRect)rect;
- (void) resizeScreen;
- (void) reshape;
- (void) prepareOpenGL;
- (void) dealloc;

- (void) keyDown:(NSEvent *)theEvent;
- (void) keyUp:(NSEvent *)theEvent;

@end
#endif



