//
//  EditorView.m
//  SinncaEngine
//
//  Created by Ryan Oldis on 3/7/15.
//  Copyright (c) 2015 Ryan Oldis. All rights reserved.
//

#import "EditorView.h"
#import <OpenGL/OpenGL.h>
#import <OpenGL/glext.h>
#import <OpenGL/gl.h>

@implementation EditorView

- (void)drawRect:(NSRect)dirtyRect {
    [super drawRect:dirtyRect];
    
    // Drawing code here.
	glClearColor(0.5f, 0.64f, 0.77f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glFlush();
}

@end
