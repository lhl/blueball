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
//  BBDelegatingInputStream.h
//  LightAquaBlue
//
//  A NSInputStream subclass that calls readDataWithMaxLength: on the delegate
//  when data is required.
//  This class is only intended for use from the LightBlue library.
//  Most methods are not implemented, and there are no stream:HandleEvent: 
//  calls to the delegate.
//

#import <Cocoa/Cocoa.h>


@interface BBStreamingInputStream : NSInputStream {
    id mDelegate;
    NSStreamStatus mStatus;
}
- (id)initWithDelegate:(id)delegate;

@end


@protocol BBStreamingInputStreamDelegate

- (NSData *)readDataWithMaxLength:(unsigned int)maxLength;

@end

