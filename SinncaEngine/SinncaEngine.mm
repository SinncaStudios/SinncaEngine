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

- (BOOL) acceptsFirstResponder
{
	return YES;
}

- (BOOL) becomeFirstResponder
{
	return YES;
}

- (BOOL) resignFirstResponder
{
	return YES;
}

- (void) viewDidLoad
{
	
}

- (void) awakeFromNib
{
	// Start the engine!
	
	running = YES;
	isActive = FALSE;
	engineTime = CFAbsoluteTimeGetCurrent();
	
	timer = [NSTimer timerWithTimeInterval:(1.0f/60.0f) target:self selector:@selector(run:) userInfo:nil repeats:YES];
	[[NSRunLoop currentRunLoop] addTimer:timer forMode:NSDefaultRunLoopMode];
}

- (void) run:(NSTimer *)timer
{
	BOOL active = NO;
	
	if (running)
	{
		#warning remove all of this! check FPS in loopItr
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
	
	isActive = TRUE;
	
}

- (void) drawRect:(NSRect)rect
{
	if (isActive)
	{
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
	
}


- (void) keyDown:(NSEvent *)theEvent
{
	unichar theKey = [[theEvent charactersIgnoringModifiers] characterAtIndex:0];
	
	Input::sendKeyDown((int)theKey);
}
- (void) keyUp:(NSEvent *)theEvent
{
	unichar theKey = [[theEvent charactersIgnoringModifiers] characterAtIndex:0];
	
	Input::sendKeyUp((int)theKey);
}
- (void) mouseDown:(NSEvent *)theEvent
{
	
	switch ([theEvent type])
	{
		case NSLeftMouseDown:
			Input::Mouse::left.x = 1.0f;
			Input::Mouse::pressure.x = theEvent.pressure;
			break;
			
		case NSOtherMouseDown:
			Input::Mouse::middle.x = 1.0f;
			break;
			
		case NSRightMouseDown:
			Input::Mouse::right.x = 1.0f;
			break;
			
		
		default:
			break;
	}
}

- (void) mouseUp:(NSEvent *)theEvent
{
	
	switch ([theEvent type])
	{
		case NSLeftMouseUp:
			Input::Mouse::left.x = 0.0f;
			Input::Mouse::pressure.x = theEvent.pressure;
			break;
			
		case NSOtherMouseUp:
			Input::Mouse::middle.x = 0.0f;
			break;
			
		case NSRightMouseUp:
			Input::Mouse::right.x = 0.0f;
			break;
			
			
		default:
			break;
	}
}

- (void) mouseMoved:(NSEvent*)theEvent
{
	NSPoint loc = [self convertPoint:[theEvent locationInWindow] fromView: nil];
	Input::Mouse::x = loc.x;
	Input::Mouse::y = loc.y;
}

// multi-touch events

- (void) magnifyWithEvent:(NSEvent*)theEvent
{
	Input::Touch::magnify = [theEvent magnification];
}

- (void) rotateWithEvent:(NSEvent*)theEvent
{
	Input::Touch::rotation = [theEvent rotation];
}

- (void) swipeWithEvent:(NSEvent*)theEvent
{
	Input::Touch::swipeX = [theEvent deltaX];
	Input::Touch::swipeY = [theEvent deltaY];
}

- (void) resizeScreen
{
	NSRect newBounds = [self bounds];
	
	Graphics::setScreenSize(newBounds.size.width, newBounds.size.height);
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

