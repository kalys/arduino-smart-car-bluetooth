//
//  JoyStickWatcher.h
//  SmartCarGamePadApp
//
//  Created by Kalys Osmonov on 11/1/14.
//  Copyright (c) 2014 Kalys Osmonov. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum {
    WheelDirectionStopped = 0,
    WheelDirectionForward = 1,
    WheelDirectionBackward = 2
} WheelDirection;

@interface JoyStickWatcher : NSObject

@property (nonatomic, strong) NSArray *joySticks;

@property (nonatomic, assign) WheelDirection leftWheelDirection;
@property (nonatomic, assign) WheelDirection rightWheelDirection;
@property (nonatomic, strong) NSNumber *leftWheelSpeed;
@property (nonatomic, strong) NSNumber *rightWheelSpeed;

- (void)startWatchingJoysticks;

@end
