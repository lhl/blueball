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
//  BBDelegatingInputStream.m
//  LightAquaBlue
//

#import "BBStreamingInputStream.h"


@implementation BBStreamingInputStream

- (id)initWithDelegate:(id)delegate
{
    self = [super init];
    
    mDelegate = delegate;
    mStatus = NSStreamStatusNotOpen;
    
    return self;
}

- (int)read:(uint8_t *)buffer maxLength:(unsigned int)maxLength
{
    NSData *data = [mDelegate readDataWithMaxLength:maxLength];
    if (!data) 
        return -1;

    int copyLength = [data length] < maxLength ? [data length] : maxLength;
    [data getBytes:buffer length:copyLength];
    return copyLength;
}

- (BOOL)getBuffer:(uint8_t **)buffer length:(unsigned int *)len
{
    // we cannot access buffer data without calling read:maxLength:
    return NO;
}

- (BOOL)hasBytesAvailable
{
    // don't know whether bytes are available until read:maxLength: is called
    return YES;
}

- (void)open
{
    mStatus = NSStreamStatusOpen;
}

- (void)close
{
    mStatus = NSStreamStatusClosed;
}

- (void)setDelegate:(id)delegate
{
    mDelegate = delegate;
}

- (id)delegate
{
    return mDelegate;
}

- (void)scheduleInRunLoop:(NSRunLoop *)aRunLoop forMode:(NSString *)mode
{
}

- (void)removeFromRunLoop:(NSRunLoop *)aRunLoop forMode:(NSString *)mode
{
}

- (BOOL)setProperty:(id)property forKey:(NSString *)key
{
    return NO;
}

- (id)propertyForKey:(NSString *)key
{
    return nil;
}

- (NSStreamStatus)streamStatus
{
    return mStatus;
}

@end
