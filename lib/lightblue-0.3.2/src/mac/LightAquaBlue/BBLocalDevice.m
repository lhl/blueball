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
//  BBLocalDevice.m
//  LightAquaBlue
//

#import <IOBluetooth/Bluetooth.h>
#import <IOBluetooth/IOBluetoothUserLib.h>
#import <IOBluetooth/IOBluetoothUtilities.h>

#import "BBLocalDevice.h"


@implementation BBLocalDevice

+ (NSString *)getName
{
	BluetoothDeviceName name;
    IOReturn result;
	
	result = IOBluetoothLocalDeviceReadName(name, NULL, NULL, NULL);
    if (result == kIOReturnSuccess) {
		NSString *s = [NSString stringWithCString:(char *)name];
		if (s != nil) 
			return s;
    }        
	
    return nil;
}

+ (NSString *)getAddressString
{
	BluetoothDeviceAddress address;
    IOReturn result;
	
	result = IOBluetoothLocalDeviceReadAddress(&address, NULL, NULL, NULL);
    if (result == kIOReturnSuccess) {
		return IOBluetoothNSStringFromDeviceAddress(&address);
    }        
	
    return nil;
}

+ (BluetoothClassOfDevice)getClassOfDevice
{
	BluetoothClassOfDevice classOfDevice;
    IOReturn result;
	
	result = IOBluetoothLocalDeviceReadClassOfDevice(&classOfDevice, NULL, NULL, NULL);
    if (result == kIOReturnSuccess) {
		return classOfDevice;
    }        
	
    return -1;
}

+ (BOOL)isPoweredOn
{
	if (!IOBluetoothLocalDeviceAvailable()) 
		return NO;
	
	BluetoothHCIPowerState powerState;
	IOReturn status = IOBluetoothLocalDeviceGetPowerState(&powerState);
	if (status != kIOReturnSuccess || powerState != kBluetoothHCIPowerStateON) 
		return NO;
	
	return YES;
}

@end
