/*
 * Copyright (c) 2006 Bea Lam. All rights reserved.
 * 
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation files
 * (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

//
//  BBLocalDevice.h
//  LightAquaBlue
//
//	Provides information about the local Bluetooth device.
//

#import <Cocoa/Cocoa.h>
#import <IOBluetooth/Bluetooth.h>

@interface BBLocalDevice : NSObject {
	//
}

/*
 * Returns the local device name, or nil if it can't be read.
 */
+ (NSString *)getName;

/*
 * Returns the local device address as a string, or nil if it can't be read.
 * The address is separated by hyphens, e.g. "00-11-22-33-44-55".
 */
+ (NSString *)getAddressString;

/*
 * Returns the local device's class of device, or -1 if it can't be read.
 */
+ (BluetoothClassOfDevice)getClassOfDevice;

/*
 * Returns YES if the local device is available and switched on.
 */
+ (BOOL)isPoweredOn;

@end
