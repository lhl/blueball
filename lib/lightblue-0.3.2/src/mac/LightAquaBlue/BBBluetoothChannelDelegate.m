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
//  BBBluetoothChannelDelegate.m
//  LightAquaBlue
//

#import "BBBluetoothChannelDelegate.h"

#import <IOBluetooth/objc/IOBluetoothRFCOMMChannel.h>
#import <IOBluetooth/objc/IOBluetoothL2CAPChannel.h>

static SEL channelDataSelector;
static SEL channelClosedSelector;


@implementation BBBluetoothChannelDelegate

+ (void)initialize
{
    channelDataSelector = @selector(channelData:data:);
    channelClosedSelector = @selector(channelClosed:);
}

- (id)initWithDelegate:(id)delegate
{
    self = [super init];
    m_delegate = delegate;
    return self;
}

- (void)rfcommChannelData:(IOBluetoothRFCOMMChannel *)rfcommChannel 
                     data:(void *)dataPointer 
                   length:(size_t)dataLength
{
    if (m_delegate && [m_delegate respondsToSelector:channelDataSelector]) {
        [m_delegate channelData:rfcommChannel 
                           data:[NSData dataWithBytes:dataPointer length:dataLength]];
    }
}

- (void)rfcommChannelClosed:(IOBluetoothRFCOMMChannel *)rfcommChannel
{
    if (m_delegate && [m_delegate respondsToSelector:channelClosedSelector]) {
        [m_delegate channelClosed:rfcommChannel];
    }        
}

- (void)l2capChannelData:(IOBluetoothL2CAPChannel *)l2capChannel 
                    data:(void *)dataPointer 
                  length:(size_t)dataLength
{
    if (m_delegate && [m_delegate respondsToSelector:channelDataSelector]) {
        [m_delegate channelData:l2capChannel 
                           data:[NSData dataWithBytes:dataPointer length:dataLength]];
    }    
}

- (void)l2capChannelClosed:(IOBluetoothL2CAPChannel *)l2capChannel
{
    if (m_delegate && [m_delegate respondsToSelector:channelClosedSelector]) {
        [m_delegate channelClosed:l2capChannel];
    }            
}

+ (IOReturn)synchronouslyWriteData:(NSData *)data
                   toRFCOMMChannel:(IOBluetoothRFCOMMChannel *)channel
{
    return [channel writeSync:(void *)[data bytes] length:[data length]];
}
                   
+ (IOReturn)synchronouslyWriteData:(NSData *)data
                    toL2CAPChannel:(IOBluetoothL2CAPChannel *)channel
{
    return [channel writeSync:(void *)[data bytes] length:[data length]];
}

@end
