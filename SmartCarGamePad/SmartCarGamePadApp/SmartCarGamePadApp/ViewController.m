//
//  ViewController.m
//  SmartCarGamePadApp
//
//  Created by Kalys Osmonov on 11/1/14.
//  Copyright (c) 2014 Kalys Osmonov. All rights reserved.
//

#import "ViewController.h"
#import "JoyStickWatcher.h"
#import "ORSSerialPort.h"

@interface ViewController ()

@property (nonatomic, strong) JoyStickWatcher *watcher;
@property (nonatomic, strong) ORSSerialPort *serialPort;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.watcher = [JoyStickWatcher new];
    [self.watcher startWatchingJoysticks];
    
    [NSTimer scheduledTimerWithTimeInterval:0.2 target:self selector:@selector(timer:) userInfo:nil repeats:YES];
    self.serialPort = [ORSSerialPort serialPortWithPath:@"/dev/tty.HC-06-DevB"];
    self.serialPort.baudRate = @9600;
    [self.serialPort open];
}

- (void) timer:(NSTimer *) timer {
    if ([self.watcher.leftWheelSpeed intValue] > 0 || [self.watcher.rightWheelSpeed intValue] > 0) {
        [self.serialPort sendData:[self wheelsData]];
    }
}

- (NSData *) wheelsData {
    unsigned char data[5];
    if (self.watcher.leftWheelDirection == WheelDirectionForward || self.watcher.leftWheelDirection == WheelDirectionStopped) {
        data[0] = 'f';
    } else {
        data[0] = 'b';
    }
    
    if (self.watcher.rightWheelDirection == WheelDirectionForward || self.watcher.rightWheelDirection == WheelDirectionStopped) {
        data[2] = 'f';
    } else {
        data[2] = 'b';
    }
    
    data[1] = [self.watcher.leftWheelSpeed charValue];
    data[3] = [self.watcher.rightWheelSpeed charValue];
    data[4] = 'e';
    
    return [NSData dataWithBytes:data length:5];
}

- (void) dealloc {
    [self.serialPort close];
}

@end
