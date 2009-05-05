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
//  BBBluetoothChannelDelegate.h
//  LightAquaBlue
//
//	Provides a delegate for RFCOMM and L2CAP channels. This is only intended
//  for use from the LightBlue library.
//

#include <Foundation/Foundation.h>

@class IOBluetoothRFCOMMChannel;
@class IOBluetoothL2CAPChannel;


@interface BBBluetoothChannelDelegate : NSObject {
    id m_delegate;
}

- (id)initWithDelegate:(id)delegate;

+ (IOReturn)synchronouslyWriteData:(NSData *)data
                   toRFCOMMChannel:(IOBluetoothRFCOMMChannel *)channel;
                   
+ (IOReturn)synchronouslyWriteData:(NSData *)data
                    toL2CAPChannel:(IOBluetoothL2CAPChannel *)channel;                   

@end


/*
 * These are the methods that should be implemented by the delegate of this
 * delegate (very awkward, but that's what it is).
 */
@protocol BBBluetoothChannelDelegateObserver

- (void)channelData:(id)channel data:(NSData *)data;
- (void)channelClosed:(id)channel;

@end
