//
//  AppDelegate.h
//  Sinnca Demo
//
//  Created by Ryan Oldis on 10/31/13.
//  Copyright (c) 2013 Ryan Oldis. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>

@property (assign) IBOutlet NSWindow *window;

- (void) applicationDidFinishLaunching:(NSNotification *)notification;
- (BOOL) applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender;

@end
