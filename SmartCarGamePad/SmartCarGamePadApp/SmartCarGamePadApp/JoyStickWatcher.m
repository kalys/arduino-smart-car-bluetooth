//
//  JoyStickWatcher.m
//  SmartCarGamePadApp
//
//  Created by Kalys Osmonov on 11/1/14.
//  Copyright (c) 2014 Kalys Osmonov. All rights reserved.
//

#import "JoyStickWatcher.h"
#import "DDHidLib.h"

@interface JoyStickWatcher ()

@property (nonatomic, strong) NSDictionary *wheelsStates;

@end

@implementation JoyStickWatcher

- (instancetype) init {
    self = [super init];
    if (self) {
        self.wheelsStates = @{
                              @(-1): @[@(WheelDirectionStopped), @(WheelDirectionStopped), @(0), @(0)],
                              @(0): @[@(WheelDirectionForward), @(WheelDirectionForward), @(255), @(255)],
                              @(4500): @[@(WheelDirectionForward), @(WheelDirectionForward), @(255), @(128)],
                              @(9000): @[@(WheelDirectionForward), @(WheelDirectionForward), @(255), @(0)],
                              @(13500): @[@(WheelDirectionBackward), @(WheelDirectionBackward), @(255), @(128)],
                              @(18000): @[@(WheelDirectionBackward), @(WheelDirectionBackward), @(255), @(255)],
                              @(22500): @[@(WheelDirectionBackward), @(WheelDirectionBackward), @(128), @(255)],
                              @(27000): @[@(WheelDirectionForward), @(WheelDirectionForward), @(0), @(255)],
                              @(31500): @[@(WheelDirectionForward), @(WheelDirectionForward), @(128), @(255)]
                              };
    }
    return self;
}

- (void)startWatchingJoysticks
{
    self.joySticks = [DDHidJoystick allJoysticks];
    [self.joySticks makeObjectsPerformSelector:@selector(setDelegate:) withObject:self];
    [self.joySticks makeObjectsPerformSelector:@selector(startListening) withObject:nil];
}

- (void) ddhidJoystick: (DDHidJoystick *) joystick
                 stick: (unsigned) stick
             povNumber: (unsigned) povNumber
          valueChanged: (int) value;
{
    NSLog(@"Stick111: %d, POV number: %d, changed: %d", stick, povNumber, value);
    NSArray *wheelsState = self.wheelsStates[@(value)];
    self.leftWheelDirection = [wheelsState[0] intValue];
    self.rightWheelDirection = [wheelsState[1] intValue];
    self.leftWheelSpeed = wheelsState[2];
    self.rightWheelSpeed = wheelsState[3];
}

- (void)ddhidJoystick:(DDHidJoystick *)joystick buttonDown:(unsigned)buttonNumber
{
    NSLog(@"button number %@ of joystick %u went down",joystick,buttonNumber);
}

- (void)ddhidJoystick:(DDHidJoystick *)joystick buttonUp:(unsigned)buttonNumber
{
    NSLog(@"button number %@ of joystick %u went up",joystick,buttonNumber);
}

@end
