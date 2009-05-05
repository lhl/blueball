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
//  BBServiceAdvertiser.m
//  LightAquaBlue
//


#import <IOBluetooth/IOBluetoothUserLib.h>
#import <IOBluetooth/objc/IOBluetoothSDPServiceRecord.h>
#import <IOBluetooth/objc/IOBluetoothSDPUUID.h>

#import "BBServiceAdvertiser.h"


static NSString *kServiceItemKeyServiceClassIDList;
static NSString *kServiceItemKeyServiceName;
static NSString *kServiceItemKeyProtocolDescriptorList;

// template service dictionaries for each pre-defined profile
static NSDictionary *serialPortProfileDict;
static NSDictionary *objectPushProfileDict;
static NSDictionary *fileTransferProfileDict;	


@implementation BBServiceAdvertiser

+ (void)initialize
{
	kServiceItemKeyServiceClassIDList = @"0001 - ServiceClassIDList";
	kServiceItemKeyServiceName = @"0100 - ServiceName*";
	kServiceItemKeyProtocolDescriptorList = @"0004 - ProtocolDescriptorList";
	
	// initialize the template service dictionaries
	NSBundle *classBundle = [NSBundle bundleForClass:[BBServiceAdvertiser class]];
	serialPortProfileDict = 
		[[NSDictionary alloc] initWithContentsOfFile:[classBundle pathForResource:@"SerialPortDictionary"
                                                                           ofType:@"plist"]];
	objectPushProfileDict = 
		[[NSDictionary alloc] initWithContentsOfFile:[classBundle pathForResource:@"OBEXObjectPushDictionary"
                                                                           ofType:@"plist"]];
	fileTransferProfileDict = 
		[[NSDictionary alloc] initWithContentsOfFile:[classBundle pathForResource:@"OBEXFileTransferDictionary"
                                                                           ofType:@"plist"]];
	
	//kRFCOMMChannelNone = 0;
	//kRFCOMM_UUID = [[IOBluetoothSDPUUID uuid16:kBluetoothSDPUUID16RFCOMM] retain];	
}

+ (NSDictionary *)serialPortProfileDictionary
{
	return serialPortProfileDict;
}

+ (NSDictionary *)objectPushProfileDictionary
{
	return objectPushProfileDict;
}

+ (NSDictionary *)fileTransferProfileDictionary
{
	return fileTransferProfileDict;
}


+ (void)updateServiceDictionary:(NSMutableDictionary *)sdpEntries
					   withName:(NSString *)serviceName
					   withUUID:(IOBluetoothSDPUUID *)uuid
{
	if (sdpEntries == nil) return;
	
	// set service name
	if (serviceName != nil) {
		[sdpEntries setObject:serviceName forKey:kServiceItemKeyServiceName];
	}
	
	// set service uuid if given
	if (uuid != nil) {
		
		NSMutableArray *currentServiceList = 
		[sdpEntries objectForKey:kServiceItemKeyServiceClassIDList];
		
		if (currentServiceList == nil) {
			currentServiceList = [NSMutableArray array];
		} 
		
		[currentServiceList addObject:[NSData dataWithBytes:[uuid bytes] length:[uuid length]]];
		
		// update dict
		[sdpEntries setObject:currentServiceList forKey:kServiceItemKeyServiceClassIDList];
	}
}


+ (IOReturn)addRFCOMMServiceDictionary:(NSDictionary *)dict
							  withName:(NSString *)serviceName
								  UUID:(IOBluetoothSDPUUID *)uuid
							 channelID:(BluetoothRFCOMMChannelID *)outChannelID
				   serviceRecordHandle:(BluetoothSDPServiceRecordHandle *)outServiceRecordHandle
{	
	if (dict == nil)
		return kIOReturnError;
	
	NSMutableDictionary *sdpEntries = [NSMutableDictionary dictionaryWithDictionary:dict];
	[BBServiceAdvertiser updateServiceDictionary:sdpEntries
										withName:serviceName
										withUUID:uuid];
	
	// publish the service
	IOBluetoothSDPServiceRecordRef serviceRecordRef;
	IOReturn status = IOBluetoothAddServiceDict((CFDictionaryRef) sdpEntries, &serviceRecordRef);
	
	if (status == kIOReturnSuccess) {
		
		IOBluetoothSDPServiceRecord *serviceRecord =
			[IOBluetoothSDPServiceRecord withSDPServiceRecordRef:serviceRecordRef];
		
		// get service channel ID & service record handle
		status = [serviceRecord getRFCOMMChannelID:outChannelID];
		if (status == kIOReturnSuccess) {
			status = [serviceRecord getServiceRecordHandle:outServiceRecordHandle];
		}
		
		// cleanup
		IOBluetoothObjectRelease(serviceRecordRef);
	}
	
	return status;
}


+ (IOReturn)removeService:(BluetoothSDPServiceRecordHandle)handle
{
	return IOBluetoothRemoveServiceWithRecordHandle(handle);
}

@end
