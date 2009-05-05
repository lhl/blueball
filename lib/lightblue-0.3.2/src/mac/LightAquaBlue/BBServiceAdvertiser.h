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
//  BBServiceAdvertiser.h
//  LightAquaBlue
//
//	Provides some basic operations for advertising Bluetooth services.
//

#import <IOBluetooth/Bluetooth.h>
@class IOBluetoothSDPUUID;

@interface BBServiceAdvertiser : NSObject {
	//
}

/*
 * Returns a ready-made dictionary for advertising a service with the Serial 
 * Port Profile.
 */ 
+ (NSDictionary *)serialPortProfileDictionary;

/*
 * Returns a ready-made dictionary for advertising a service with the OBEX 
 * Object Push Profile.
 */
+ (NSDictionary *)objectPushProfileDictionary;

/*
 * Returns a ready-made dictionary for advertising a service with the OBEX 
 * File Transfer Profile.
 */
+ (NSDictionary *)fileTransferProfileDictionary;

/*
 * Advertise a RFCOMM-based (i.e. RFCOMM or OBEX) service.
 *
 * Arguments:
 *	- dict: the dictionary containing the service details.
 *	- serviceName: the service name to advertise, which will be added to the
 *	  dictionary. Can be nil.
 *	- uuid: the custom UUID to advertise for the service, which will be added to 
 *	  the dictionary. Can be nil.
 *	- outChannelID: once the service is advertised, this will be set to the
 *	  RFCOMM channel ID that was used to advertise the service.
 *	- outServiceRecordHandle: once the service is advertised, this will be set 
 *    to the service record handle which identifies the service.
 */
+ (IOReturn)addRFCOMMServiceDictionary:(NSDictionary *)dict
							  withName:(NSString *)serviceName
								  UUID:(IOBluetoothSDPUUID *)uuid
							 channelID:(BluetoothRFCOMMChannelID *)outChannelID
				   serviceRecordHandle:(BluetoothSDPServiceRecordHandle *)outServiceRecordHandle;


/*
 * Stop advertising a service.
 */
+ (IOReturn)removeService:(BluetoothSDPServiceRecordHandle)handle;

@end
