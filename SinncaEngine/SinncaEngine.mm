//
//  SinncaEngine.mm
//  SinncaEngine
//
//  Created by Ryan Oldis on 10/30/13.
//  Copyright (c) 2013 Ryan Oldis. All rights reserved.
//

#import "SinncaEngine.h"

#ifdef snMacosx
#import <OpenGL/gl.h>
#import <OpenGL/glext.h>
#import <OpenGL/glu.h>
#endif

#include "Global.h"
#include "Input.h"
#include "Graphics.h"

#ifdef snMacosx
@implementation SinncaEngine
using namespace sinnca;

- (void) viewDidLoad
{
	
}

- (void) awakeFromNib
{
	// Start the engine!
	
	running = YES;
	engineTime = CFAbsoluteTimeGetCurrent();
	
	timer = [NSTimer timerWithTimeInterval:(1.0f/60.0f) target:self selector:@selector(run:) userInfo:nil repeats:YES];
	[[NSRunLoop currentRunLoop] addTimer:timer forMode:NSDefaultRunLoopMode];
}

- (void) run:(NSTimer *)timer
{
	BOOL active = NO;
	
	if (running)
	{
		static CFTimeInterval delta = CFAbsoluteTimeGetCurrent() - engineTime;
		
		if (delta > 10.0f)
		{
			return;
			
		} else {
			
			active = YES;
		}
		
		engineTime = CFAbsoluteTimeGetCurrent();
		if (active)
		{
			[self drawRect:[self bounds]];
		}
	}
}

- (void) prepareOpenGL
{
	
	myGame.glW = [self bounds].size.width;
	myGame.glH = [self bounds].size.height;
	
	myGame.startUp();
	
}

- (void) drawRect:(NSRect)rect
{
	//[self resizeScreen];
	/*
	 glClear(GL_COLOR_BUFFER_BIT);
	 
	 glColor3f(1.0f, 0.9f, 0.0f);
	 
	 glBegin(GL_QUADS);
	 
	 glVertex2f(0.0f, 0.0f);
	 glVertex2f(1.0f, 0.0f);
	 glVertex2f(1.0f, 1.0f);
	 glVertex2f(0.0f, 1.0f);
	 
	 glEnd();
	 */
	
	myGame.loopItr();
	
	GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        //std::cout << "OpenGL error: " << err << std::endl;
    }
	
	if ([self inLiveResize])
		glFlush ();
	
	else
		[[self openGLContext] flushBuffer];
	
}


- (void) keyDown:(NSEvent *)theEvent
{
	unichar theKey = [[theEvent charactersIgnoringModifiers] characterAtIndex:0];
	
	Input->sendKeyDown((int)theKey);
}
- (void) keyUp:(NSEvent *)theEvent
{
	unichar theKey = [[theEvent charactersIgnoringModifiers] characterAtIndex:0];
	
	Input->sendKeyUp((int)theKey);
}
- (void) mouseDown:(NSEvent *)theEvent
{
	
}

- (void) resizeScreen
{
	NSRect newBounds = [self bounds];
	
	Graphics->setScreenSize(newBounds.size.width, newBounds.size.height);
	glViewport(0, 0, newBounds.size.width, newBounds.size.height);
}

- (void) reshape
{
	[super reshape];
	
	[self resizeScreen];
	[[self openGLContext] makeCurrentContext];
}


- (void) dealloc
{
	myGame.cleanUp();
	// [super dealloc] // not used with ARC!
}

@end
#endif

